/*
 * File   : ColourButton.cxx
 * Program: Written for ARGBSetterWidget
 * Purpose: A QPushButton subclass with changeable background color
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Notes  : Code is all here, no additional source (.cxx) file.
 * Created: 02/18/2016
 * Updated: 02/23/2016
 */

#include "ColourButton.hxx"

ColourButton::ColourButton(const QString& text, const QColor& colourIni,/*{{{*/
        QWidget* parent) : QPushButton(parent)
{
    _colour = colourIni;
    setText(text);
    connect(this, SIGNAL(clicked()), this, SLOT(clickedSendColour()));
}
/*}}}*/
void ColourButton::setColour(QColor newColor)/*{{{*/
{
    _colour = newColor;
    QColor colour_complement = QColor();
    colour_complement.setHsl( _colour.hslHue() + 180,
            _colour.hslSaturation(),     // want to just keep good saturation!
            255 - _colour.lightness(), 255);
    QPalette newPalette = this->palette();
    newPalette.setColor( QPalette::Normal, QPalette::Button, newColor );
    newPalette.setColor( QPalette::Normal, QPalette::ButtonText,
            colour_complement );
    this->setPalette( newPalette );
}
/*}}}*/
