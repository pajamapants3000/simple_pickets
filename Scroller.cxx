/*
 * File   : Scroller.hxx
 * Program: ScrollerDialog++
 * Purpose: Program that helps user create and modify icons
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT - See LICENSE
 * Notes  :
 * Created: 02/24/2016
 * Updated: 02/28/2016
 */

#include <QVBoxLayout>
#include <QScrollArea>

#include "Scroller.hxx"

Scroller::Scroller(QWidget* parent) : QWidget(parent)/*{{{*/
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    iconViewGrid = new IconViewGrid;

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);  // makes area stand out
    scrollArea->setWidget(iconViewGrid);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(scrollArea);
    setLayout(layout);
}
/*}}}*/
