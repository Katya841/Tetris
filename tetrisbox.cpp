#include "tetrisbox.h"

TetrisBox::TetrisBox(QWidget *parent) : QWidget(parent)
{
    block.centerX = -1;
    block.centerY = -1;
    block.ID = -1;
    for (int i = 0; i < 4; i++)
    {
        block.x[i] = -1;
        block.y[i] = -1;
    }


    for (int i = 0; i < MAXX; i++)
    {
        for (int j = 0; j < MAXY; j++)
        {
            box[i][j] = 0;
        }
    }
    int w = Tetris::getWidth();
    int h = Tetris::getHeight();
    setFixedSize(w, h);
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
}


void TetrisBox::updateTetris(Tetris tetris)
{
    block = tetris.getBlock();
    for (int i = 0; i < MAXX; i++)
    {
        for (int j = 0; j < MAXY; j++)
        {
            box[i][j] = tetris.getBox(i, j);
        }
    }
    repaint();
}

void TetrisBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    brush.setColor((QColor(255, 0, 0, 127)));
    painter.setPen(pen);
    painter.setBrush(brush);
    for (int i = 0; i < MAXX; i++)
    {
        for (int j = 0; j < MAXY; j++)
        {
            if (box[i][j] >= 1)
            {
                int x = i * WIDTH + i * INTERVAL;
                int y = j * HEIGHT + j * INTERVAL;
                Tetris::DrawRectangle(painter, x, y, WIDTH, HEIGHT, box[i][j]);
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int x = block.x[i];
        int y = block.y[i];
        int x1 = x * WIDTH + x * INTERVAL;
        int y1 = y * HEIGHT + y * INTERVAL;
        Tetris::DrawRectangle(painter, x1, y1, WIDTH, HEIGHT, block.ID);
    }
}
