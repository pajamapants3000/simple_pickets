/*
 * File   : IconViewGrid.hxx
 * Program: IconViewGridDialog++
 * Purpose: Program that helps user create and modify icons
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT - See LICENSE
 * Created: 02/24/2016
 * Updated: 03/01/2016
 */

#ifndef ICONVIEWGRID_HXX
#define ICONVIEWGRID_HXX

#include <QColor>
#include <QImage>
#include <QWidget>

class IconViewGrid : public QWidget
{
    Q_OBJECT;
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor);
    Q_PROPERTY(QList<QPoint> brushShape READ brushShape WRITE setBrushShape);
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage);
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor);

public:
    IconViewGrid(QWidget* parent = 0);

    QColor penColor() const { return curColor; }
    QList<QPoint> brushShape() const { return curShape; }
    int zoomFactor() const { return zoom; }
    QImage iconImage() const { return image; }
    QSize sizeHint() const;

signals:
    void modified(const QPoint& pos, const QColor& before, const QColor& after);
    void zoomed();
    void mousePressed();
    void mouseReleased();
    void mouseMoved(int i, int j);

public slots:
    void setPenColor(const QColor &newColor);
    void setBrushShape(const QList<QPoint>& newShape);
    void setZoomFactor(int newZoom);
    void setIconImage(const QImage &newImage);
    void draw(const QPoint& pos, const QColor& color,
            QList<QPoint> shape = QList<QPoint>());
    void draw(const QPoint& pos, const bool opaque,
            QList<QPoint> shape = QList<QPoint>());

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    QRect pixelRect(int i, int j) const;
    void setImagePixel(const QPoint &pos, const QColor& color);
    QColor curColor;
    QList<QPoint> curShape;
    QImage image;
    int zoom;

};

#endif
