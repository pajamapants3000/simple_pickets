/*
 * File   : ARGBSetterWidget.hxx
 * Program: ARGBSetterWidget
 * Purpose: A widget (QWidget subclass) that allows the user to set values
 *+for alhpa, red, green, and blue to produce a specific color; there is also
 *+a box that demonstrates the currently set color.
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Notes  : colourChanged signal carries the new color to be used when the
 *+user clicks the button
 * Created: 02/15/2016
 * Updated: 02/24/2016
 */

#include <QWidget>
#include <QColor>

#include "HexSpinBox.hxx"
#include "ColourButton.hxx"

class ARGBSetterWidget : public QWidget/*{{{*/
{
    Q_OBJECT;
    Q_PROPERTY(QColor _colour READ colour WRITE setColour 
            NOTIFY colourChanged);

public:
    ARGBSetterWidget(int red = 0, int green = 0, int blue = 0, int alpha = 255,
            QWidget* parent = 0);
    QColor colour() const { return _colour; }

private:
    QColor _colour;         // current in-use color, from last button click
    HexSpinBox* colorSetters[4];   // ARGB HexSpinBoxes

signals:
    void colourChanged(const QColor& newColor) const;
    void pendingChanged(const QColor& newPendingColor) const;

private slots:
    void setColour(const QColor& newThe_color);
    void updateButtonColour();

};/*}}}*/

