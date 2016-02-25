/*
 * File   : ARGBSetterWidget.cxx
 * Program: IconEditorDialog
 * Purpose: A widget (QWidget subclass) that allows the user to set values
 *+for alhpa, red, green, and blue to produce a specific color; there is also
 *+a button that demonstrates the currently set color and allows the user to
 *+select it for use.
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Notes  : colourChanged signal carries the new color to be used when the
 *+user clicks the button
 * Created: 02/15/2016
 * Updated: 02/24/2016
 */

#include <QFormLayout>
#include <QLabel>

#include "ARGBSetterWidget.hxx"

ARGBSetterWidget::ARGBSetterWidget(int red, int green, int blue, int alpha,
        QWidget* parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QFormLayout* layout = new QFormLayout;
    layout->setLabelAlignment(Qt::AlignLeft);

    // Set up hexspinboxes for red, green, blue, and alpha values; constantly/*{{{*/
    //+keeps button colour updated with each change in value
    colorSetters[1] = new HexSpinBox(red);
    layout->addRow(tr("&Red:"), colorSetters[1]);
    colorSetters[2] = new HexSpinBox(green);
    layout->addRow(tr("&Green:"), colorSetters[2]);
    colorSetters[3] = new HexSpinBox(blue);
    layout->addRow(tr("&Blue:"), colorSetters[3]);
    colorSetters[0] = new HexSpinBox(alpha);
    layout->addRow(tr("&Alpha:"), colorSetters[0]);
    for (int i = 0; i < 4; ++i)
    {
        connect(colorSetters[i], SIGNAL(valueChanged(int)),
                this, SLOT(updateButtonColour()));
    }
/*}}}*/
    // Set up the button: shows the current color created from spinbox values;/*{{{*/
    //+clicking the button sends the current color to interested classes via
    //+the colourChanged signal (emitted by setColour);
    ColourButton* button = new ColourButton(tr("Select"), _colour);
    connect(button, SIGNAL(clicked(const QColor&)),
            this, SLOT(setColour(const QColor&)));
    connect(this, SIGNAL(pendingChanged(const QColor&)),
            button, SLOT(updateColour(const QColor&)));
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addRow(button);
    layout->setAlignment(button, Qt::AlignHCenter);
/*}}}*/

    updateButtonColour();
    setLayout(layout);
}

// Slots
void ARGBSetterWidget::updateButtonColour()/*{{{*/
{
    QColor newColor = QColor::fromRgb(colorSetters[1]->value(),
            colorSetters[2]->value(), colorSetters[3]->value(),
            colorSetters[0]->value());
    emit pendingChanged(newColor);
}
/*}}}*/
void ARGBSetterWidget::setColour(const QColor& newColor)/*{{{*/
{
    _colour = newColor;
    emit colourChanged(newColor);
}
/*}}}*/
