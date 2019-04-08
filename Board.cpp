#include "Board.h"
#include <QPainter>
#include <QDebug>
#include <QSlider>
#include <QSpinBox>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
//棋盘的构造函数（初始化棋盘数据）
Board::Board(QWidget *parent) : QWidget(parent)
{
    _dz=false;
    go();

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //棋盘缩放滑块
    pSlider = new QSlider(this);
    pSlider->setStyleSheet("\
                           QSlider::groove:horizontal {\
                                   height: 6px;\
                                   border-radius: 3px;\
                                   background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(200, 129, 200), stop: 1.0 rgb(34, 23, 80));\
                           }\
                           QSlider::handle:horizontal {\
                                   width: 5px;\
                                   background: rgb(0, 160, 230);\
                                   margin: -10px 3px -10px 3px;\
                                   border-radius: 8px;\
                                   background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(0, 160, 230), stop: 1.0 rgb(172, 137, 244));\
                           }");

    pSlider->setOrientation(Qt::Horizontal);  // 水平方向
    pSlider->setMinimum(48);  // 最小值
    pSlider->setMaximum(108);  // 最大值
    pSlider->setSingleStep(10);  // 步长
    connect(pSlider, SIGNAL(valueChanged(int)), this, SLOT(change(int)));

    //悔棋按钮
    button1 = new QPushButton(this);
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(bm()));

    //重来按钮
    button2 = new QPushButton(this);
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(go()));
    //旋转按钮
    button3 = new QPushButton(this);
    connect(button3,SIGNAL(clicked(bool)),this,SLOT(dz()));
    //退出按钮
    button4 = new QPushButton(this);
    connect(button4,SIGNAL(clicked(bool)),this,SLOT(qt()));

    change(50);
}
void Board::change(int value)
{
    d=value;
    pSlider->setGeometry(10,-d/4,2*d,d/2);
    button1->setGeometry(QRect(10*d,7*d,d,d));
    button1->setFont(QFont("STKaiti", d/4, QFont::Normal));
    button1->setText(QString::fromLocal8Bit("悔棋"));
    button2->setGeometry(QRect(10*d,8*d,d,d));
    button2->setFont(QFont("STKaiti", d/4, QFont::Normal));
    button2->setText(QString::fromLocal8Bit("重来"));
    button3->setGeometry(QRect(11*d,7*d,d,d));
    button3->setFont(QFont("STKaiti", d/4, QFont::Normal));
    button3->setText(QString::fromLocal8Bit("兑子"));
    button4->setGeometry(QRect(11*d,8*d,d,d));
    button4->setFont(QFont("STKaiti", d/4, QFont::Normal));
    button4->setText(QString::fromLocal8Bit("退出"));
}

