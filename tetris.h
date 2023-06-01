
#ifndef TETRIS_H
#define TETRIS_H

#include <cstdlib>
#include <ctime>
#include <QPainter>

const int MAXX = 15;
const int MAXY = 25;
const int NEXTMAXX = 6;
const int NEXTMAXY = 6;
const int WIDTH = 30;
const int HEIGHT = 30;
const int INTERVAL = 4;
const int  COUNT =  4;

struct Block
{
    int x [COUNT];
    int y [COUNT];
    int centerX;
    int centerY;
    int ID;
};


class Tetris
{
public:
    Tetris();
         void createBlock ();
         Block getNextBlock ();
         Block getBlock ();
         int getScore ();
         int getBox (int x, int y);
         bool rotate ();
         bool moveToLeft ();
         bool moveToRight ();
         bool moveToBottom ();
         bool isEnd ();
         void killLines ();
         void clear ();

         static int getWidth ();
         static int getHeight ();
         static int getNextWidth ();
         static int getNextHeight ();
         static void DrawRectangle(QPainter&, int x1, int y1, int width, int heigth, int id);
         static QColor chooseColor(int);



private:
         void createNextBlock ();
         bool move (int dx, int dy);
         void blockToBox ();
         bool isRotatable ();
         int getFirstFullLine ();

private:
         int score;
         Block block;
         Block nextBlock;
         int box [MAXX] [MAXY];
};

#endif // TETRIS_H
