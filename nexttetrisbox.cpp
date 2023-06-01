
#include "nexttetrisbox.h"
#include "tetris.h"

NextTetrisBox::NextTetrisBox(QWidget *parent) : QWidget(parent)
{
    for (int i = 0; i < 4; i++)
    {
        nextBlock.x[i] = -1;
        nextBlock.y[i] = -1;
    }
    nextBlock.centerX = -1;
    nextBlock.centerY = -1;
    nextBlock.ID = 0;
    int w = Tetris::getNextWidth();
    int h = Tetris::getNextHeight();
    setFixedSize(w, h);
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
}


void NextTetrisBox::updateNextTetris(Tetris tetris)
{
    nextBlock = tetris.getNextBlock();
    for (int i = 0; i < 4; i++)
    {
        nextBlock.x[i] -= RESTX;
        nextBlock.y[i] += RESTY;
    }
    repaint();
}


void NextTetrisBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255, 255, 255));
    painter.setPen(pen);
    painter.setBrush(brush);

    for (int i = 0; i < 4; i++)
    {
        int x = nextBlock.x[i];
        int y = nextBlock.y[i];
        int x1 = x * WIDTH + x * INTERVAL;
        int y1 = y * HEIGHT + y * INTERVAL;
        Tetris::DrawRectangle(painter, x1, y1, WIDTH, HEIGHT, nextBlock.ID);
    }
}