//退出
void Board::qt()
{
    close();
}
//兑子
void Board::dz()
{
    _dz=!_dz;
    int num=0;
    int kill=0;
    TYPE killType = NO;
    if(_dz)
    {
        for(int i=0;i<32;i++)
        {
            stone[i].push(_s[i]);
        }
        return;
    }
    else if(_bRedTurn)
    {
        for(int i=10;i<=14;i++)
        {
            if(_s[i]._select==true&&_s[i]._row==8)
            {
                _s[i]._dead=true;
                //棋子死后行列要置到棋盘外!!!
                _s[i]._row=100;
                _s[i]._col=100;
                num++;
                qDebug()<<num;
            }
        }
        switch(num)
        {
            case 0:
                for(int i=0;i<32;i++)
                {
                    _s[i]._select=false;
                }
                update();
                return;
            case 1:
                killType = BING;
                break;
            case 2:
                killType = PAO;
                break;
            case 3:
                killType = MA;
                break;
            case 4:
                killType = CHE;
                break;
        }
        if (killType ==BING)
        {
            for(int i=26;i<=30;i++)
            {
               if(_s[i]._select==true)
               {
                   _s[i]._dead=true;
                   //棋子死后行列要置到棋盘外!!!
                   _s[i]._row=100;
                   _s[i]._col=100;
                   kill+=1;
               }
            }
        }
        else if(killType == PAO)
        {
            for(int i=24;i<=25;i++)
            {
               if(_s[i]._select==true)
               {
                   _s[i]._dead=true;
                   //棋子死后行列要置到棋盘外!!!
                   _s[i]._row=100;
                   _s[i]._col=100;
                   kill+=1;
               }
            }
        }
        else if(killType== MA)
        {
            for(int i=18;i<=19;i++)
            {
               if(_s[i]._select==true)
               {
                   _s[i]._dead=true;
                   //棋子死后行列要置到棋盘外!!!
                   _s[i]._row=100;
                   _s[i]._col=100;
                   kill+=1;
               }
            }
        }
        else if(killType == CHE)
        {
            for(int i=16;i<=17;i++)
            {
               if(_s[i]._select==true)
               {
                   _s[i]._dead=true;
                   //棋子死后行列要置到棋盘外!!!
                   _s[i]._row=100;
                   _s[i]._col=100;
                   kill+=1;
               }
            }
        }
        for(int i=0;i<32;i++)
        {
            _s[i]._select=false;
        }
        if(kill==0)
        {
            if(stone->length()>0)
                {
                    _selectid=-1;
                    for(int i=0;i<32;i++)
                    {
                        _s[i]=stone[i].top();
                        _s[i]._select=false;
                        stone[i].pop();
                    }
                }
            _bRedTurn=!_bRedTurn;
            update();
            return;
        }
            _selectid=-1;
            _bRedTurn=!_bRedTurn;
            update();
            return;
    }
    else if(!_bRedTurn)
    {
        for(int i=26;i<31;i++)
        {
            if(_s[i]._select==true&&_s[i]._row==0)
            {
                _s[i]._dead=true;
                //棋子死后行列要置到棋盘外!!!
                _s[i]._row=100;
                _s[i]._col=100;
                num++;
                qDebug()<<num;
            }
        }
        switch(num)
        {
            case 0:
                for(int i=0;i<32;i++)
                {
                    _s[i]._select=false;
                }
                update();
                return;
            case 1:
                killType = BING;
                break;
            case 2:
                killType = PAO;
                break;
            case 3:
                killType = MA;
                break;
            case 4:
                killType = CHE;
                break;
        }
        if (killType ==BING)
        {
            for(int i=10;i<=14;i++)
            {
               if(_s[i]._select==true)
               {
                   _s[i]._dead=true;
                   //棋子死后行列要置到棋盘外!!!
                   _s[i]._row=100;
                   _s[i]._col=100;
                   kill+=1;
               }
            }
        }
        else if(killType == PAO)
        {
            for(int i=8;i<=9;i++)
            {
               if(_s[i]._select==true)
               {
                   _s[i]._dead=true;
                   //棋子死后行列要置到棋盘外!!!
                   _s[i]._row=100;
                   _s[i]._col=100;
                   kill+=1;
               }
            }
        }
        else if(killType == MA)
        {
            for(int i=2;i<=3;i++)
            {
               if(_s[i]._select==true)
               {
                   _s[i]._dead=true;
                   //棋子死后行列要置到棋盘外!!!
                   _s[i]._row=100;
                   _s[i]._col=100;
                   kill+=1;
               }
            }
        }
        else if(killType == CHE)
        {
            for(int i=0;i<=1;i++)
            {
               if(_s[i]._select==true)
               {
                   _s[i]._dead=true;
                   //棋子死后行列要置到棋盘外!!!
                   _s[i]._row=100;
                   _s[i]._col=100;
                   kill+=1;
               }
            }
        }
        for(int i=0;i<32;i++)
        {
            _s[i]._select=false;
        }
        if(kill==0)
        {
            if(stone->length()>0)
                {
                    _selectid=-1;
                    for(int i=0;i<32;i++)
                    {
                        _s[i]=stone[i].top();
                        _s[i]._select=false;
                        stone[i].pop();
                    }
                }
            _bRedTurn=!_bRedTurn;
            update();
            return;
        }
            _selectid=-1;
            _bRedTurn=!_bRedTurn;
            update();
            return;
    }
}
//底线兵数量
int Board::num_of_DXB(bool _bRedTurn)
{
    int num = 0;
    if(_bRedTurn)
    {
        for(int i=10;i<15;i++)
        {
            if(_s[i]._row==8)
            {
                num++;
            }
        }
    }
    else
    {
        for(int i=26;i<31;i++)
        {
            if(_s[i]._row==0)
            {
                num++;
            }
        }
    }
    return num;

}
//初始化
void Board::go()
{

    while(!stone->isEmpty())
    {
        stone->pop();
    }
    for(int i=0;i<32;i++)
    {
        _s[i].init(i);
    }
    _selectid=-1;
    _bRedTurn=true;
    _state=PLAYING;
    update();
}

