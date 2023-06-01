#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    status = STATUS_OFF;
    tetrisBox = new TetrisBox;
    nextTetrisBox = new NextTetrisBox;
    nextTetrisLabel = new QLabel(tr("NEXT"));
    controlLabel = new QLabel(tr("CONTROL:"));
    h_controlLabel = new QLabel(tr("H - START"));
    c_controlLabel = new QLabel(tr("C - RESTART"));
    m_controlLabel = new QLabel(tr("M - END GAME"));
    scoreTitleLabel = new QLabel(tr("SCORE:"));
    QFont font("Arial", 10, QFont::Cursive);
    nextTetrisLabel->setFont(font);
    controlLabel->setFont(font);
    h_controlLabel->setFont(font);
    c_controlLabel->setFont(font);
    m_controlLabel->setFont(font);
    scoreTitleLabel->setFont(font);
    scoreLabel = new QLabel(tr("0"));
    scoreLabel->setFont(font);
    Layout = new QGridLayout;

    Layout->setHorizontalSpacing(20);
    Layout->setVerticalSpacing(20);
    Layout->setAlignment(Qt::AlignCenter);

    Layout->addWidget(tetrisBox, 0, 0, 14, 1);
    Layout->addWidget(nextTetrisLabel, 0, 1);
    Layout->addWidget(nextTetrisBox, 1, 1, 1, 2);
    Layout->addWidget(controlLabel, 2, 1);
    Layout->addWidget(h_controlLabel, 3, 1);
    Layout->addWidget(c_controlLabel, 4, 1);
    Layout->addWidget(m_controlLabel, 5, 1);
    Layout->addWidget(scoreTitleLabel, 6, 1);
    Layout->addWidget(scoreLabel, 6, 2);



    QWidget *widget = new QWidget(this);
    widget->setLayout(Layout);
    setCentralWidget(widget);

    setPalette(Qt::gray);

    nextTetrisBox->updateNextTetris(tetris);
    setWindowTitle(tr("GAME OFF"));
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}
MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Up)
    {
        if (tetris.rotate())
        {
            if (status == STATUS_ON) {
                tetrisBox->updateTetris(tetris);
            }
        }
    }
    else if (event->key() == Qt::Key_Left)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToLeft())
            {
                tetrisBox->updateTetris(tetris);
            }
        }
    }
    else if (event->key() == Qt::Key_Down)
    {
        if (status == STATUS_ON) {
            if (tetris.moveToBottom())
            {
                tetrisBox->updateTetris(tetris);
                nextTetrisBox->updateNextTetris(tetris);
                updateScore();
            } else
            {
                timer->stop();
                QString str;
                str +=  QString("Game Over!\nYour Score is: %1!").arg(tetris.getScore());
                QMessageBox::information(this, tr("Game Over"), str);
                status = STATUS_END;
                setWindowTitle(tr("Game END"));
            }
        }
    }
    else if (event->key() == Qt::Key_Right)
    {
        if (status == STATUS_ON)
        {
            if (tetris.moveToRight())
            {
                tetrisBox->updateTetris(tetris);
            }
        }
    }
    else if (event->key() == Qt::Key_H)
    {
       if (status == STATUS_OFF)
        {

            tetris.createBlock();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            status = STATUS_ON;
            setWindowTitle(tr("Game ON"));
            timer->start(500);
        }
        else if (status == STATUS_END)
        {
            tetris.clear();
            tetris.createBlock();
            tetrisBox->updateTetris(tetris);
            nextTetrisBox->updateNextTetris(tetris);
            updateScore();
            status = STATUS_ON;
            setWindowTitle(tr("Game ON"));
            timer->start(500);
        }
    }
    else if (event->key() == Qt::Key_C)
    {
        timer->stop();
        tetris.clear();
        tetrisBox->updateTetris(tetris);
        nextTetrisBox->updateNextTetris(tetris);
        updateScore();
        status = STATUS_OFF;
        setWindowTitle(tr("Game OFF"));
    }
    else if (event->key() == Qt::Key_M)
    {
        close();
    }
}
void MainWindow::onTimer()
{
    if(tetris.moveToBottom())
    {
        tetrisBox->updateTetris(tetris);
        nextTetrisBox->updateNextTetris(tetris);
        updateScore();
    }
    else
    {
        timer->stop();
        QString str;
        str +=  QString("Game Over!\nYour Score is: %1!").arg(tetris.getScore());
        QMessageBox::information(this, tr("Game Over"), str);
        status = STATUS_END;
        setWindowTitle(tr("Game END"));
    }
}
void MainWindow::updateScore()
{
    QString str;
    int score = tetris.getScore();
    str = QString::number(score);
    scoreLabel->setText(str);
}
