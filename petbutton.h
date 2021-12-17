#ifndef PETBUTTON_H
#define PETBUTTON_H
#include "common.h"
#include <sstream>
#if defined(Q_OS_WIN)
#include <windows.h>
#endif
class PetButton :public QObject
{
    Q_OBJECT
private:
    QFontDatabase fontDb;         //读取字体包
    QFont iconFont;               //图标字体
    QImage image;                 //图片
    QString basename;             //路径名
    QWidget * widgetObj;          //窗口对象
public:
    PetButton(QWidget * widget);

    /*按钮定义*/
    //QPushButton *Nude=new QPushButton();
    QPushButton *msg=new QPushButton();
    QPushButton *about=new QPushButton();
    QPushButton *Exit=new QPushButton();
    QPushButton *SetWallpaper=new QPushButton();
    QPushButton *FullScreen=new QPushButton();

    /*点击事件*/
    void onMsgButton();                                     //消息
    void onAboutButton();                                   //关于
    void onExitButton();                                    //退出
    void onGrabFullScreen();                                //截图
    void onsetWallPaper();                                  //设置壁纸事件

    /*功能*/
    void setButtonIcon(QPushButton *btn,QChar iconID);      //设置按钮icon
    void setWallPaper(QString filePath);                    //设置壁纸
    /*待实现*/
    void showPushButton();
    void hidePushButton();
    ~PetButton();
};

#endif // PETBUTTON_H
