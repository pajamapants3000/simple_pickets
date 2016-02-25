// hexspinbox.cxx
// Custom Qt Widget - HexSpinBox - implementation

#include "HexSpinBox.hxx"

HexSpinBox::HexSpinBox(const int& i_value, QWidget *parent) : QSpinBox(parent)
{
    setRange(0, 255);
    validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
    setValue(i_value);
    setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
}

QValidator::State HexSpinBox::validate(QString &text, int &pos) const
{
    return validator->validate(text, pos);
}

QString HexSpinBox::textFromValue(int value) const
{
    return QString::number(value, 16).toUpper();
}

int HexSpinBox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, 16);
}

void HexSpinBox::valueChangedToDec(const QString& boxValue) const
{

    bool ok = false;
    int decValue = boxValue.toInt(&ok, 16);
    const QString result = QString::number(decValue);

    emit decValueChanged(result);
}

