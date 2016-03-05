/*
 * File   : Editor.cxx
 * Program: icon editor in its own window with controls - source file
 * Purpose: just a practice program
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Notes  : This one will be more elaborate, with a color setter
 * Created: 02/15/2016
 * Updated: 03/05/2016
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
    scroller = new Scroller();/*{{{*/
    connect(scroller->iconViewGrid, SIGNAL(beginEdit()),
            this, SLOT(startRecord()));
    connect(scroller->iconViewGrid, SIGNAL(endEdit()),
            this, SLOT(stopRecord()));
    connect(scroller->iconViewGrid,
            SIGNAL(modified(const QPoint&, const QColor&, const QColor&)),
            this, SLOT(newMod(const QPoint&, const QColor&, const QColor&)));

/*}}}*/
    setters = new ARGBSetterWidget();/*{{{*/
    connect(setters, SIGNAL(colourChanged(const QColor&)),
            scroller->iconViewGrid, SLOT(setPenColor(const QColor&)));
/*}}}*/
    // Add widgets to the layouts/*{{{*/
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* splitLayout = new QHBoxLayout;
    mainLayout->addWidget(heading);
    mainLayout->addLayout(splitLayout);
    splitLayout->addWidget(scroller);
    splitLayout->addWidget(setters);
/*}}}*/
    // Apply additional positioning/*{{{*/
    mainLayout->setAlignment(heading, Qt::AlignHCenter);
/*}}}*/
    setLayout(mainLayout);

}
/*}}}*/
void Editor::newImage(QSize dimensions)/*{{{*/
{
    QImage* image = new QImage(dimensions, QImage::Format_ARGB32);
    image->fill(qRgba(0, 0, 0, 0));
    scroller->iconViewGrid->setIconImage(*image);
    // start undo history over
    history.clear();
    historyIndex = history.begin();
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
    // start undo history over
    history.clear();
    historyIndex = history.begin();
}
/*}}}*/
void Editor::newMod(const QPoint& pos,/*{{{*/
        const QColor& before, const QColor& after)
{
    if (recording)
    {
        struct mod new_mod = {pos, before, after};
        curEdit->push_back(new_mod);
    }
}
/*}}}*/
void Editor::startRecord()/*{{{*/
{
    curEdit = new edit;
    recording = true;
}
/*}}}*/
void Editor::stopRecord()/*{{{*/
{
    // Don't change history if nothing changed
    if (!curEdit->empty())
    {
        // New edit becomes most recent; lose all available redos
        if (historyIndex < history.end())
            history.erase(historyIndex, history.end());
        history.push_back(*curEdit);
        historyIndex = history.end();
        curEdit = 0;
        recording = false;
        emit redoAvailable(false);
        emit undoAvailable(true);
    }
}
/*}}}*/
void Editor::undoEdit()/*{{{*/
{
    if (historyIndex > history.begin())
    {
        --historyIndex;
        QList<struct mod>::ConstIterator citer =
                (*historyIndex).constBegin();
        do scroller->iconViewGrid->draw((*citer).pos, (*citer).before,
                &(scroller->iconViewGrid->simplePen));
        while (++citer != (*historyIndex).constEnd());
        emit redoAvailable(true);
    }
    if (historyIndex == history.begin())
        emit undoAvailable(false);
}
/*}}}*/
void Editor::redoEdit()/*{{{*/
{
    if (historyIndex < history.end())
    {
        QList<struct mod>::ConstIterator citer =
                (*historyIndex).constBegin();
        do scroller->iconViewGrid->draw((*citer).pos, (*citer).after,
                &(scroller->iconViewGrid->simplePen));
        while (++citer != (*historyIndex).constEnd());
        ++historyIndex;
        emit undoAvailable(true);
    }
    if (historyIndex == history.end())
        emit redoAvailable(false);
}
/*}}}*/
