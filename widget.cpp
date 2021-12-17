#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    /*主窗口*/
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);    // 去掉边框
    setFixedSize(320,360);                                 //设置窗口大小固定值，不可以调整
    setWindowModality(Qt::NonModal);
    setWindowIcon(QIcon("://res/girls/icon2.png"));  //窗口的图标
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //获取屏幕分辨率
    QRect rect = list_screen.at(0)->geometry();
//    petCharacter->dsx= rect.width();
//    petCharacter->dsy=rect.height();


    /*鼠标移动相关的*/
    isHover = false;
    screenPos = QPoint(0,0);

    /*宠物*/
    pet->setParent(this);
//    pet->setPixmap(QPixmap("://res/pet/bigbreast.gif"));
//    pet->move(50,90);
//    pet->setMaximumSize(220,270);
    QMovie *movie = new QMovie("://res/pet/bigbreast.gif");        //动图对象，添加gif
    movie->setScaledSize(QSize(275,250));                          //设置缩放大小
    pet->setMovie(movie);                                         //设置动图
    pet->move(0,110);//设置动图
    movie->start();                                                //动态激活
    pet->setMinimumSize(110,135);
    pet->setScaledContents(true);
    pet->installEventFilter(this);                    

    /*内容框*/
    m_textedit->setParent(this);
    m_textedit->move(10,0);
    m_textedit->resize(300,80);
    m_textedit->setReadOnly(true);
    m_textedit->setObjectName("m_textedit");
    m_textedit->setStyleSheet("#m_textedit{border: 2px solid #FFDEAD;border-radius:5px;background: #EEFF99;}");
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this); //设置具体阴影
    shadow_effect->setOffset(0, 0); //设置阴影距离
    shadow_effect->setColor(QColor(38, 78, 119, 127)); //设置阴影颜色
    shadow_effect->setBlurRadius(15); //设置阴影圆角
    m_textedit->setGraphicsEffect(shadow_effect);  //为部件设置阴影
    m_textedit->hide();
    ReadJsonDoc(QDir::currentPath()+"/petContext.json");//读取json内容配置文件

    /*系统托盘*/
    Minumized->setParent(this);
    Minumized->move(this->pos().x() + 270 ,this->pos().y() + 270); //设置按你的坐标位置
    petButton->setButtonIcon(Minumized,0xe6e1);
    systemTrayIcon->setIcon(QIcon("://res/girls/icon.png")); //将icon设到QSystemTrayIcon托盘对象中
    systemTrayIcon->setToolTip(QObject::trUtf8("嘤嘤嘤"));//当鼠标移动到托盘上的图标时，显示的内容
    systemTrayIcon->show(); //在系统托盘显示此对象
    m_menu->addAction(m_action1);
    m_menu->addAction(m_action2);
    m_menu->addAction(m_action3);

    /*托盘菜单样式以后再看*/
    //    m_menu->setStyleSheet(  "QMenu {"
    //                            " background-color : rgb(253,253,254);"
    //                            " padding:5px;"
    //                            " border-radius:15px;"
    //                            "}"
    //                            "QMenu::item {"
    //                            "    font-family:'Microsoft YaHei';"
    //                            "    font-size:11pt;"
    //                            "    color: rgb(0,0,0);"
    //                            "    background-color:rgb(253,253,254);"
    //                            "    padding: 8px 25px 6px 10px;"
    //                            "    margin: 4px 1px;"
    //                            "    padding-left:25px;"
    //                            "}"
    //                            "QMenu::item:selected {"
    //                            "    background-color : rgb(236,236,237);"
    //                            "}"
    //                            "QMenu::icon:selected {"
    //                            "    position: absolute;"
    //                            "    top: 1px;"
    //                            "    right: 1px;"
    //                            "    bottom: 1px;"
    //                            "    left: 1px;"
    //                            "}"
    //                            "QMenu::separator {"
    //                            "    height: 2px;"
    //                            "    background: rgb(235,235,236);"
    //                            "    margin-left: 10px;"
    //                            "    margin-right: 10px;"
    //                            "}");

    systemTrayIcon->setContextMenu(m_menu);  //设置托盘菜单
    connect(m_action1, &QAction::triggered, this, [=]{ this->show(); });
    connect(m_action2, &QAction::triggered, this, [=]{
        //按下open按钮，弹出新窗口
        newwidget->show();
        newwidget->resize(300,200);
        newwidget->move(1350,350);
        newwidget->setWindowTitle("啥也没有");
        newwidget->setWindowModality(Qt::NonModal);    //设置不阻塞（非模态）
    });
    connect(m_action3, &QAction::triggered, this, [=]{ exit(0);});
    connect(Minumized,&QPushButton::clicked, this, [=]{
        //this->showMinimized();//窗口隐藏，在桌面工具栏显示一个活动图标
        this->hide();//隐藏程序主窗口
        connect(systemTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));//托盘激活绑定
    });


    /*以后再看*/
    //待实现功能
    //按钮移入移除显示
    //    petButton->hidePushButton();
    //    Minumized->hide();
    //音乐播放
    //    player = new QMediaPlayer(this);
    //    music[0] = "../music/menu.mp3";  //打开菜单的音乐

    //音乐
    //    QMediaPlaylist playlist = new QMediaPlaylist;
    //    playlist->addMedia(QUrl::fromLocalFile("E:\\CloudMusic\\林沁简介 - 太阳的后裔 MIX.mp3"));
    //    playlist->addMedia(QUrl::fromLocalFile("E:\\CloudMusic\\芭比 - 触电 (完整版).mp3"));
    //    playlist->addMedia(QUrl::fromLocalFile("E:\\CloudMusic\\郭芯语 - 快点告诉你.mp3"));
    //    playlist->setCurrentIndex(1);
    //    player = new QMediaPlayer;
    //    player->setPlaylist(playlist);
    //    player->play();
}
//事件过滤器
bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(event);
    //光标位置
    //       QCursor *cursor;
    //       int x=cursor->pos().x();
    //       int y=cursor->pos().y();
    //       qDebug()<<"x=="<<x<<"y=="<<y;

    if(pet == watched && QEvent::Enter==event->type()) {
        this->m_textedit->show();
        m_textedit->setText(subArray.at(QRandomGenerator::global()->bounded(10)).toString());;               //最新退出的方法 推荐使用,生成一个0和10之间的整数
        /*以后再看*/
        //        petButton->showPushButton();
        //        Minumized->show();
    }
    else if(QEvent::Leave==event->type()){
        this->m_textedit->hide();
        /*以后再看*/
        //这块建议用多线程
        //        QThread::msleep(1500);//还是尝试用qss
        //        petButton->hidePushButton();
        //        Minumized->hide();
    }
    return QObject::eventFilter(watched,event);
}

