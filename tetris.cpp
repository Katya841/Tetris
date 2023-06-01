#include "tetris.h"
#include <QDebug>

Tetris::Tetris()
{
    srand(unsigned(time(NULL)));
    score = 0;
    for (int i = 0; i < MAXX; i++)
    {
        for (int j = 0; j < MAXY; j++)
        {
            box[i][j] = 0;
        }
    }
    for (int i = 0; i < COUNT; i++)
    {
        block.x[i] = -1;
        block.y[i] = -1;
    }
    block.centerX = -1;
    block.centerY = -1;
    block.ID = 0;
    createNextBlock();

}

void Tetris::createBlock()
{

    for (int i = 0; i < COUNT; i++)
    {
        block.x[i] = nextBlock.x[i];
        block.y[i] = nextBlock.y[i];
    }
    block.centerX = nextBlock.centerX;
    block.centerY = nextBlock.centerY;
    block.ID = nextBlock.ID;
    createNextBlock();
}

Block Tetris::getNextBlock()
{
    return nextBlock;
}

Block Tetris::getBlock()
{
    return block;
}

int Tetris::getScore()
{
    return score;
}

int Tetris::getBox(int x, int y)
{
    return box[x][y];
}

bool Tetris::rotate()
{
    if (isRotatable())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tetris::moveToLeft()
{
    if (move(-1, 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tetris::moveToRight()
{
    if (move(1, 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tetris::moveToBottom()
{
    if (!move(0, 1))
    {
        blockToBox ();
        killLines ();
        if(isEnd())
        {
            return false;
        }
        else
        {
            createBlock();
        }
    }
    return true;
}

bool Tetris::isEnd()
{
    int j = 0;
    for (int i = 0; i < MAXX; i++)
    {
        if (box[i][j] >= 1)
        {
            return true;
        }
    }
    return false;
}

void Tetris::killLines()
{
    int count = 0;
    int temp = 0;
    while ((temp = getFirstFullLine()) != -1)
    {
        for (int j = temp; j >0; j--)
        {
            for (int i = 0; i < MAXX; i++)
            {
                box[i][j] = box[i][j-1];
            }
        }
        count++;
    }
    score += count;
}

void Tetris::clear()
{
    score = 0;
    srand(unsigned(time(NULL)));
    for (int i = 0; i < MAXX; i++)
    {
        for (int j = 0; j < MAXY; j++)
        {
            box[i][j] = 0;
        }
    }
    for (int i = 0; i < COUNT; i++)
    {
        block.x[i] = -1;
        block.y[i] = -1;
    }
    block.centerX = -1;
    block.centerY = -1;
    block.ID = 0;
    createNextBlock();
}

int Tetris::getWidth()
{
    return MAXX * WIDTH + (MAXX - 1) * INTERVAL;
}

int Tetris::getHeight()
{
    return MAXY * HEIGHT + (MAXY - 1) * INTERVAL;
}

int Tetris::getNextWidth()
{
    return NEXTMAXX * WIDTH + (NEXTMAXX - 1) * INTERVAL;
}

int Tetris::getNextHeight()
{
    return NEXTMAXY * WIDTH + (NEXTMAXY - 1) * INTERVAL;
}

void Tetris::DrawRectangle(QPainter& painter, int x1, int y1, int width, int height, int id)
{
    QPen pen;
    QBrush brush;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    auto color = chooseColor(id);
    brush.setColor(color);
    painter.setBrush(brush);
    painter.drawRect(x1, y1, width, height);
}

QColor Tetris::chooseColor(int id)
{
    QColor color = Qt::green;
    switch(id) {
    case 1:
        color = Qt::white;
        break;
    case 2:
        color = Qt::yellow;
        break;
    case 3:
        color = Qt::green;
        break;
    case 4:
        color = Qt::red;
        break;
    case 5:
        color = Qt::blue;
        break;
    case 6:
        color = Qt::magenta;
        break;
    case 7:
        color = Qt::lightGray;
        break;

    }
    return color;
}

void Tetris::createNextBlock()
{
    int centerX = (MAXX-1) / 2;
    int ID = rand ()% 7;

    switch (ID)
    {
    case 0:
        //##
        //##
        nextBlock.x[0] = centerX;
        nextBlock.x[1] = centerX;
        nextBlock.x[2] = centerX + 1;
        nextBlock.x[3] = centerX + 1;
        nextBlock.y[0] = -2;
        nextBlock.y[1] = -1;
        nextBlock.y[2] = -2;
        nextBlock.y[3] = -1;
        nextBlock.centerX = 0;
        nextBlock.centerY = 0;
        nextBlock.ID = 1;
        break;
    case 1:
        //####
        //
        nextBlock.x[0] = centerX - 1;
        nextBlock.x[1] = centerX;
        nextBlock.x[2] = centerX + 1;
        nextBlock.x[3] = centerX + 2;
        nextBlock.y[0] = -1;
        nextBlock.y[1] = -1;
        nextBlock.y[2] = -1;
        nextBlock.y[3] = -1;
        nextBlock.centerX = centerX;
        nextBlock.centerY = -1;
        nextBlock.ID = 2;
        break;
    case 2:
        //##
        // ##
        nextBlock.x[0] = centerX - 1;
        nextBlock.x[1] = centerX;
        nextBlock.x[2] = centerX;
        nextBlock.x[3] = centerX + 1;
        nextBlock.y[0] = -2;
        nextBlock.y[1] = -2;
        nextBlock.y[2] = -1;
        nextBlock.y[3] = -1;
        nextBlock.centerX = centerX;
        nextBlock.centerY = -2;
        nextBlock.ID = 3;
        break;
    case 3:
        // ##
        //##
        nextBlock.x[0] = centerX;
        nextBlock.x[1] = centerX + 1;
        nextBlock.x[2] = centerX - 1;
        nextBlock.x[3] = centerX;
        nextBlock.y[0] = -2;
        nextBlock.y[1] = -2;
        nextBlock.y[2] = -1;
        nextBlock.y[3] = -1;
        nextBlock.centerX = centerX;
        nextBlock.centerY = -2;
        nextBlock.ID = 4;
        break;
    case 4:
        //#
        //###
        nextBlock.x[0] = centerX - 1;
        nextBlock.x[1] = centerX - 1;
        nextBlock.x[2] = centerX;
        nextBlock.x[3] = centerX + 1;
        nextBlock.y[0] = -2;
        nextBlock.y[1] = -1;
        nextBlock.y[2] = -1;
        nextBlock.y[3] = -1;
        nextBlock.centerX = centerX;
        nextBlock.centerY = -1;
        nextBlock.ID = 5;
        break;
    case 5:
        //  #
        //###
        nextBlock.x[0] = centerX + 1;
        nextBlock.x[1] = centerX - 1;
        nextBlock.x[2] = centerX;
        nextBlock.x[3] = centerX + 1;
        nextBlock.y[0] = -2;
        nextBlock.y[1] = -1;
        nextBlock.y[2] = -1;
        nextBlock.y[3] = -1;
        nextBlock.centerX = centerX;
        nextBlock.centerY = -1;
        nextBlock.ID = 6;
        break;
    case 6:
        // #
        //###
        nextBlock.x[0] = centerX;
        nextBlock.x[1] = centerX - 1;
        nextBlock.x[2] = centerX;
        nextBlock.x[3] = centerX + 1;
        nextBlock.y[0] = -2;
        nextBlock.y[1] = -1;
        nextBlock.y[2] = -1;
        nextBlock.y[3] = -1;
        nextBlock.centerX = centerX;
        nextBlock.centerY = -1;
        nextBlock.ID = 7;
        break;
    default:
        break;
    }
}


bool Tetris::move(int dx, int dy)
{
    int newX[COUNT];
    int newY[COUNT];
    int newCenterX;
    int newCenterY;
    for (int i = 0; i < COUNT; i++)
    {
        newX[i] = block.x[i] + dx;
        newY[i] = block.y[i] + dy;
        if (newX[i] < 0 || newX[i] >= MAXX)
        {
            return false;
        }
        if (newY[i] >=0 && newY[i] < MAXY)
        {
            if (box[newX[i]][newY[i]] >= 1)
            {
                return false;
            }
         }
        else if (newY[i] >= MAXY)
        {
            return false;
        }

    }
    newCenterX = block.centerX + dx;
    newCenterY = block.centerY + dy;
    for (int i = 0; i < COUNT; i++)
    {
        block.x[i] = newX[i];
        block.y[i] = newY[i];
    }
    block.centerX = newCenterX;
    block.centerY = newCenterY;

    return true;
}

bool Tetris::isRotatable()
{
    int newX[COUNT];
    int newY[COUNT];
    int newCenterX, newCenterY;

    if (block.ID == 0)
    {
        return false;
    }
    for (int i = 0; i < COUNT; i++)
    {
        int nx = block.x[i] - block.centerX;
        int ny = block.y[i] - block.centerY;
        newX[i] = nx * 0 + ny * (-1) + block.centerX;
        newY[i] = nx * 1 + ny * 0 + block.centerY;
        if (newX[i] < 0 || newX[i] >= MAXX || newY[i] < 0 || newY[i] >= MAXY)
        {
            return false;
        }

        if (box[newX[i]][newY[i]] >= 1)
        {
            return false;
        }
    }
    newCenterX = block.centerX;
    newCenterY = block.centerY;
    for (int i = 0; i < COUNT; i++)
    {
        block.x[i] = newX[i];
        block.y[i] = newY[i];
    }
    block.centerX = newCenterX;
    block.centerY = newCenterY;
    return true;
}

void Tetris::blockToBox()
{
    for (int i = 0; i < COUNT; i++)
    {
        int x = block.x[i];
        int y = block.y[i];
        if (y >= 0)
        {
            box[x][y] = block.ID;
        }
    }
}

int Tetris::getFirstFullLine()
{

    for (int j = 0; j < MAXY; j++)
    {
        bool flag = true;
        for (int i = 0; i < MAXX; i++)
        {
            if (box[i][j] == 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return j;
        }
    }
    return -1;
}
