/*
 * File   : Scroller.hxx
 * Program: ScrollerDialog++
 * Purpose: Program that helps user create and modify icons
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT - See LICENSE
 * Created: 02/24/2016
 * Updated: 02/28/2016
 */

#ifndef ICONSCROLLGRID_HXX
#define ICONSCROLLGRID_HXX

#include <QWidget>

#include "IconViewGrid.hxx"

class Scroller : public QWidget
{
    Q_OBJECT;

public:
    Scroller(QWidget* parent = 0);

    IconViewGrid* iconViewGrid;
};

#endif
