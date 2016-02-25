/*
 * File   : Scroller.hxx
 * Program: ScrollerDialog++
 * Purpose: Program that helps user create and modify icons
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT - See LICENSE
 * Notes  :
 * Created: 02/24/2016
 * Updated: 02/24/2016
 */

#include <QScrollArea>
#include <QVBoxLayout>

#include "Scroller.hxx"

Scroller::Scroller(QWidget* parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    iconViewGrid = new IconViewGrid;

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);  // makes area stand out
    scrollArea->setWidget(iconViewGrid);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(scrollArea);
    setLayout(layout);
}

