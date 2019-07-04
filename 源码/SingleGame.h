#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "Board.h"
#include "Step.h"


class SingleGame : public Board
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);
    ~SingleGame();

    int _level;

    virtual void click(int id,int row,int col);
    Step* getBestMove();
    void getAllPossibleMove(QVector<Step*> &steps);
    void getAllPossibleMoveRed(QVector<Step*> &steps);

    void saveStep(int moveid, int killid, int row, int col,QVector<Step*> &steps);

    void fakeMove(Step* step);
    void unfakeMove(Step* step);

    int calcScore();
    int getMinScore(int level,int curMaxScore);
    int getMaxScore(int level,int curMinScore);

public slots:
    void computerMove();

};

#endif // SINGLEGAME_H