void Board::bm()
{
    backMove();
    _bRedTurn=!_bRedTurn;
    for(int i;i<32;i++)
    {
        _s[i]._select=false;
    }
    _selectid=-1;
    _state=PLAYING;
    update();
}
//画
void Board::paintEvent(QPaintEvent *)
{



    setMinimumHeight(10*d);
    setMinimumWidth(13*d);
    setMaximumHeight(10*d);
    setMaximumWidth(13*d);

     _r=d/2;

    QPainter painter(this);




    //画棋盘边框
    painter.setPen(QPen(QColor(105, 105, 105), 1));
    for(int i =d/12;i<d/6;i++)
    {
        painter.drawLine(QPoint(d-i,d-i),QPoint(9*d+i,d-i));
        painter.drawLine(QPoint(d-i,9*d+i),QPoint(9*d+i,9*d+i));
        painter.drawLine(QPoint(d-i,d-i),QPoint(d-i,9*d+i));
        painter.drawLine(QPoint(9*d+i,d-i),QPoint(9*d+i,9*d+i));
    }
    //画格子

    //画9条横线
    for(int i=1;i<=9;i++)
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    //画9条竖线
    for(int i=1;i<=9;i++)
    {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,9*d));

    }
    //防走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    //画九宫格
    painter.drawLine(QPoint(4*d,4*d),QPoint(6*d,6*d));
    painter.drawLine(QPoint(4*d,6*d),QPoint(6*d,4*d));

    if(_dz)
    {
        painter.drawRect(11*d,7*d,d,d);
    }

    //绘制32颗棋子
    for(int i=0;i<32;i++)
    {
        drawStone(painter,i);
    }

    //绘制棋局转态
    drawState(painter);

    //绘制开发者信息
    //QRect rect = QRect(10*d,d,2*d,d);
    //painter.setFont(QFont("STKaiti", d/5, QFont::Normal));
    //painter.drawText(rect,QString::fromLocal8Bit("开发者の微博：""@如意羊_贾伯斯"),QTextOption(Qt::AlignCenter));
}

void Board::drawStone(QPainter& painter,int id)
{
    //先判断一下棋子死没死 如果死了就不画出来了
    if(_s[id]._dead)
        return;
    QPoint c = center(id);


    QRect rect = QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);
    //防走样
    //painter.setRenderHint(QPainter::Antialiasing, true);
    //确定棋子底色
    if((id == _selectid||_s[id]._select==true)&&_state==PLAYING)
        painter.setBrush(QBrush(QColor(255, 255, 50, 255)));
    else
        painter.setBrush(QBrush(QColor(254, 212, 83, 255)));
    //画棋子
    if(_s[id]._red)
    {
        painter.setPen(QPen(QColor(178, 34, 34, 255),1.8));
        painter.drawEllipse(c,_r-1,_r-1);
        painter.setPen(QPen(QColor(178, 34, 34, 255),1));
        painter.drawEllipse(c,_r-4,_r-4);
    }
    else
    {
        painter.setPen(QPen(QColor(50, 50, 50, 255),1.8));
        painter.drawEllipse(c,_r-1,_r-1);
        painter.setPen(QPen(QColor(50, 50, 50, 255),1));
        painter.drawEllipse(c,_r-4,_r-4);
    }
    //改变字体
    painter.setFont(QFont("STKaiti", d/2, QFont::Normal));
    //写棋名
//    if(_s[id]._red)
//    {
//        painter.translate(c);
//        painter.rotate(180);
//        painter.translate(-c);
//        painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
//        painter.resetMatrix();
//    }
//    else
//    {
        painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
//    }
}

