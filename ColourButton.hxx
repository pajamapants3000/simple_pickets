/*
 * File   : ColourButton.hxx
 * Program: Written for ARGBSetterWidget
 * Purpose: A QPushButton subclass with changeable background color
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Notes  : Code is all here, no additional source (.cxx) file.
 * Created: 02/17/2016
 * Updated: 02/23/2016
 */

#include <QPushButton>

class ColourButton : public QPushButton/*{{{*/
{
    Q_OBJECT;
    Q_PROPERTY(QColor _colour READ Colour WRITE setColour NOTIFY colourChanged);


public:
    ColourButton(const QString& text = QString("Select"),
            const QColor& colourIni = QColor("whitesmoke"),
            QWidget* parent = 0);
    QColor Colour() const { return _colour; }

private:
    QColor _colour;
    void setColour(QColor newColor);

signals:
    void clicked(const QColor& curColour) const;
    void colourChanged(const QColor& newColour) const;

public slots:
    void updateColour(QColor newColor) { setColour(newColor); }

private slots:
    void clickedSendColour() const { emit clicked(_colour); }

};/*}}}*/

