#include <QApplication>
#include "Board.h"
#include "singlegame.h"
#include <QTextCodec>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include "ChooseDlg.h"
#include "Dialog.h"



int main(int argc,char* argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc,argv);
  Board *board = new Board;

 qDebug() << "Btn_Clicked()";
 Dialog d(board);
 int ret = d.exec();
 if (ret == Dialog::Accepted)
 {
     Board *board = new Board;
//     QGraphicsScene *scene = new QGraphicsScene;
//     QGraphicsProxyWidget *w = scene->addWidget(board);
//     w->setRotation(180);
//     QGraphicsView *view = new QGraphicsView(scene);
//     view->show();
//     qDebug() << "Accepted";
     board->setWindowTitle(QString::fromLocal8Bit("中宫象棋"));
     board->setWindowOpacity(0.95);
     board->show();
 }
 else if (ret == Dialog::Rejected)
 {
     SingleGame *board = new SingleGame;
//     QGraphicsScene *scene = new QGraphicsScene;
//     QGraphicsProxyWidget *w = scene->addWidget(board);
//     w->setRotation(180);
//     QGraphicsView *view = new QGraphicsView(scene);
//     view->show();
//     qDebug() << "Rejected";
     board->setWindowTitle(QString::fromLocal8Bit("中宫象棋"));
     board->setWindowOpacity(0.95);
     board->show();
 }





    return app.exec();

}
