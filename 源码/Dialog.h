//Dialog.h
#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT
protected:
    QPushButton Btn1;   //对话框内按钮1
    QPushButton Btn2;   //对话框内按钮2
protected slots:
    void Btn1_Clicked();    //按钮1的槽
    void Btn2_Clicked();    //按钮2的槽
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
};

#endif // DIALOG_H
