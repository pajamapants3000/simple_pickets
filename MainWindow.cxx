/*
 * File   : MainWindow.hxx
 * Program: MainWindow
 * Purpose: Create and edit icons - this is the main window
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Created: 02/21/2016
 * Updated: 02/25/2016
 */

#include <QAction>
#include <QMenuBar>
#include <QFileDialog>


#include "MainWindow.hxx"

MainWindow::MainWindow()
{

    editor = new Editor();
    editor->setAttribute(Qt::WA_DeleteOnClose, true);
    setCentralWidget(editor);

    createActions();
    createMenus();

    setWindowIcon(QIcon(":/images/main.png"));
    setAttribute(Qt::WA_DeleteOnClose);

}

void MainWindow::createActions()/*{{{*/
{
    newFileAction = new QAction(tr("&New"), this);
    newFileAction->setIcon(QIcon(":/images/newFile.png"));
    newFileAction->setShortcut(QKeySequence::New);
    newFileAction->setStatusTip(tr("Start a new icon"));
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openFileAction = new QAction(tr("&Open"), this);
    openFileAction->setIcon(QIcon(":/images/openFile.png"));
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open a previously saved icon"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveFileAction = new QAction(tr("&Save"), this);
    saveFileAction->setIcon(QIcon(":/images/saveFile.png"));
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save icon"));
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveasFileAction = new QAction(tr("&Saveas"), this);
    saveasFileAction->setIcon(QIcon(":/images/saveasFile.png"));
    saveasFileAction->setShortcut(QKeySequence::SaveAs);
    saveasFileAction->setStatusTip(tr("Save icon as new file"));
    connect(saveasFileAction, SIGNAL(triggered()), this, SLOT(saveasFile()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setIcon(QIcon(":/images/exit.png"));
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the program"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    undoAction = new QAction(tr("&Undo"), this);
    undoAction->setIcon(QIcon(":/images/undo.png"));
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip(tr("Undo last change"));
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

    redoAction = new QAction(tr("&Redo"), this);
    redoAction->setIcon(QIcon(":/images/redo.png"));
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip(tr("Redo last undo"));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));

    toggleGridAction = new QAction(tr("&ToggleGrid"), this);
    toggleGridAction->setShortcut(tr("Ctrl+T"));
    toggleGridAction->setStatusTip(tr("Toggle gridlines"));
    connect(toggleGridAction, SIGNAL(triggered()), this, SLOT(toggleGrid()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setIcon(QIcon(":/images/about.png"));
    aboutAction->setStatusTip(tr("About this program"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

}
/*}}}*/
void MainWindow::createMenus()/*{{{*/
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveasFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    menuBar()->addSeparator();
    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(toggleGridAction);

    menuBar()->addSeparator();
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);

}
/*}}}*/
bool MainWindow::modified()/*{{{*/
{
    return true;
}
/*}}}*/
void MainWindow::newFile()/*{{{*/
{
    if (okToContinue())
    {
        curFile = QString();
        QImage* image = new QImage(16, 16, QImage::Format_ARGB32);
        image->fill(qRgba(0, 0, 0, 0));
        editor->scroller->iconViewGrid->setIconImage(*image);
    }
}
/*}}}*/
bool MainWindow::openFile()/*{{{*/
{
    if (okToContinue())
    {
        QString dir("/media/Sync/google_drive-otripleg/Code/C++/Qt4");
        dir += "/Blanchette_and_Summerfield/Part_I/Chapter_05/icon_editor";
        dir += "/IconEditorDialog++/saves";
            QString fileName = QFileDialog::getOpenFileName(this,
                QString(tr("Open Icon File")), dir, tr("Icons (*.png *.ico)"));
        if (!fileName.isEmpty())
            return editor->loadFile(fileName);
        else
            return false;
    }

    else
        return false;
}
/*}}}*/
bool MainWindow::saveFile()/*{{{*/
{
    if (curFile.isEmpty())
        return saveasFile();
    return editor->writeFile(curFile);
}
/*}}}*/
bool MainWindow::saveasFile()/*{{{*/
{
    QString dir("/media/Sync/google_drive-otripleg/Code/C++/Qt4");
    dir += "Blanchette_and_Summerfield/Part_I/Chapter_05/icon_editor/IconEditorDialog++/saves";

    QString fileName = QFileDialog::getSaveFileName(this,
            QString(tr("Save Icon File")), dir, tr("Icons (*.png *.ico)"));

    if (!fileName.isEmpty())
    {
        curFile = fileName;
        return editor->writeFile(fileName);
    }
    else
        return false;
}
/*}}}*/
bool MainWindow::okToContinue()/*{{{*/
{
    return true;
}
/*}}}*/
// do we still need this with the QMainWindow?
/*
bool MainWindow::event(QEvent* event)
{
    if (event->type() == QEvent::ChildRemoved)  // child closed
    {
        close();                                // so close everything
        return true;
    }
    else
        return QWidget::event(event);
}
*/