//移动窗口
void Widget::mouseMoveEvent(QMouseEvent *event)
{    
    if(isHover){
        QPoint tempPos = event->globalPos() - screenPos;
        move(pos() + tempPos);
        screenPos = event->globalPos();
    }
}

//鼠标按下
void Widget::mousePressEvent(QMouseEvent *event)
{
    //点击鼠标左键
    if(event->buttons() == Qt::LeftButton){
        isHover = true;
        screenPos = event->globalPos();
    }

    //中间键按下
    else if(event->button() == Qt::MidButton)
    {

    }

    //    //右键被按下 跳出菜单//这里多加个功能音乐播放
    else
    {
        //            timer.stop();
        //            //打开菜单的音乐
        //            player->setMedia(QUrl::fromLocalFile (music[0]));
        //            player->setVolume(80); //音量
        //            player->play();
        //            //显示菜单
        //            mousePosP = e->pos();  //mousePosP 全局变量，QPoint
        //            //QPointF mouseLocPos = e->localPos();  //获得指针当前的相对地址，同pos()
        //            //QPoint mouseGlobePos = e->globalPos();  //获得指针当前的绝对地址，相对屏幕左上角
        //            //执行弹出操作
        petCharacter->p_Menu->popup(event->globalPos());
    }
    update();
}

//鼠标释放
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    isHover = false;
}

//托盘激活
void Widget::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:       //单击系统托盘
        //单击托盘图标
        //单击后显示主程序窗口
        this->show();
        break;
    case QSystemTrayIcon::DoubleClick:   //双击系统托盘
        //...
        break;
    case QSystemTrayIcon::Context:       //系统托盘的上下文菜单请求
        //...
        break;

    case QSystemTrayIcon::MiddleClick:   //鼠标中键点击系统托盘
        //...
        systemTrayIcon->showMessage(tr("托盘标题"), tr("托盘显示内容"));      // 显示系统托盘提示信息，//有些系统根本不会出现,看配置和用户设置
        break;
    default:
        break;
    }
}

Widget::~Widget()
{
    delete ui;
    delete Minumized;
    delete pet;
}