void Board::drawState(QPainter& painter)
{
    state();
    QRect rect = QRect(10*d,4*d,2*d,2*d);
    //确定底色
    painter.setBrush(QBrush(QColor(150, 150, 150, 255)));
    //确定状态颜色
    switch(_state)
    {
        case PLAYING:
            painter.setPen(QPen(QColor(105, 105, 105),3));
            break;
        case HE:
            painter.setPen(QPen(QColor(254, 212, 83, 255),3));
            break;
        case HONG:
            painter.setPen(QPen(QColor(178, 34, 34, 255),3));
            break;
        case HEI:
            painter.setPen(QPen(QColor(50, 50, 50, 255),3));
            break;
    }
    painter.drawEllipse(10*d,4*d,2*d,2*d);
    //改变字体大小
    painter.setFont(QFont("STKaiti", 4*d/9, QFont::Normal));
    //写对局状态
    painter.drawText(rect,getState(),QTextOption(Qt::AlignCenter));
}
//输入行列坐标 返回像素坐标
QPoint Board::center(int row,int col)
{
    QPoint ret;
    ret.rx()=(col+1)*_r*2;
    ret.ry()=(row+1)*_r*2;
    return ret;
}
//输入棋子的id 返回像素坐标
QPoint Board::center(int id)
{
    return center(_s[id]._row,_s[id]._col);
}

//鼠标释放回调函数
void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt = ev->pos();

    //将pt转化成象棋的行列值
    //判断行列值上有没有棋子
    int row,col;
    //确定鼠标点击的位置是否有棋子
    bool bClicked = getRowCol(pt,row,col);
    if(!bClicked)//点到棋子外
        return;

    int id=getStoneId(row,col);
    click(id,row,col);

}
void Board::mousePressEvent(QMouseEvent *ev)
{
    dp = ev->globalPos()-pos();
}

void Board::mouseMoveEvent(QMouseEvent *ev)
{
     this->move(ev->globalPos() - dp);

}
//传入鼠标点击的像素坐标返回鼠标点击的位置是否有棋子
bool Board::getRowCol(QPoint pt,int &row,int &col)
{
    for(row=0;row<=9;row++)
        for(col=0;col<=8;col++)
        {
            QPoint c = center(row,col);
            int dx = c.x() - pt.x();
            int dy = c.y() - pt.y();
            int dist = dx*dx + dy*dy;
            if(dist<_r*_r)
                return true;
        }
    return false;
}

bool Board::canMove(int moveid, int row, int col, int killid)
{
    if(killid==-1||!_s[moveid]._red==_s[killid]._red)
    {
        if(canMove0(moveid,row,col,killid))
        {
            switch(_s[moveid]._type)
            {
            case Stone::JIANG:
                return canMove1(moveid,row,col,killid);
            case Stone::SHI:
                return canMove2(moveid,row,col,killid);
            case Stone::XIANG:
                return canMove3(moveid,row,col,killid);
            case Stone::CHE:
                return canMove4(moveid,row,col,killid);
            case Stone::MA:
                return canMove5(moveid,row,col,killid);
            case Stone::PAO:
                return canMove6(moveid,row,col,killid);
            case Stone::BING:
                return canMove7(moveid,row,col,killid);
            default: break;
            }
        }
        else
            return false;
    }

    if(_s[moveid]._red==_s[killid]._red/*killid超出下标范围值_red的值为false*/)
    {
        /*换选择*/
        _s[_selectid]._select=false;
        _s[killid]._select=true;
        _selectid=killid;
        update();
        return false;
    }
    return true;
}

