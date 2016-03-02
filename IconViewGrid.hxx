/*
 * File   : IconViewGrid.hxx
 * Program: IconViewGridDialog++
 * Purpose: Program that helps user create and modify icons
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT - See LICENSE
 * Created: 02/24/2016
 * Updated: 03/02/2016
 */

#ifndef ICONVIEWGRID_HXX
#define ICONVIEWGRID_HXX

#include <QColor>
#include <QImage>
#include <QWidget>

typedef QList<QPoint> shape_t;
const shape_t shapePoint = { QPoint(0, 0) };

class IconViewGrid : public QWidget
{
    Q_OBJECT;
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor);
    Q_PROPERTY(shape_t brushShape READ brushShape WRITE setBrushShape);
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage);
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor);

public:
    IconViewGrid(QWidget* parent = 0);

    QColor penColor() const { return curColor; }
    shape_t brushShape() const { return *curShape; }
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
    void setBrushShape(const shape_t& newShape);
    void setZoomFactor(int newZoom);
    void setIconImage(const QImage &newImage);
    void draw(const QPoint& pos, const QColor& color,
            const shape_t* shape = new shape_t());
    void draw(const QPoint& pos, const bool opaque,
            const shape_t* shape = new shape_t());
    void toggleGrid();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    QRect pixelRect(int i, int j) const;
    void setImagePixel(const QPoint &pos, const QColor& color);
    QColor curColor;
    const shape_t* curShape = &shapePoint;
    QImage image;
    int zoom;
    bool gridOn = true;

};

#endif
