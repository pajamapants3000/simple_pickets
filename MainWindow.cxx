/*
 * File   : MainWindow.hxx
 * Program: MainWindow
 * Purpose: Create and edit icons - this is the main window
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Created: 02/21/2016
 * Updated: 03/05/2016
 * TODO: Organize functions, slots, etc.
 */

#include <QMessageBox>

#include "MainWindow.hxx"
#include "SizeDialog.hxx"
#include "BrushSizer.hxx"
#include "Zoomer.hxx"



MainWindow::MainWindow()/*{{{*/
{

    editor = new Editor();
    setCentralWidget(editor);

    createActions();
    createMenus();
    createToolBars();

    setWindowIcon(QIcon(":/images/main.png"));
    setWindowTitle(QString("[untitled][*] | Simple Pickets"));
    setAttribute(Qt::WA_DeleteOnClose);

    connect(editor->scroller->iconViewGrid,
            SIGNAL(modified(const QPoint&, const QColor&, const QColor&)),
            this, SLOT(iconModified()));
    connect(editor, SIGNAL(undoAvailable(bool)),
            undoAction, SLOT(setEnabled(bool)));
    connect(editor, SIGNAL(redoAvailable(bool)),
            redoAction, SLOT(setEnabled(bool)));

    filterEscape();
}
/*}}}*/
void MainWindow::filterEscape()/*{{{*/
{
    escapeFilter = new EscapeFilter;
    editor->installEventFilter(escapeFilter);
    editor->setters->installEventFilter(escapeFilter);
    for (int i = 0; i < 4; ++i)
    {
        editor->setters->colorSetters[i]->installEventFilter(escapeFilter);
    }
    connect(escapeFilter, SIGNAL(escapeKeyPressed()),
            this, SLOT(escapeSlot()));
}
/*}}}*/
void MainWindow::escapeSlot()/*{{{*/
{
    // Insert desired action later!
}
/*}}}*/
void MainWindow::createActions()/*{{{*/
{
    // menu actions/*{{{*/
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

    clearAction = new QAction(tr("C&lear"), this);
    clearAction->setIcon(QIcon(":/images/clear.png"));
    clearAction->setShortcut(tr("Ctrl+L"));
    clearAction->setStatusTip(tr("Clear the image"));
    connect(clearAction, SIGNAL(triggered()),
            editor->scroller->iconViewGrid, SLOT(clearScreen()));

    undoAction = new QAction(tr("&Undo"), this);
    undoAction->setIcon(QIcon(":/images/undo.png"));
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip(tr("Undo last change"));
    undoAction->setEnabled(false);
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

    redoAction = new QAction(tr("&Redo"), this);
    redoAction->setIcon(QIcon(":/images/redo.png"));
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip(tr("Redo last undo"));
    redoAction->setEnabled(false);
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));

    toggleGridAction = new QAction(tr("&ToggleGrid"), this);
    toggleGridAction->setShortcut(tr("Ctrl+T"));
    toggleGridAction->setStatusTip(tr("Toggle gridlines"));
    connect(toggleGridAction, SIGNAL(triggered()),
            editor->scroller->iconViewGrid, SLOT(toggleGrid()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setIcon(QIcon(":/images/about.png"));
    aboutAction->setStatusTip(tr("About this program"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
/*}}}*/
    // toolbar actions/*{{{*/
    ellipseBrushAction = new QAction(tr("&EllipseBrush"), this);
    ellipseBrushAction->setIcon(QIcon(":/images/ellipse.png"));
    ellipseBrushAction->setStatusTip(tr("Use filled-in ellipse brush"));
    connect(ellipseBrushAction, SIGNAL(triggered()),
            editor->scroller->iconViewGrid->brush(), SLOT(ellipseBrush()));

    ringBrushAction = new QAction(tr("&RingBrush"), this);
    ringBrushAction->setIcon(QIcon(":/images/ring.png"));
    ringBrushAction->setStatusTip(tr("Use ring brush"));
    connect(ringBrushAction, SIGNAL(triggered()),
            editor->scroller->iconViewGrid->brush(), SLOT(ringBrush()));

    rectangleBrushAction = new QAction(tr("&RectangleBrush"), this);
    rectangleBrushAction->setIcon(QIcon(":/images/rectangle.png"));
    rectangleBrushAction->setStatusTip(tr("Use rectangle brush"));
    connect(rectangleBrushAction, SIGNAL(triggered()),
            editor->scroller->iconViewGrid->brush(), SLOT(rectangleBrush()));

    blockBrushAction = new QAction(tr("&BlockBrush"), this);
    blockBrushAction->setIcon(QIcon(":/images/block.png"));
    blockBrushAction->setStatusTip(tr("Use block brush"));
    connect(blockBrushAction, SIGNAL(triggered()),
            editor->scroller->iconViewGrid->brush(), SLOT(blockBrush()));
/*}}}*/

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
    editMenu->addAction(clearAction);
    editMenu->addSeparator();
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
void MainWindow::createToolBars()/*{{{*/
{
    toolBar = addToolBar(tr("ToolBar"));

    BrushSizer* brushSizer = new BrushSizer;
    connect(brushSizer, SIGNAL(brushXChanged(int)),
            editor->scroller->iconViewGrid->brush(), SLOT(setBrushX(int)));
    connect(brushSizer, SIGNAL(brushYChanged(int)),
            editor->scroller->iconViewGrid->brush(), SLOT(setBrushY(int)));
    brushSizer->setBrushX(0);
    brushSizer->setBrushY(0);
    editor->scroller->iconViewGrid->brush()->setBrushX(0);
    editor->scroller->iconViewGrid->brush()->setBrushY(0);

    Zoomer* zoomer = new Zoomer;
    connect(zoomer, SIGNAL(zooming(int)),
            editor->scroller->iconViewGrid, SLOT(setZoomFactor(int)));
    zoomer->setZoom(zoomer->defaultZoom);

    toolBar->addAction(ringBrushAction);
    toolBar->addAction(ellipseBrushAction);
    toolBar->addAction(rectangleBrushAction);
    toolBar->addAction(blockBrushAction);
    toolBar->addSeparator();
    toolBar->addWidget(brushSizer);
    toolBar->addSeparator();
    toolBar->addWidget(zoomer);

}
/*}}}*/
bool MainWindow::modified()/*{{{*/
{
    return isWindowModified();
}
/*}}}*/
void MainWindow::iconModified()/*{{{*/
{
    setWindowModified(true);
}/*}}}*/
void MainWindow::newFile()/*{{{*/
{
    if (okToContinue() && getDimensions())
    {
        editor->newImage(dimensions);
        curFile = QString();
        setWindowModified(false);
        setWindowTitle(QString("[untitled][*] | Simple Pickets"));
    }
}
/*}}}*/
bool MainWindow::openFile()/*{{{*/
{
    if (okToContinue())
    {
        QString dir("/media/Sync/google_drive-otripleg/Code/C++/Qt4");
        dir += "/Blanchette_and_Summerfield/Part_I/Chapter_05/icon_editor";
        dir += "/simple_pickets/saves";
            QString fileName = QFileDialog::getOpenFileName(this,
                QString(tr("Open Icon File")), dir, tr("Icons (*.png *.ico)"));
        if (!fileName.isEmpty())
        {
            curFile = fileName;
            if (editor->loadFile(fileName))
            {
                setWindowModified(false);
                setWindowTitle(curFile + "[*] | Simple Pickets");
                return true;
            }
            else
                return false;
        }
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
    if (editor->writeFile(curFile))
    {
        setWindowModified(false);
        return true;
    }
    else
        return false;
}
/*}}}*/
bool MainWindow::saveasFile()/*{{{*/
{
    QString dir("/media/Sync/google_drive-otripleg/Code/C++/Qt4");
    dir += "Blanchette_and_Summerfield/Part_I/Chapter_05/icon_editor";
    dir += "/simple_pickets/saves";
    QString fileName = QFileDialog::getSaveFileName(this,
            QString(tr("Save Icon File")), dir, tr("Icons (*.png *.ico)"));

    if (fileName.isEmpty())
        return false;
    curFile = fileName;
    if (saveFile())
    {
        setWindowModified(false);
        setWindowTitle(curFile + "[*] | Simple Pickets");
        return true;
    }
    else
        return false;
}
/*}}}*/
bool MainWindow::okToContinue()/*{{{*/
{
    if (isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("Spreadsheet"),
                        tr("The document has been modified.\n"
                           "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::No
                                         | QMessageBox::Cancel);
        if (r == QMessageBox::Yes)
            return saveFile();
        else if (r == QMessageBox::Cancel)
            return false;
    }
    return true;
}
/*}}}*/
bool MainWindow::getDimensions()/*{{{*/
{
    SizeDialog dialog(dimensions);
    return dialog.exec();
}
/*}}}*/
void MainWindow::closeEvent(QCloseEvent* event)/*{{{*/
{
    if (!okToContinue())
        event->ignore();
}
/*}}}*/
