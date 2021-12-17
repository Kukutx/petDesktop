#include "petbutton.h"
#include "widget.h"
PetButton::PetButton(QWidget * widget)
{
    //拿到主窗口对象
    widgetObj=widget;

    //检测字体是否存在
    if (!fontDb.families().contains("iconfont")) {
        int fontId = fontDb.addApplicationFont("://res/icon/iconfont.ttf");
        QStringList fontName = fontDb.applicationFontFamilies(fontId);
        if (fontName.count() == 0) {
            qDebug() << "加载 iconfont.ttf 错误";
        }
    }
    if (fontDb.families().contains("iconfont")) {
        iconFont = QFont("iconfont");
        iconFont.setHintingPreference(QFont::PreferNoHinting);
        iconFont.setPixelSize(25); //设置字体大小
    }

    //设置壁纸
    SetWallpaper->setParent(this->widgetObj);
    SetWallpaper->move(this->widgetObj->pos().x() + 270 ,this->widgetObj->pos().y() + 110); //设置按你的坐标位置
    setButtonIcon(SetWallpaper,0xe6ae);                                                     //设置icon
    connect(SetWallpaper,&QPushButton::clicked, this, &PetButton::onsetWallPaper);

    //截屏
    FullScreen->setParent(this->widgetObj);
    FullScreen->move(this->widgetObj->pos().x() + 270 ,this->widgetObj->pos().y() + 150); //设置按你的坐标位置
    setButtonIcon(FullScreen,0xe631);
    connect(FullScreen,&QPushButton::clicked, this, &PetButton::onGrabFullScreen);

    /*消息*/
    msg->setParent(this->widgetObj);
    msg->move(this->widgetObj->pos().x() + 270 ,this->widgetObj->pos().y() + 190); //设置按你的坐标位置
    setButtonIcon(msg,0xe728);
    connect(msg,&QPushButton::clicked, this, &PetButton::onMsgButton);

    /*关于*/
    about->setParent(this->widgetObj);
    about->move(this->widgetObj->pos().x() + 270 ,this->widgetObj->pos().y() + 230); //设置按你的坐标位置
    setButtonIcon(about,0xe710);
    connect(about,&QPushButton::clicked, this, &PetButton::onAboutButton);

    /*退出*/
    Exit->setParent(this->widgetObj);
    Exit->move(this->widgetObj->pos().x() + 270 ,this->widgetObj->pos().y() + 310); //设置按你的坐标位置
    setButtonIcon(Exit,0xe63b);
    connect(Exit,&QPushButton::clicked, this, &PetButton::onExitButton);

}

void PetButton::setButtonIcon(QPushButton *btn,QChar iconID)
{
    btn->setFont(iconFont); //设置QPushButton的字体
    btn->setText(iconID); //设置QPushButton的文体
    btn->setFlat(true);
    QFontMetrics metrics(iconFont);//设置字体信息
    btn->resize(metrics.boundingRect(QChar(0xe78c)).size() * 2);  //设置按钮的大小
    //设置QPushButton的样式
    btn->setStyleSheet(
                //默认样式
                "QPushButton{"
                "color:black;"
                "}"
                //鼠标悬停样式
                "QPushButton:hover{"
                "color:#67caff;"
                "font-size:30px"
                "}"
                //鼠标按下样式
                "QPushButton:pressed{"
                "color:orange;"
                "}");
}

void PetButton::onMsgButton()
{
    QMessageBox::information(NULL, "消息", "要死了，要死了");
}

void PetButton::onAboutButton()
{
    const QUrl regUrl(QLatin1String("http://www.baidu.com"));
    QDesktopServices::openUrl(regUrl);
}

void PetButton::onExitButton()
{
    exit(0);
}

