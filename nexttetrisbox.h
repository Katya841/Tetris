#ifndef NEXTTETRISBOX_H
#define NEXTTETRISBOX_H

#include <QWidget>
#include <QWidget>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QColor>
#include "tetris.h"

 #define RESTX (MAXX-NEXTMAXX) / 2
 #define RESTY 4

class NextTetrisBox : public QWidget
{
    Q_OBJECT
public:
    explicit NextTetrisBox(QWidget *parent = nullptr);
         void updateNextTetris (Tetris tetris);
         void paintEvent (QPaintEvent * event);

private:
         Block nextBlock;

};

#endif // NEXTTETRISBOX_H
