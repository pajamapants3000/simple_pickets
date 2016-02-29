/*
 * File   : Zoomer.cxx
 * Program: simple_pickets
 * Purpose: Sets zoom level of image - implementation
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Created: 02/27/2016
 * Updated: 02/28/2016
 */

#include <QPushButton>
#include <QHBoxLayout>

#include "Zoomer.hxx"

Zoomer::Zoomer(QWidget* parent) : QWidget(parent)/*{{{*/
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    validator = new QIntValidator(1, 99);

    QPushButton* minus = new QPushButton(QIcon(":/images/minus.png"),
            tr(""));
    minus->setAutoRepeat(true);
    minus->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    minus->setFixedSize(QSize(26, 26));
    QPushButton* plus = new QPushButton(QIcon(":/images/plus.png"),
            tr(""));
    plus->setAutoRepeat(true);
    plus->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    plus->setFixedSize(QSize(26, 26));
    indicator = new QLineEdit(QString::number(defaultZoom));
    indicator->setValidator(validator);
    indicator->setFixedSize(QSize(26, 26));
    indicator->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(minus, SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(plus, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(indicator, SIGNAL(returnPressed()),
            this, SLOT(editZoom()));

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(minus);
    layout->addWidget(indicator);
    layout->addWidget(plus);
    layout->setSpacing(0);
    setLayout(layout);

}
/*}}}*/
void Zoomer::setZoom(const QString& newZoomText)/*{{{*/
{
    bool ok;
    setZoom(newZoomText.toInt(&ok, 10));
}
/*}}}*/
void Zoomer::setZoom(int newZoomLevel)/*{{{*/
{
    _zoom = newZoomLevel;
    indicator->setText(QString::number(_zoom));
    emit zooming(_zoom);
}
/*}}}*/
void Zoomer::zoomIn()/*{{{*/
{
    setZoom(_zoom + 1);
}
/*}}}*/
void Zoomer::zoomOut()/*{{{*/
{
    setZoom(_zoom - 1);
}
/*}}}*/
void Zoomer::unzoom()/*{{{*/
{
    setZoom(defaultZoom);
}
/*}}}*/
void Zoomer::editZoom()/*{{{*/
{
    setZoom(indicator->text());
}
/*}}}*/
