#ifndef BOARD_H
#define BOARD_H

#include <QStack>
#include <QWidget>
#include "Stone.h"
#include <QMouseEvent>
#include <QSlider>
#include<QPushButton>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    enum STATE{PLAYING,HE,HEI,HONG};
    enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG,NO};


    QSlider *pSlider;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    bool _dz;
    //32颗棋子
    Stone _s[32];
    //棋盘大小
    int d;
    //棋子的像素半径
    int _r;
    //选中棋子的id
    int _selectid;
    //将帅四周有没有气
    int qir;
    int qib;
    //胜者即是正义
    STATE _state;
    int sta=0;
    //悔棋功能
    QStack <Stone> stone[32];
    QStack <Board> board;

    //该不该红棋走
    bool _bRedTurn;
    //输入行列获取棋子的id
    int getStoneId(int row,int col);
    //计算即将行走的棋子与某一坐标之间有几颗棋子
    int num_of_Stone(int moveid,int row,int col);
    //输入行列坐标判断该坐标上有没有棋子
    bool beStone(int row,int col);
    //底线兵数量
    int num_of_DXB(bool _bRedTurn);

    //能不能走的判断判断
    bool canMove(int moveid,int row,int col,int killid);
    //牵将和对局转态
    bool canMove0(int moveid,int row,int col,int killid);
    //判断将能不能走
    bool canMove1(int moveid,int row,int col,int killid);
    //判断士能不能走
    bool canMove2(int moveid,int row,int col,int killid);
    //判断象能不能走
    bool canMove3(int moveid,int row,int col,int killid);
    //判断车能不能走
    bool canMove4(int moveid,int row,int col,int killid);
    //判断马能不能走
    bool canMove5(int moveid,int row,int col,int killid);
    //判断炮能不能走
    bool canMove6(int moveid,int row,int col,int killid);
    //判断兵能不能走
    bool canMove7(int moveid,int row,int col,int killid);

    //输入行列坐标 返回像素坐标
    QPoint center(int row,int col);
    //输入棋子的id 返回像素坐标
    QPoint center(int id);

    //判断对局状态
    void state();
    //返回对局状态
    QString getState();

    void qi();


    bool getRowCol(QPoint pt,int &row,int &col);

    void drawStone(QPainter& painter,int id);
    void drawState(QPainter& painter);
    void paintEvent(QPaintEvent *event);

    //悔棋
    void backMove();

    //鼠标释放回调函数
    void mouseReleaseEvent(QMouseEvent *);
    QPoint dp;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    virtual void click(int id,int row,int col);



signals:

public slots:
        void change(int value);
        void bm();
        void go();
        void dz();
        void qt();
};

#endif // BOARD_H
