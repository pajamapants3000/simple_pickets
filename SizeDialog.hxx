/*
 * File   : SizeDialog.hxx
 * Program: simple_pickets
 * Purpose: prompts for size dimensions when starting new icon - header
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Created: 02/28/2016
 * Updated: 02/29/2016
 */

#ifndef SIZEDIALOG_HXX
#define SIZEDIALOG_HXX

#include <QDialog>
#include <QIntValidator>

class SizeDialog : public QDialog
{
    Q_OBJECT;

public:
    SizeDialog(QSize& size);

private:
    QSize* result;
    QIntValidator* validator;

private slots:
    void dim_x_update(const QString& newWidthString);
    void dim_y_update(const QString& newHeightString);
};

#endif  // def SIZEDIALOG_HXX

