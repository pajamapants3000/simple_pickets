/*
 * File   : MainWindow.hxx
 * Program: Editor
 * Purpose: Create and edit icons - main window
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Created: 02/21/2016
 * Updated: 03/03/2016
 */

#include <QMainWindow>
#include <QCloseEvent>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QToolBar>

#include "Editor.hxx"
#include "EscapeFilter.hxx"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow();

private slots:
    void newFile();
    bool openFile();
    bool saveFile();
    bool saveasFile();
    void undo() { editor->undoEdit(); }
    void redo() { editor->redoEdit(); }
    void about() {}
    bool modified();
    void iconModified();
    void escapeSlot();
    bool getDimensions();
    void ellipseBrush();
    void ringBrush();
    void rectangleBrush();
    void blockBrush();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void filterEscape();
    bool okToContinue();
    void updateBrush();

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* optionsMenu;
    QMenu* helpMenu;

    QToolBar* toolBar;

    QAction* newFileAction;
    QAction* openFileAction;
    QAction* saveFileAction;
    QAction* saveasFileAction;
    QAction* exitAction;

    QAction* undoAction;
    QAction* redoAction;

    QAction* toggleGridAction;
    QAction* togglePreviewBrush;

    QAction* aboutAction;

    QAction* ellipseBrushAction;
    QAction* ringBrushAction;
    QAction* rectangleBrushAction;
    QAction* blockBrushAction;

    Editor* editor;
    QString curFile;
    EscapeFilter* escapeFilter;
    QSize dimensions;
};

