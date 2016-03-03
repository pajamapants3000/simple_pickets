/*
 * File   : BrushSizer.hxx
 * Program: simple_pickets
 * Purpose: sets the size of the brush using one or two dimension values - hdr
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Notes  : Add to toolbar using addWidget(); connect with brush shapes
 * Created: 03/03/2016
 * Updated: 03/03/2016
 */

#ifndef BRUSHSIZER_HXX
#define BRUSHSIZER_HXX

#include <QSpinBox>

class BrushSizer : public QWidget/*{{{*/
{
    Q_OBJECT;

public:
    BrushSizer(QWidget* parent = 0);
    int brushX() const { return spinner1->text().toInt(); }
    int brushY() const { return spinner2->text().toInt(); }

public slots:
    void setBrushX(int newBrushX);
    void setBrushY(int newBrushY);
private:
    QSpinBox* spinner1;
    QSpinBox* spinner2;

signals:
    void brushXChanged(int newBrushX) const;
    void brushYChanged(int newBrushY) const;

};
/*}}}*/

#endif  // def BRUSHSIZER_HXX

