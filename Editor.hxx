/*
 * File   : Editor.hxx
 * Program: icon editor in its own window with controls - header file
 * Purpose: just a practice program
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Notes  : This one will be more elaborate, with a color setter
 * Created: 02/15/2016
 * Updated: 03/02/2016
 */

#ifndef EDITOR_HXX
#define EDITOR_HXX

#include <QDialog>
#include <QList>


#include "Scroller.hxx"
#include "ARGBSetterWidget.hxx"
#include "Zoomer.hxx"

class Editor : public QDialog
{
    Q_OBJECT;

public:
    Editor(QWidget* parent = 0, Qt::WindowFlags f = 0);

    Scroller* scroller;
    ARGBSetterWidget* setters;
    Zoomer* zoomer;
    bool writeFile(const QString& fileName);
    bool loadFile(const QString& fileName);
    void undoEdit();
    void redoEdit();

private:
    struct mod
    {
        const QPoint pos;
        const QColor before;
        const QColor after;
    };
    typedef QList<struct mod> edit;
    edit* curEdit;
    QList<edit> history;
    QList<edit>::Iterator historyIndex = history.begin();
    bool recording = false;

    const QColor _black = {0, 0, 0};
    const QColor _white = {255, 255, 255};
    const QPoint _origin = {0, 0};
    const shape_t* genModCircle(int radius);
    const shape_t* genModRing(int radius);
    const shape_t* genModSquare(int length);
    const shape_t* genModRectangle(int width,int height);
    const shape_t* genModLine(int length);

private slots:
    void newMod(const QPoint& pos, const QColor& before, const QColor& after);
    void startEdit();
    void stopEdit();

signals:
    void redoAvailable(bool available);
    void undoAvailable(bool available);

};

#endif // def EDITOR_HXX