void PetButton::onGrabFullScreen()
{
    //选择路径
    basename = QFileDialog::getExistingDirectory(widgetObj, "请选择文件保存路径…", "./");
    QScreen *screen = QGuiApplication::primaryScreen();
    QString filePathName = "full-";
    filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
    filePathName += ".jpg";
    QString saveFilePath = basename + '/' + filePathName;
    if(basename == "" || !screen->grabWindow(0).save(saveFilePath, "jpg"))
    {
        QMessageBox::information(NULL, "截屏", "截屏失败");
        return;
    }else QMessageBox::information(NULL, "截屏", "截屏成功，保存在目录：" + saveFilePath);
}

void PetButton::onsetWallPaper()
{
    /*打开文件对话框选取文件*/
    QString fileName = QFileDialog::getOpenFileName(this->widgetObj,
                                                    "请选择一个图像文件",
                                                    "",
                                                    "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
//    QFileInfo base(fileName);
//    QString basename = base.baseName(); //打开的文件文件名,xx。不包含文件后缀
    if( fileName != "" )
       {
           if(image.load(fileName) )
           {//这里搞三目运算符，加lambda表达式
               qDebug()<<fileName;
               setWallPaper(fileName);
           }
       }
}

/*
 * 输入本地图片文件的全路径
 * 调用windows系统函数SystemParametersInfo设置当前路径下的图片为桌面背景
 */
#if defined(Q_OS_WIN)
void PetButton::setWallPaper(QString filePath)
{
    const char *tmp = filePath.toStdString().c_str(); //QDir::currentPath().append("/").append(currentFileName_).toStdString().c_str();
    std::wstringstream wss;
    wss << tmp;
    const wchar_t *filename = wss.str().c_str();
    if( !SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)filename, SPIF_UPDATEINIFILE) )
    {
        qDebug("设置桌面背景失败!");
    }
}

//未测试不清楚
#elif defined(Q_OS_LINUX)
#include <QProcess>
void PetButton::setWallPaper(QString filePath)
{
//
    QFile file(qApp->applicationDirPath() + "/setwallpaperforUbuntu");
    file.open(QIODevice::ReadWrite);
    QTextStream textStream(&file);
    QString text = textStream.readAll();
    int start = text.indexOf("/home");
    textStream.seek(start);
    textStream << filePath << "' ";//这么多空格是因为每次路径字符串长度不等，保证能够覆盖。SHELL文件相应位置也有空格（empty spaces）
    file.close();

    //调用执行该SHELL文件
    QProcess *setWallPaperSHELL = new QProcess;
    QString command = qApp->applicationDirPath() + "/setwallpaperforUbuntu";
    qDebug()<< command;
    setWallPaperSHELL->start(command);
    qDebug()<<setWallPaperSHELL->errorString();

//    qDebug()<<setWallPaperSHELL->execute("saveDir=$HOME'/'");
//    qDebug()<<setWallPaperSHELL->execute("picOpts=\"zoom\"");
//    qDebug()<<setWallPaperSHELL->execute("picName=\"Fiddleheads_ZH-CN14463697077_1920x1200.jpg\"");
//    qDebug()<<setWallPaperSHELL->execute("DISPLAY=:0 GSETTINGS_BACKEND=dconf gsettings set org.gnome.desktop.background picture-uri '\"file://'$saveDir$picName'\"'");
//    qDebug()<<setWallPaperSHELL->execute(" DISPLAY=:0 GSETTINGS_BACKEND=dconf gsettings set org.gnome.desktop.background picture-options $picOpts");

//    qDebug()<<setWallPaperSHELL->execute("./setwallpaperforUbuntu");
//    system("/home/yinhe/develop/DeskWallPaper/setwallpaperforUbuntu");
//    system("opt/setwallpaperforUbuntu");
    qDebug("ubuntu");
}
#endif



//暂时没啥用
void PetButton::showPushButton()
{
    msg->show();
    about->show();
    Exit->show();
}

void PetButton::hidePushButton()
{
    msg->hide();
    about->hide();
    Exit->hide();
}

PetButton::~PetButton()
{
    delete msg;
    delete about;
    delete Exit;
}
