/*
 * File   : Editor.hxx
 * Program: icon editor in its own window with controls - header file
 * Purpose: just a practice program
 * Author : Tommy Lincoln <pajamapants3000@gmail.com>
 * License: MIT
 * Notes  : This one will be more elaborate, with a color setter
 * Created: 02/15/2016
 * Updated: 03/03/2016
 */

#ifndef EDITOR_HXX
#define EDITOR_HXX

#include <QDialog>
#include <QList>


#include "Scroller.hxx"
#include "ARGBSetterWidget.hxx"
//#include "Zoomer.hxx"

enum brushShape { Ellipse, Ring, Rectangle, Block };

class Editor : public QDialog
{
    Q_OBJECT;

public:
    Editor(QWidget* parent = 0, Qt::WindowFlags f = 0);

    Scroller* scroller;
    ARGBSetterWidget* setters;
    bool writeFile(const QString& fileName);
    bool loadFile(const QString& fileName);
    void undoEdit();
    void redoEdit();
    enum brushShape shape() const { return curBrushShape; }

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
    const shape_t* genEllipse(int x, int y);
    const shape_t* genRing(int x, int y);
    const shape_t* genRectangle(int x, int y);
    const shape_t* genBlock(int x, int y);
    enum brushShape curBrushShape;
    int curBrushX;
    int curBrushY;

public slots:
    void setBrushShape(enum brushShape newBrushShape);
    void setBrushX(int newBrushX);
    void setBrushY(int newBrushY);

private slots:
    void newMod(const QPoint& pos, const QColor& before, const QColor& after);
    void startEdit();
    void stopEdit();
    void setBrush(int x, int y, enum brushShape shape = Block);

signals:
    void redoAvailable(bool available) const;
    void undoAvailable(bool available) const;

};

#endif // def EDITOR_HXX

