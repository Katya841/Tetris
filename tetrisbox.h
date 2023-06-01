#ifndef TETRISBOX_H
#define TETRISBOX_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QPen>
#include <QBrush>
#include <QColor>
#include "tetris.h"

class TetrisBox : public QWidget
{
    Q_OBJECT
public:
    explicit TetrisBox(QWidget *parent = nullptr);
         void updateTetris (Tetris tetris);
         void paintEvent (QPaintEvent * event);

private:
         Block block;
         int box [MAXX] [MAXY];
};
#endif // TETRISBOX_H
