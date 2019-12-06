#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H

#include <QObject>
#include <QString>
#include <QNetworkInterface>
#include <QHostInfo>
namespace utils {

class SystemUtils
{

public:
    SystemUtils();
    //  获取mac地址
    static const QString mac();
    // 获取设备名称
    static const  QString getDevice();
};
}
#endif // SYSTEMUTILS_H
