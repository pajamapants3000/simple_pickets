// hexspinbox.hxx
// Custom Qt Widget - HexSpinBox - header

#ifndef HEXSPINBOX_HXX
#define HEXSPINBOX_HXX

#include <QSpinBox>

class QRegExpValidator;

class HexSpinBox : public QSpinBox
{
    Q_OBJECT;
public:
    HexSpinBox(const int& i_value = 0, QWidget *parent = 0);

public slots:
    void valueChangedToDec(const QString&) const;

protected:
    QValidator::State validate(QString &text, int &pos) const;
    int valueFromText(const QString &text) const;
    QString textFromValue(int value) const;
signals:
    void decValueChanged(const QString& newValue) const;

private:
    QRegExpValidator *validator;
};

#endif

