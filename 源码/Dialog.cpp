

#include "Dialog.h"

//Dialog类的构造函数，初始化列表指定两个按钮的父窗口都为Dialog
Dialog::Dialog(QWidget *parent) : QDialog(parent), Btn1(this), Btn2(this)
{
    //初始化按钮1
    Btn1.setText("人人对战");
    Btn1.move(20, 20);
    Btn1.resize(100, 30);

    //初始化按钮2
    Btn2.setText("人机对战");
    Btn2.move(140, 20);
    Btn2.resize(100, 30);

    //初始化对话框的大小以及设置其名字
    this->resize(260, 70);
    this->setWindowTitle("Dialog");

    //信号与槽的映射
    connect(&Btn1, SIGNAL(clicked()), this, SLOT(Btn1_Clicked()));
    connect(&Btn2, SIGNAL(clicked()), this, SLOT(Btn2_Clicked()));
}

Dialog::~Dialog()
{
}

//按钮1的槽
void Dialog::Btn1_Clicked()
{
    qDebug() << "Btn1_Clicked()";
    done(Accepted);
}

//按钮2的槽
void Dialog::Btn2_Clicked()
{
    qDebug() << "Btn2_Clicked()";
    done(Rejected);
}
