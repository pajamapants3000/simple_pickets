/*
 * File   : MainWindow.hxx
 * Program: Editor
 * Purpose: Create and edit icons - main window
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Created: 02/21/2016
 * Updated: 02/25/2016
 */

#include <QMainWindow>
#include <QEvent>

#include "Editor.hxx"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow();

private:
    // reimplement QWidget::event() to close when any child closes.
    bool event(QEvent* event);

private slots:
    void newFile();
    bool openFile();
    bool saveFile();
    bool saveasFile();
    bool modified();
    void iconModified();

private:
    void createActions();
    void createMenus();
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
};