bool Board::canMove0(int moveid,int row,int col,int killid)
{
    //判断对局转态
    if(_state!=PLAYING)return false;


    //判断有无牵将
    if(killid==15)
    {
        for(int i=0;i<15;i++)
        {

            switch(_s[i]._type)
            {
            case Stone::SHI:
                if(canMove2(i,row,col,killid))return false;
                break;
            case Stone::XIANG:
                if(canMove3(i,row,col,killid))return false;
                break;
            case Stone::CHE:
                if(canMove4(i,row,col,killid))return false;
                break;
            case Stone::MA:
                if(canMove5(i,row,col,killid))return false;
                break;
            case Stone::PAO:
                if(canMove6(i,row,col,killid))return false;
                break;
            case Stone::BING:
                if(canMove7(i,row,col,killid))return false;
                break;
            default: break;
            }
        }
    }
    else if(killid==31)
    {
        for(int i=16;i<31;i++)
        {
            switch(_s[i]._type)
            {
            case Stone::SHI:
                if(canMove2(i,row,col,killid))return false;
                break;
            case Stone::XIANG:
                if(canMove3(i,row,col,killid))return false;
                break;
            case Stone::CHE:
                if(canMove4(i,row,col,killid))return false;
                break;
            case Stone::MA:
                if(canMove5(i,row,col,killid))return false;
                break;
            case Stone::PAO:
                if(canMove6(i,row,col,killid))return false;
                break;
            case Stone::BING:
                if(canMove7(i,row,col,killid))return false;
                break;
            default: break;
            }
        }
    }
    return true;
}


bool Board::canMove1(int moveid,int row,int col,int killid)
{
    /*
        将的行走规则:
        1.只能在九宫内行走
        2.移动的步长是一个格子
    */

    int flag_buchang=0;

    if(col<3) return false;
    if(col>5) return false;

    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);
    if(d==1||d==10)
        flag_buchang=1;

    //在田字格里面走
    if(row<=5&&row>=3&&flag_buchang==1) return true;

    return false;
}

bool Board::canMove2(int moveid,int row,int col,int killid)
{
    /*士的走棋规则
        1.走斜线
        2.能过河
    */

    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);
    if(d==11)
        return true;

    return false;
}
bool Board::canMove3(int moveid,int row,int col,int killid)
{
    /*象的走棋规则:
        1.走田字格
        2.不能过河
        3.考虑别象眼
    */

    /******走田字格******/
    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int medium_r=(_s[moveid]._row+row)/2;
    int medium_c=(_s[moveid]._col+col)/2;
    if(abs(dc)==2&&abs(dr)==2)
        /*别象眼检验*/
        if(beStone(medium_r,medium_c)==false)
            return true;
    /******走田字格******/
    return false;
}
bool Board::canMove4(int moveid,int row,int col,int killid)
{
    /*车只能直着走*/
    if(num_of_Stone(moveid,row,col)==0)
        return true;

    return false;
}
bool Board::canMove5(int moveid,int row,int col,int killid)
{
    /*马的走棋规则:
        1.走日字格
        2.考虑别马腿
     */
    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);
    int medium_r=(_s[moveid]._row+row)/2;
    int medium_c=(_s[moveid]._col+col)/2;
    if(d==21||d==12)
    {
        if(abs(dr)==2)
        {
            if(beStone(medium_r,_s[moveid]._col)==false)
                return true;
        }
        else
        {
            if(beStone(_s[moveid]._row,medium_c)==false)
                return true;
        }
    }
    return false;
}
bool Board::canMove6(int moveid,int row,int col,int killid)
{
    /*炮的走棋规则*/
    if(num_of_Stone(moveid,row,col)==1&&killid!=-1||(num_of_Stone(moveid,row,col)==0&&killid==-1))
        return true;

    return false;
}
bool Board::canMove7(int moveid,int row,int col,int killid)
{
    /*兵的走棋规则*/
    int dr=_s[moveid]._row-row;
    int dc=_s[moveid]._col-col;
    int d=abs(dr)*10+abs(dc);

    if(_s[moveid]._red) //红棋
    {
        if(d==10||d==1)
        {
            if(dr==1)   //竖着走
                return false;  //竖着走走了回头路就要返回错误
            else      //横着走
                return true;
        }
        else
            return false;
    }
    else              //黑棋
    {
        if(d==10||d==1)
        {
            if(dr==-1)
                return false;
            else
                return true;
        }
        else
            return false;
    }
}

