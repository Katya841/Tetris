#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tetris.h"
#include "nexttetrisbox.h"
#include "tetrisbox.h"

#include <QMainWindow>
#include <QMainWindow>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QKeyEvent>
#include <QTimer>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>


 #define STATUS_ON 0
 #define STATUS_OFF 2
 #define STATUS_END 3

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
         void keyPressEvent(QKeyEvent *event);

         void updateScore();

public slots:
    void onTimer();

private:
         int status;
         Tetris tetris;
         QTimer *timer;
         TetrisBox *tetrisBox;
         NextTetrisBox *nextTetrisBox;
         QGridLayout *Layout;
         QLabel *nextTetrisLabel;
         QLabel *controlLabel;
         QLabel *h_controlLabel;
         QLabel *c_controlLabel;
         QLabel *m_controlLabel;
         QLabel *scoreTitleLabel;
         QLabel *scoreLabel;

};

#endif // MAINWINDOW_H
