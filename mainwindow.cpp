#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <cmath>
#include <vector>
#include <QMessageBox>

int const chess_size = 16;
int const space = 20;
int const blanking = 50;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    game(new Game)
{
    game->start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for (int i = 0;i < chess_size;i++) {
        painter.drawLine(20+50*i,20,20+50*i,20+50*(chess_size-1));
        painter.drawLine(20,20+50*i,20+50*(chess_size-1),20+50*i);
    }
    for (int i = 0;i < chess_size;i++) {
        for(int j = 0;j< chess_size;j++){
           vector<unsigned long>::size_type i1 = static_cast<vector<unsigned long>::size_type>(i);
           vector<unsigned long>::size_type j1 = static_cast<vector<unsigned long>::size_type>(j);
            if (game->map[i1][j1] == -1){
                painter.setBrush(Qt::white);
                painter.setPen(Qt::black);
                painter.drawEllipse(20+blanking*i-20,20+blanking*j-20,40,40);
            }
            if (game->map[i1][j1] == 1){
                painter.setBrush(Qt::black);
                painter.setPen(Qt::white);
                painter.drawEllipse(20+blanking*i-20,20+blanking*j-20,40,40);
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{

    int x = e->x();
    int y = e->y();
    double relativeX = (x - space) * 1.0/ blanking;
    double relativeY = (y - space) * 1.0/ blanking;
    auto &map = game->map;
    vector<unsigned long>::size_type X = static_cast<vector<unsigned long>::size_type>(round(relativeX));
    vector<unsigned long>::size_type Y = static_cast<vector<unsigned long>::size_type>(round(relativeY));
    if (chess_size <= X || chess_size <= Y){
        return;
    }
    if (game->flag == true){
        if(map[X][Y] == 0){
            map[X][Y] = -1;
            game->flag = !game->flag;
        }
    }
    else{
        if(map[X][Y] == 0){
            map[X][Y] = 1;
            game->flag = !game->flag;
        }
    }
    update();
    checkGame(X,Y);
}

void MainWindow::checkGame(int x, int y)
{
    game->isWins = game->isWin(x,y);
    if (game->isWins){
        game->isWins = false;
        if(game->flag){
            QMessageBox::information(this,"对话框","黑色方win",QMessageBox::Ok);
        }else{
            QMessageBox::information(this,"对话框","白色方win",QMessageBox::Ok);
        }
        game->start();
    }
    if(game->isDraw()){
        QMessageBox::information(this,"对话框","平局",QMessageBox::Ok);
        QMessageBox::information(this,"对话框","是否开始下一局",QMessageBox::Ok);
        game->start();
    }
}

