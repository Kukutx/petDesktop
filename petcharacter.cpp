#include "petcharacter.h"

PetCharacter::PetCharacter(QWidget * widget)
{
    //拿到主窗口对象
    widgetObj=widget;

    //创建弹出菜单对象
    p_Menu = new QMenu(widgetObj);
    //添加活动1
    p_Action1= new  QAction (p_Menu);
    p_Action1->setText("关于");   //设置文字
    p_Menu->addAction(p_Action1);  //action 添加到menu中
    //添加活动2
    p_Action2 = new  QAction (p_Menu);
    p_Action2->setText("退出");   //设置文字
    //pAction2->setIcon(QIcon("."));  //设置图标
    p_Menu->addAction(p_Action2);  //action 添加到menu中

    //关联事件响应函数，选择菜单中的action后·，触发槽函数执行
    connect(p_Action1, &QAction::triggered, this, [=]{
        QMessageBox message(QMessageBox::NoIcon,tr("关于"),tr("版本：嘤嘤嘤v0.1"));
        message.setIconPixmap(QPixmap("://res/pet/pic/idle/0000.png"));
        message.exec();
    });
    connect(p_Action2,&QAction::triggered,this,[=]{
        if ( !(QMessageBox::information(widgetObj,tr("退出"),tr("给爷爬"),tr("关闭"),tr("取消")))) exit(0);  //关闭
    });


}

PetCharacter::~PetCharacter()
{

}



