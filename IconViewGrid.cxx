/*
 * File   : IconViewGrid.cxx
 * Program: IconViewGridDialog++
 * Purpose: Program that helps user create and modify icons
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Created: 02/24/2016
 * Updated: 03/04/2016
 */

#include <QPainter>
#include <QMouseEvent>

#include "IconViewGrid.hxx"

IconViewGrid::IconViewGrid(QWidget* parent) : QWidget(parent)/*{{{*/
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    curColor = Qt::black;
    zoom = 8;

    curBrush = new Brush(simplePen);

    image = QImage(16, 16, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));

}
/*}}}*/
QSize IconViewGrid::sizeHint() const/*{{{*/
{
    QSize size = zoom * image.size();
    if (gridOn && zoom >= 3)
        size += QSize(1, 1);
    return size;
}
/*}}}*/
void IconViewGrid::setPenColor(const QColor &newColor)/*{{{*/
{
    curColor = newColor;
}
/*}}}*/
void IconViewGrid::setIconImage(const QImage &newImage)/*{{{*/
{
    if (newImage != image)
    {
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        update();
        updateGeometry();
    }
}
/*}}}*/
void IconViewGrid::setZoomFactor(int newZoom)/*{{{*/
{
    if (newZoom < 1)
        newZoom = 1;
    if (newZoom != zoom)
    {
        zoom = newZoom;
        update();
        updateGeometry();
        emit zoomed();
    }
}
/*}}}*/
void IconViewGrid::paintEvent(QPaintEvent* event)/*{{{*/
{
    QPainter painter(this);
    if (gridOn && zoom >= 3)
    {
        painter.setPen(palette().foreground().color());
        for (int i = 0; i <= image.width(); ++i)
            painter.drawLine(zoom * i, 0,
                             zoom * i, zoom * image.height());
        for (int j = 0; j <= image.height(); ++j)
            painter.drawLine(0, zoom * j,
                             zoom * image.width(), zoom * j);
    }
    for (int i = 0; i < image.width(); ++i)
    {
        for (int j = 0; j < image.height(); ++j)
        {
            QRect rect = pixelRect(i, j);
            if (!event->region().intersect(rect).isEmpty())
            {
                QColor color = QColor::fromRgba(image.pixel(i, j));
                if (color.alpha() < 255)
                    painter.fillRect(rect, Qt::white);
                painter.fillRect(rect, color);
            }
        }
    }
}
/*}}}*/
QRect IconViewGrid::pixelRect(int i, int j) const/*{{{*/
{
    if (gridOn && zoom >= 3)
        return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
    else
        return QRect(zoom * i, zoom * j, zoom, zoom);
}
/*}}}*/
void IconViewGrid::mousePressEvent(QMouseEvent* event)/*{{{*/
{
    emit mousePressed();
    if (event->button() == Qt::LeftButton)
        draw(event->pos(), true);
    else if (event->button() == Qt::RightButton)
        draw(event->pos(), false);
}
/*}}}*/
void IconViewGrid::mouseReleaseEvent(QMouseEvent* event)/*{{{*/
{
    emit mouseReleased();
    QWidget::mouseReleaseEvent(event);
}
/*}}}*/
void IconViewGrid::mouseMoveEvent(QMouseEvent* event)/*{{{*/
{
    if (event->buttons() & Qt::LeftButton)
        draw(event->pos(), true);
    else if (event->buttons() & Qt::RightButton)
        draw(event->pos(), false);
}
/*}}}*/
void IconViewGrid::setImagePixel(const QPoint &pos, const QColor& color)/*{{{*/
{
    int i = pos.x() / zoom;
    int j = pos.y() / zoom;

    if (image.rect().contains(i, j))
    {
        QColor before, after;
        before = QColor::fromRgba(iconImage().pixel(i, j));
        after = color;
        image.setPixel(i, j, after.rgba());
        update(pixelRect(i, j));

        if (before != after)
            emit modified(pos, before, after);
    }
}
/*}}}*/
void IconViewGrid::setBrush(Brush& newBrush)/*{{{*/
{
    curBrush = &newBrush;
}
/*}}}*/
void IconViewGrid::draw(const QPoint& pos, const QColor& color,/*{{{*/
            const Brush* _brush)
{
    if (!_brush)
        _brush = curBrush;
    shape_t::ConstIterator citer = _brush->brushShape().constBegin();
    do
    {
        QPoint absolutePos = pos + (zoom * *citer);
        setImagePixel(absolutePos, color);
    } while (++citer != _brush->brushShape().constEnd());
    // remove updates from setImagePixel and just do here?

}
/*}}}*/
void IconViewGrid::draw(const QPoint& pos, const bool opaque,/*{{{*/
            const Brush* _brush)
{
    QColor color = opaque ? penColor() : QColor(0, 0, 0, 0);
    draw(pos, color, _brush);
}
/*}}}*/
void IconViewGrid::toggleGrid()/*{{{*/
{
    gridOn = ! gridOn;
    update();
    updateGeometry();
}
/*}}}*/
void IconViewGrid::usePen()/*{{{*/
{
    curBrush = new Brush(simplePen);
}
/*}}}*/
