/*
 * File   : Brush.hxx
 * Program: simple_pickets
 * Purpose: produces brush according to shape and size desired - header
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Created: 03/04/2016
 * Updated: 03/04/2016
 */

#include <QObject>
#include <QPoint>
#include <QList>

#ifndef BRUSH_HXX
#define BRUSH_HXX

typedef QList<QPoint> shape_t;

class Brush : public QObject/*{{{*/
{
    Q_OBJECT;

public:
    enum brushGeom { Ellipse, Ring, Rectangle, Block };
    Brush() : QObject() { create(0, 0, Block); }
    Brush(int x, int y, enum brushGeom geom) : QObject() {create(x, y, geom);}
    Brush(const Brush& orig) : QObject()
            { create(orig.curBrushX, orig.curBrushY, orig.curBrushGeom); }
    ~Brush() { uncreate(); }
    enum brushGeom geom() const { return curBrushGeom; }
    const shape_t& brushShape() const { return *curBrushShape; }

private:
    void create(int x, int y, enum brushGeom geom);
    void uncreate();
    void operator=(const Brush& lhs);
    bool operator==(const Brush& lhs);
    bool operator!=(const Brush& lhs);
    const shape_t& genEllipse(const int x, const int y) const;
    const shape_t& genRing(const int x, const int y) const;
    const shape_t& genRectangle(const int x, const int y) const;
    const shape_t& genBlock(const int x, const int y) const;
    enum brushGeom curBrushGeom;
    int curBrushX;
    int curBrushY;
    const shape_t* curBrushShape;

signals:
    void brushChanged(const shape_t& newBrushShape) const;

public slots:
    void setBrushGeom(enum brushGeom newBrushGeom);
    void setBrushX(int newBrushX);
    void setBrushY(int newBrushY);
    void ellipseBrush();
    void ringBrush();
    void rectangleBrush();
    void blockBrush();

private slots:
    void setBrush(int x, int y, enum brushGeom geom = Block);

};
/*}}}*/

#endif  // def BRUSH_HXX

