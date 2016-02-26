/*
 * File   : MainWindow.hxx
 * Program: Editor
 * Purpose: Create and edit icons - main window
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Created: 02/21/2016
 * Updated: 02/26/2016
 */

#include <QMainWindow>

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
    void undo() {}
    void redo() {}
    void toggleGrid() {}
    void about() {}
    bool modified();
    void iconModified();
    void close();
    void escapeSlot();

private:
    void createActions();
    void createMenus();
    void filterEscape();
    bool okToContinue();

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* optionsMenu;
    QMenu* helpMenu;

    QAction* newFileAction;
    QAction* openFileAction;
    QAction* saveFileAction;
    QAction* saveasFileAction;
    QAction* exitAction;

    QAction* undoAction;
    QAction* redoAction;

    QAction* toggleGridAction;

    QAction* aboutAction;

    Editor* editor;
    QString curFile;
    EscapeFilter* escapeFilter;
};

