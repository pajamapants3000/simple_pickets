/*
 * File   : IconViewGrid.hxx
 * Program: IconViewGridDialog++
 * Purpose: Program that helps user create and modify icons
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT - See LICENSE
 * Created: 02/24/2016
 * Updated: 02/25/2016
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
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage);
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor);

public:
    IconViewGrid(QWidget* parent = 0);

    QColor penColor() const { return curColor; }
    int zoomFactor() const { return zoom; }
    QImage iconImage() const { return image; }
    QSize sizeHint() const;

signals:
    void modified();

public slots:
    void setPenColor(const QColor &newColor);
    void setZoomFactor(int newZoom);
    void setIconImage(const QImage &newImage);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

    QColor curColor;
    QImage image;
    int zoom;
};

#endif
