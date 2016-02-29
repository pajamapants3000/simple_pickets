/*
 * File   : SizeDialog.hxx
 * Program: simple_pickets
 * Purpose: prompts for size dimensions when starting new icon - implementation
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT; See LICENSE
 * Created: 02/29/2016
 * Updated: 02/29/2016
 * TODO: Add checkbox for syncing x and y; later maybe add a ratio box.
 */

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

#include "SizeDialog.hxx"

SizeDialog::SizeDialog(QSize& size)
{
    setModal(true);
    validator = new QIntValidator(1, 128);

    result = &size;

    // create and connect buttons for confirming or cancelling/*{{{*/
    QPushButton* button_ok = new QPushButton(tr("Ok"));
    connect(button_ok, SIGNAL(clicked()), this, SLOT(accept()));
    QPushButton* button_cancel = new QPushButton(tr("Cancel"));
    connect(button_cancel, SIGNAL(clicked()), this, SLOT(reject()));
/*}}}*/
    // create edit boxes/*{{{*/
    QString dim_x_str;
    QLineEdit* dim_x_entry = new QLineEdit(dim_x_str);
    connect(dim_x_entry, SIGNAL(textChanged(const QString&)),
            this, SLOT(dim_x_update(const QString&)));
    QString dim_y_str;
    QLineEdit* dim_y_entry = new QLineEdit(dim_y_str);
    connect(dim_y_entry, SIGNAL(textChanged(const QString&)),
            this, SLOT(dim_y_update(const QString&)));
/*}}}*/
    // create and customize label for heading/*{{{*/
    QLabel* heading = new QLabel(tr("Set size for new icon"));
    QFont* heading_font = new QFont(heading->font());
    heading_font->setBold(true);
    heading_font->setUnderline(true);
    heading_font->setFamily(QString("Courier"));
    heading_font->setPointSize(16);
    heading->setFont(*heading_font);
    heading->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
/*}}}*/
    // create other labels for form/*{{{*/
    QLabel* dim_x_units = new QLabel(tr("pixels"));
    QLabel* dim_x_label = new QLabel(tr("&Width:"));
    dim_x_label->setBuddy(dim_x_entry);
    QLabel* dim_y_units = new QLabel(tr("pixels"));
    QLabel* dim_y_label = new QLabel(tr("&Height:"));
    dim_y_label->setBuddy(dim_y_entry);
/*}}}*/
    // create layout
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(heading, 1, 1, 1, 5, Qt::AlignHCenter);
    layout->addWidget(dim_x_label, 2, 1, 1, 2, Qt::AlignLeft);
    layout->addWidget(dim_x_entry, 2, 3, 1, 2, Qt::AlignRight);
    layout->addWidget(dim_x_units, 2, 5, 1, 1, Qt::AlignLeft);
    layout->addWidget(dim_y_label, 3, 1, 1, 2, Qt::AlignLeft);
    layout->addWidget(dim_y_entry, 3, 3, 1, 2, Qt::AlignRight);
    layout->addWidget(dim_y_units, 3, 5, 1, 1, Qt::AlignLeft);
    layout->addWidget(button_ok, 4, 2, 1, 1, Qt::AlignCenter);
    layout->addWidget(button_cancel, 4, 4, 1, 1, Qt::AlignCenter);
    setLayout(layout);

}

void SizeDialog::dim_x_update(const QString& newWidthString)/*{{{*/
{
    result->setWidth(newWidthString.toInt());
}
/*}}}*/
void SizeDialog::dim_y_update(const QString& newHeightString)/*{{{*/
{
    result->setHeight(newHeightString.toInt());
}
/*}}}*/