/*确定某个行列位置上是否有棋子*/
bool Board::beStone(int row,int col)
{
    for(int i=0;i<32;i++)
        if(_s[i]._row==row&&_s[i]._col==col)
                return true;

    return false;
}
/*输入行列获取棋子id*/
int Board::getStoneId(int row,int col)
{
    for(int i=0;i<32;i++)
        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false)
            return i;
    return -1;
}
void Board::click(int id,int row,int col)
{

    if(_dz)
    {
        _s[id]._select=true;
        update();
    }
    else if(_selectid==-1)
    {
        if(id!=-1)
        {
            if(_bRedTurn==_s[id]._red)
            {
                _selectid=id;
                _s[id]._select=true;
            }
            update();
        }
    }
    else
    {
        if(canMove(_selectid,row,col,id))
        {
            //走之前先入栈
            for(int i=0;i<32;i++)
            {

                stone[i].push(_s[i]);
                //qDebug()<<stone[i].top()._id<<stone[i].top()._row<<stone[i].top()._col;
            }
            /*走棋*/
            _s[_selectid]._row=row;
            _s[_selectid]._col=col;

            if(id!=-1)
            {
                _s[id]._dead=true;
                //棋子死后行列要置到棋盘外!!!
                _s[id]._row=100;
                _s[id]._col=100;
            }

            //判断是否自己断气
            qi();

            _s[_selectid]._select=false;
            _selectid=-1;
            _bRedTurn=!_bRedTurn;
            update();
        }
    }
}
int Board::num_of_Stone(int moveid,int row,int col)
{
    int i;
    int sum=0;
    if(_s[moveid]._row==row)
    {
        if(col-_s[moveid]._col>0)
            for(i=_s[moveid]._col+1;i<col;i++)
            {
                if(beStone(_s[moveid]._row,i)==true)
                    sum++;
            }
        else
            for(i=_s[moveid]._col-1;i>col;i--)
            {
                if(beStone(_s[moveid]._row,i)==true)
                    sum++;
            }
        return sum;
    }
    else if(_s[moveid]._col==col)
    {
        if(row-_s[moveid]._row>0)
            for(i=_s[moveid]._row+1;i<row;i++)
            {
                if(beStone(i,_s[moveid]._col)==true)
                    sum++;
            }
        else
            for(i=_s[moveid]._row-1;i>row;i--)
            {
                if(beStone(i,_s[moveid]._col)==true)
                    sum++;
            }
        return sum;
    }
    //两个棋子不在一条直线上
    return -1;
}

void Board::state()
{


    if(num_of_DXB(!_bRedTurn)==5&&_bRedTurn)
    {
        _state=HEI;
    }
    else if(num_of_DXB(!_bRedTurn)==5&&!_bRedTurn)
    {
        _state=HONG;
    }

    if(_s[15]._dead)_state=HEI;
    else if(_s[31]._dead)_state=HONG;
}

QString Board::getState()
{
    switch(_state)
    {
        case PLAYING:
            return QString::fromLocal8Bit("对局中" );
        case HE:
            return QString::fromLocal8Bit("和棋");
        case HONG:
            return QString::fromLocal8Bit("红方胜");
        case HEI:
            return QString::fromLocal8Bit("黑方胜");
    }
    return QString::fromLocal8Bit("对局状态错误");
}

void Board::qi()
{
    if(beStone(_s[15]._row-1,_s[15]._col)&&beStone(_s[15]._row+1,_s[15]._col)&&beStone(_s[15]._row,_s[15]._col-1)&&beStone(_s[15]._row,_s[15]._col+1))
        _s[15]._qi=false;
    else
        _s[15]._qi=true;

    if(beStone(_s[31]._row-1,_s[31]._col)&&beStone(_s[31]._row+1,_s[31]._col)&&beStone(_s[31]._row,_s[31]._col-1)&&beStone(_s[31]._row,_s[31]._col+1))
        _s[31]._qi=false;
    else
        _s[31]._qi=true;

    if(_bRedTurn&&!_s[15]._qi)
    {
        backMove();
        _bRedTurn=!_bRedTurn;
    }

    if(!_bRedTurn&&!_s[31]._qi)
    {
        backMove();
        _bRedTurn=!_bRedTurn;
    }
}

void Board::backMove()
{
    if(_dz)
    {
        return;
    }
    else if(stone->length()==0)
    {
        go();
    }
    else if(stone->length()>0)
    {
        _selectid=-1;
        for(int i=0;i<32;i++)
        {
            _s[i]=stone[i].top();
            _s[i]._select=false;
            stone[i].pop();
        }
    }
}










