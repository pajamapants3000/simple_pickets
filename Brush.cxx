/*
 * File   : Brush.cxx
 * Program: simple_pickets
 * Purpose: produces brush according to shape and size desired - implementation
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Created: 03/04/2016
 * Updated: 03/04/2016
 */

#include "Brush.hxx"

void Brush::create(const int x, const int y, const enum brushGeom geom)/*{{{*/
{
    curBrushX = x;
    curBrushY = y;
    curBrushGeom = geom;

    setBrush(curBrushX, curBrushY, curBrushGeom);

}
/*}}}*/
void Brush::uncreate()/*{{{*/
{
    delete curBrushShape;
}
/*}}}*/
void Brush::operator=(const Brush& lhs)/*{{{*/
{
    if (*this != lhs)
    {
        uncreate();
        create(lhs.curBrushX, lhs.curBrushY, lhs.curBrushGeom);
    }
}
/*}}}*/
bool Brush::operator==(const Brush& lhs)/*{{{*/
{
    return this->curBrushShape == lhs.curBrushShape;
}
/*}}}*/
bool Brush::operator!=(const Brush& lhs)/*{{{*/
{
    if (!(*this == lhs))
        return true;
    else
        return false;
}
/*}}}*/
void Brush::setBrush(const int x, const int y, const enum brushGeom geom)/*{{{*/
{
    switch (geom)
    {
        case Ellipse:
            curBrushShape = &genEllipse(x, y);
            break;
        case Ring:
            curBrushShape = &genRing(x, y);
            break;
        case Rectangle:
            curBrushShape = &genRectangle(x, y);
            break;
        case Block:
            curBrushShape = &genBlock(x, y);
            break;
        default:
            curBrushShape = &genBlock(x, y);
    }
    emit brushChanged(*curBrushShape);
}
/*}}}*/
void Brush::setBrushGeom(const enum brushGeom newBrushGeom)/*{{{*/
{
    curBrushGeom = newBrushGeom;
    setBrush(curBrushX, curBrushY, curBrushGeom);
}
/*}}}*/
void Brush::setBrushX(const int newBrushX)/*{{{*/
{
    curBrushX = newBrushX;
    setBrush(curBrushX, curBrushY, curBrushGeom);
}
/*}}}*/
void Brush::setBrushY(const int newBrushY)/*{{{*/
{
    curBrushY = newBrushY;
    setBrush(curBrushX, curBrushY, curBrushGeom);
}
/*}}}*/
const shape_t& Brush::genEllipse(const int x, const int y) const/*{{{*/
{
    shape_t* result = new shape_t;
    int R;
    // y = (Y/2)*sqrt(1-4(x^2/X^2)) - filled in
    if (x != 0)
        for (int i = -x / 2; i <= x / 2; ++i)
        {
            R = (int)( (y / 2.0) * sqrt( 1.0 - ((4.0 * i * i) / (x * x)) ));
            for (int j = -R; j <= R; ++j)
                result->push_back(QPoint(i, j));
        }
    if (y != 0)
        for (int i = -y / 2; i <= y / 2; ++i)
        {
            R = (int)( (x / 2.0) * sqrt( 1.0 - ((4.0 * i * i) / (y * y)) ));
            for (int j = -R; j <= R; ++j)
                result->push_back(QPoint(j, i));
        }
    if (x == 0 && y == 0)
        result->push_back(QPoint(x, y));
    return *result;
}
/*}}}*/
const shape_t& Brush::genRing(const int x, const int y) const /*{{{*/
{
    shape_t* result = new shape_t;
    int j;
    // y = (Y/2)*sqrt(1-4(x^2/X^2))
    if (x != 0)
        for (int i = -x / 2; i <= x / 2; ++i)
        {
            j = (int)( (y / 2.0) * sqrt( 1.0 - ((4.0 * i * i) / (x * x)) ));
            result->push_back(QPoint(i, j));
            result->push_back(QPoint(i, -j));
        }
    if (y != 0)
        for (int i = -y / 2; i <= y / 2; ++i)
        {
            j = (int)( (x / 2.0) * sqrt( 1.0 - ((4.0 * i * i) / (y * y)) ));
            result->push_back(QPoint(j, i));
            result->push_back(QPoint(-j, i));
        }
    if (x == 0 && y == 0)
        result->push_back(QPoint(x, y));
    return *result;
}
/*}}}*/
const shape_t& Brush::genRectangle(const int x, const int y) const/*{{{*/
{
    shape_t* result = new shape_t;
    for (int i = -x / 2; i <= x / 2; ++i)
    {
        result->push_back(QPoint(i, y/2));
        result->push_back(QPoint(i, -y/2));
    }
    for (int i = -y / 2; i < y / 2; ++i)
    {
        result->push_back(QPoint(x/2, i));
        result->push_back(QPoint(-x/2, i));
    }
    return *result;
}
/*}}}*/
const shape_t& Brush::genBlock(const int x, const int y) const/*{{{*/
{
    shape_t* result = new shape_t;
    for (int i = -x / 2; i <= x / 2; ++i)
        for (int j = -y / 2; j <= y / 2; ++j)
            result->push_back(QPoint(i, j));
    return *result;
}
/*}}}*/
void Brush::ellipseBrush()/*{{{*/
{
    setBrushGeom(Ellipse);
}
/*}}}*/
void Brush::ringBrush()/*{{{*/
{
    setBrushGeom(Ring);
}
/*}}}*/
void Brush::blockBrush()/*{{{*/
{
    setBrushGeom(Block);
}
/*}}}*/
void Brush::rectangleBrush()/*{{{*/
{
    setBrushGeom(Rectangle);
}
/*}}}*/
