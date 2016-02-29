/*
 * File   : Editor.cxx
 * Program: icon editor in its own window with controls - source file
 * Purpose: just a practice program
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Notes  : This one will be more elaborate, with a color setter
 * Created: 02/15/2016
 * Updated: 02/28/2016
 */

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <QKeyEvent>

#include "Editor.hxx"
#include "Scroller.cxx"


Editor::Editor(QWidget* parent, Qt::WindowFlags f)/*{{{*/
        : QDialog(parent, f)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Create and beautify heading/*{{{*/
    QLabel* heading = new QLabel(QLabel::tr("Create an Icon"));
    QFont* heading_font = new QFont(heading->font());
    heading_font->setBold(true);
    heading_font->setUnderline(true);
    heading_font->setFamily(QString("Courier"));
    heading_font->setPointSize(16);
    heading->setFont(*heading_font);
    heading->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
/*}}}*/
    scroller = new Scroller();

    setters = new ARGBSetterWidget();/*{{{*/
    connect(setters, SIGNAL(colourChanged(const QColor&)),
            scroller->iconViewGrid, SLOT(setPenColor(const QColor&)));
/*}}}*/

    // add zoom bar/*{{{*/
    zoomer = new Zoomer;
    connect(zoomer, SIGNAL(zooming(int)),
            scroller->iconViewGrid, SLOT(setZoomFactor(int)));
    zoomer->setZoom(zoomer->defaultZoom);
/*}}}*/
    // Add widgets to the layouts/*{{{*/
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* splitLayout = new QHBoxLayout;
    mainLayout->addWidget(heading);
    mainLayout->addWidget(zoomer);
    mainLayout->addLayout(splitLayout);
    splitLayout->addWidget(scroller);
    splitLayout->addWidget(setters);
/*}}}*/
    // Apply additional positioning/*{{{*/
    mainLayout->setAlignment(heading, Qt::AlignHCenter);
    mainLayout->setAlignment(zoomer, Qt::AlignHCenter);
/*}}}*/
    setLayout(mainLayout);

}
/*}}}*/
bool Editor::writeFile(const QString& fileName)/*{{{*/
{
    if (!scroller->iconViewGrid->iconImage().save(fileName))
    {
        QMessageBox::warning(this, tr("Icon Creator"),
                tr("Unable to write file %1.").arg(fileName));
        return false;
    }
    else
        return true;
}
/*}}}*/
bool Editor::loadFile(const QString& fileName)/*{{{*/
{
    QImage newImage(fileName);
    if (newImage.isNull())
    {
        QMessageBox::warning(this, tr("Icon Creator"),
                tr("Unable to open file %1.").arg(fileName));
        return false;
    }
    else
    {
        scroller->iconViewGrid->setIconImage(newImage);
        return true;
    }
}
/*}}}*/
