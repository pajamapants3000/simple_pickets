/*
 * File   : BrushSizer.hxx
 * Program: simple_pickets
 * Purpose: sets the size of the brush using one or two dimension values - impl
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Notes  : Add to toolbar using addWidget(); connect with brush shapes
 * Created: 03/03/2016
 * Updated: 03/03/2016
 */

#include <QLabel>
#include <QHBoxLayout>

#include "BrushSizer.hxx"

BrushSizer::BrushSizer(QWidget* parent) : QWidget(parent)/*{{{*/
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // create labels/*{{{*/
    QLabel* label1 = new QLabel(tr("&X="));
    QLabel* label2 = new QLabel(tr("&Y="));
/*}}}*/
    // create edit boxes/*{{{*/
    spinner1 = new QSpinBox();
    spinner1->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    spinner2 = new QSpinBox();
    spinner2->setButtonSymbols(QAbstractSpinBox::PlusMinus);
/*}}}*/
    label1->setBuddy(spinner1);
    label2->setBuddy(spinner2);

    // create layout
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(spinner1);
    layout->addWidget(label2);
    layout->addWidget(spinner2);

    connect(spinner1, SIGNAL(valueChanged(int)),
            this, SIGNAL(brushXChanged(int)));
    connect(spinner2, SIGNAL(valueChanged(int)),
            this, SIGNAL(brushYChanged(int)));

    setLayout(layout);
}
/*}}}*/
void BrushSizer::setBrushX(int newBrushX)/*{{{*/
{
    spinner1->setValue(newBrushX);
}
/*}}}*/
void BrushSizer::setBrushY(int newBrushY)/*{{{*/
{
    spinner2->setValue(newBrushY);
}
/*}}}*/
