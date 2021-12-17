#include "common.h"
#include "widget.h"
/*读取json内容配置*/
void Widget::ReadJsonDoc(QString path){

    QFile loadFile(path);//打开文件
    if(!loadFile.open(QIODevice::ReadOnly))    //只读方式，如果文件打开失败退出
    {
        qDebug() << "File open error";
        return;
    }
    QByteArray allData = loadFile.readAll();  //获取所有内容赋值给ByteArray
    loadFile.close();                         //关闭文件
    QJsonParseError jsonError;
    //QJsonDocument提供一种读取和写入JSON文档的方法,可以通过它的的成员函数array()或object()检索文档中包含的数组或对象，然后读取JSON数据,或者修改数据。
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));
    //判断文件是否完整
    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!" << jsonError.errorString();
        return;
    }
    //QJsonObject封装了一个JSON对象, 可以使用它的成员函数size()、insert()和remove()来对修改JSON数据.
    QJsonObject ContextObj = jsonDoc.object();

    //    QStringList keys = ContextObj.keys();
    //    for(int i = 0; i < keys.size(); i++)
    //    {
    //        qDebug() << "key" << i << " is:" << keys.at(i);
    //    }

    //    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    //    if(ContextObj.contains("author"))
    //    {
    //       QJsonObject subObj = ContextObj.value("first fruit").toObject();
    //       qDebug() << "describe is:" << subObj["describe"].toString();
    //       qDebug() << "icon is:" << subObj["icon"].toString();
    //       qDebug() << "name is:" << subObj["name"].toString();
    //    }

    //    if(ContextObj.contains("version"))
    //    {
    //       QJsonObject subObj = ContextObj.value("second fruit").toObject();
    //       qDebug() << "describe is:" << subObj.value("describe").toString();
    //       qDebug() << "icon is:" << subObj.value("icon").toString();
    //       qDebug() << "name is:" << subObj.value("name").toString();
    //    }

    if(ContextObj.contains("Context"))
    {
        subArray = ContextObj.value("Context").toArray();  //QJsonArray 封装了一个JSON数组,用来实现JSON数组的
    }
}
