#ifndef WIDGET_H
#define WIDGET_H
#include "common.h"
#include"petbutton.h"
#include "petcharacter.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void mouseMoveEvent(QMouseEvent*event);        //移动
    void mousePressEvent(QMouseEvent *event);      //点击
    void mouseReleaseEvent(QMouseEvent *event);    //释放
    bool eventFilter(QObject *watched, QEvent *event);   //事件过滤
private:
    //读取json配置
    QString strContext;
    QJsonArray subArray;
    void ReadJsonDoc(QString path);

    /*未实现功能*/
    QWidget *newwidget=new QWidget();   //创建新窗口

    /*鼠标相关的*/
    bool isHover;
    QPoint screenPos;// 屏幕上的点

    /*桌面精灵*/
    QTextEdit *m_textedit=new QTextEdit();   //内容框
    QLabel *pet=new QLabel();                 //宠物
    PetButton *petButton=new PetButton(this); //按钮
    PetCharacter* petCharacter=new PetCharacter(this);

    //系统托盘
    QPushButton *Minumized=new QPushButton();
    QSystemTrayIcon *systemTrayIcon = new QSystemTrayIcon(this); //新建QSystemTrayIcon对象
    QMenu *m_menu = new QMenu(this);
    QAction *m_action1 = new QAction(QIcon("://res/other/half_star.png"), tr("显示"), m_menu);
    QAction *m_action2 = new QAction(QIcon("://res/other/star.png"), tr("关于"), m_menu);
    QAction *m_action3 = new QAction(QIcon("://res/other/close.png"), tr("退出"), m_menu);



public slots:
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason);   //激活托盘
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H


