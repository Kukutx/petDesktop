#ifndef PETCHARACTER_H
#define PETCHARACTER_H
#include "common.h"
class PetCharacter : public QObject
{
      Q_OBJECT
private:
      QWidget * widgetObj;          //窗口对象
public:
    PetCharacter(QWidget * widget);

    int dsx; //桌面的边缘
    int dsy;

//    QString music[10];  //存放音乐的播放路径
//    QMediaPlayer * player;
    QMenu *p_Menu; //右键弹出菜单
    QAction *p_Action1;
    QAction *p_Action2;
    ~PetCharacter();
};

#endif // PETCHARACTER_H
