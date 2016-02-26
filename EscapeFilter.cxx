/*
 * File   : EscapeFilter.hxx
 * Program: simple_pickets
 * Purpose: filters the escape key on all widgets to ensure consistent behavior
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Created: 02/26/2016
 * Updated: 02/26/2016
 */

#include <QKeyEvent>

#include "EscapeFilter.hxx"

bool EscapeFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (obj) {}     // avoids unused variable warnings
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Escape)
        {
            emit escapeKeyPressed();
            return true;
        }
    }
    return false;
}

