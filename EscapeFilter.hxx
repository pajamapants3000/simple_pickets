/*
 * File   : EscapeFilter.hxx
 * Program: simple_pickets
 * Purpose: filters the escape key on all widgets to ensure consistent behavior
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Created: 02/26/2016
 * Updated: 02/26/2016
 */

#include <QObject>

class EscapeFilter : public QObject
{
    Q_OBJECT;
public:
    EscapeFilter() : QObject() {}
protected:
    bool eventFilter(QObject* obj, QEvent* event);
signals:
    void escapeKeyPressed();
};

