/*
 * File   : main.cxx
 * Program: IconEditorDialog
 * Purpose: just a practice program
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Notes  : no save functionality yet; for the full, final program,
 *+        +see IconEditorDialog++ (needs a cool name!)
 * Created: 02/2016
 * Updated: 02/23/2016
 */

/*
 * So here's the plan: a heading at the top, a quitbutton at the bottom; in
 * the middle, on the left side is the icon editor, and on the right
 * side is a group box with 4 label/edit pairs for the ARGB values, plus a
 * box displaying a sample of the color currently set.
 */

#include <QApplication>

#include "MainWindow.hxx"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow* mainwin = new MainWindow;
    mainwin->show();
    return app.exec();
}

