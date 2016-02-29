/*
 * File   : Zoomer.hxx
 * Program: simple_pickets
 * Purpose: Sets zoom level of image - header
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Created: 02/27/2016
 * Updated: 02/28/2016
 */

#ifndef ZOOMER_HXX
#define ZOOMER_HXX

#include <QWidget>
#include <QIntValidator>
#include <QLineEdit>

class Zoomer : public QWidget
{
    Q_OBJECT;
    Q_PROPERTY(int _zoom READ zoom WRITE setZoom NOTIFY zooming RESET unzoom);

public:
    Zoomer(QWidget* parent = 0);
    int zoom() { return _zoom; }
    const int defaultZoom = 10;

signals:
    void zooming(int newZoomLevel);

public slots:
    void setZoom(int newZoomLevel);
    void setZoom(const QString& newZoomText);
    void editZoom();

private slots:
    void zoomIn();
    void zoomOut();
    void unzoom();

private:
    QIntValidator* validator;
    QLineEdit* indicator;
    int _zoom;

};

#endif  // def ZOOMER_HXX

