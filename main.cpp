#include <QApplication>
#include "board.h"

int main(int argc,char* argv[])
{

    QApplication app(argc,argv);
    Board w;

    w.setWindowTitle(QString::fromLocal8Bit("中宫象棋"));

    w.setWindowOpacity(0.95);
    w.show();

    return app.exec();

}
