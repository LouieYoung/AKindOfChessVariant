#include "singlegame.h"
#include <QTime>
#include <QTimer>
SingleGame::SingleGame(QWidget *parent) : Board(parent)
{
    _level = 5;
}

SingleGame::~SingleGame()
{

}

void SingleGame::click(int id,int row,int col)
{
    if(!this->_bRedTurn)
        return;

    Board::click(id,row,col);
    if(!this->_bRedTurn)
    {
        if(_s[31]._dead)
            return;
        //0.1秒定时器
        QTimer::singleShot(100,this,SLOT(computerMove()));

    }
}

void SingleGame::computerMove()
{
    //找最有利的走法
    Step* step = getBestMove();
    //走
    moveto(step->_moveid,step->_rowTo,step->_colTo,step->_killid);
    //销毁内存
    delete step;
    //更新界面
    update();
}
Step* SingleGame::getBestMove()
{

    //找到所有可能步骤
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    //尝试走并评估局面
    int maxScore = -100000;
    Step* ret=new Step;
    while(steps.count())
    {
        Step* step = steps.back();
        steps.removeLast();
        //假装走一步
        fakeMove(step);
        //简单算法评估局面
        //int score = calcScore();
        //最大值最小值算法评估局面，其中_level默认为5
        int score = getMinScore(_level-1,maxScore);
        //去除假装走的一步
        unfakeMove(step);
        //找最有利的一步
        if(score > maxScore)
        {
            maxScore = score;
            if(ret) delete ret;
            ret = step;
        }
        else
        {
            delete step;
        }
    }
    //返回最好的结果
    return ret;
}

//假装走一步
void SingleGame::fakeMove(Step* step)
{
    if(step->_killid==-1) return;
    _s[step->_killid]._dead = true;

    _s[step->_moveid]._row=step->_rowTo;
    _s[step->_moveid]._col=step->_colTo;
}
//解除假装
void SingleGame::unfakeMove(Step* step)
{
    if(step->_killid==-1) return;
    _s[step->_killid]._dead = false;
    _s[step->_moveid]._row=step->_rowFrom;
    _s[step->_moveid]._col=step->_colFrom;
}

//评价局面分
int SingleGame::calcScore()
{
    int redTotalScore = 0;
    int blackTotalScore = 0;
    //enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG,NO};
    static int chessScore[] = {300,200,100,50,25,20,10,0};

    //黑棋分的总数 - 红旗分的总数
    for(int i=0;i<16;++i)
    {
        if(_s[i]._dead) continue;
        redTotalScore += chessScore[_s[i]._type];
    }
    for(int i=16;i<32;++i)
    {
        if(_s[i]._dead) continue;
        blackTotalScore += chessScore[_s[i]._type];
    }
    if(_s[15]._dead){
        blackTotalScore += 10000;
    }
    if(_s[31]._dead){
        redTotalScore += 10000;
    }

    return blackTotalScore - redTotalScore;
}

int SingleGame::getMinScore(int level,int curMaxScore)
{
    if(level == 0)return calcScore();
    QVector<Step*> steps;
    getAllPossibleMoveRed(steps);//这里获取的是红棋的

    int minScore = 100000;
    while(steps.count())
    {
        Step* step = steps.back();
        steps.removeLast();
        fakeMove(step);
        int score = getMaxScore(level -1,minScore);
        unfakeMove(step);
        delete step;

        if(score<=curMaxScore)
        {
            while(steps.count())
            {
                Step* step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if(score < minScore)
        {
            minScore = score;
        }
    }
    return minScore;
}

int SingleGame::getMaxScore(int level,int curMinScore)
{
    if(level == 0)return calcScore();
    QVector<Step*> steps;
    getAllPossibleMoveRed(steps);//这里获取的是红棋的

    int maxScore = -100000;
    while(steps.count())
    {
        Step* step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMinScore(level-1,maxScore);
        unfakeMove(step);
        delete step;

        if(score>=curMinScore)
        {
            while(steps.count())
            {
                Step* step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if(score > maxScore)
        {
            maxScore = score;
        }
    }
    return maxScore;
}




void SingleGame::getAllPossibleMove(QVector<Step*> &steps)
{

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    for(int i=31;i>15;i--)
    {
        if(_s[i]._dead) continue;
        for(int irow=0;irow<9;++irow)
        {
            int row=qrand()%9;

            for(int icol=0;icol<9;icol++)
            {
                int col=qrand()%9;
                int killid = this->getStoneId(row,col);
                if(canMove(i,row,col,killid))
                {
                    saveStep(i,killid,row,col,steps);
                }
            }
        }
    }

}

void SingleGame::getAllPossibleMoveRed(QVector<Step*> &steps)
{

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    for(int i=15;i>-1;i--)
    {
        if(_s[i]._dead) continue;
        for(int irow=0;irow<9;++irow)
        {
            int row=qrand()%9;

            for(int icol=0;icol<9;icol++)
            {
                int col=qrand()%9;
                int killid = this->getStoneId(row,col);
                if(canMove(i,row,col,killid))
                {
                    saveStep(i,killid,row,col,steps);
                }
            }
        }
    }

}

void SingleGame::saveStep(int moveid, int killid, int row, int col,QVector<Step*> &steps)
{
    Step* step = new Step;

    step->_moveid = moveid;
    step->_killid = killid;
    step->_rowFrom = _s[moveid]._row;
    step->_colFrom = _s[moveid]._col;
    step->_rowTo = row;
    step->_colTo = col;



    steps.append(step);
}


