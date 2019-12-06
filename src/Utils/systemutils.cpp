#include "systemutils.h"

namespace utils {


SystemUtils::SystemUtils()
{

}

const QString SystemUtils::mac()
{
    QString strMac;

    QList<QNetworkInterface> netList = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface item, netList)
    {
        if((QNetworkInterface::IsUp & item.flags()) && (QNetworkInterface::IsRunning & item.flags()))
        {
            if(strMac.isEmpty() || strMac < item.hardwareAddress())
            {
                strMac = item.hardwareAddress();
            }
        }
    }
    return strMac;
}

/*
     * 名称:get_localmachine_name
     * 功能:获取本机机器名称
     * 参数:no
     * 返回:QString
     */
const  QString SystemUtils::getDevice()
{
    QString machineName = QHostInfo::localHostName();
    return machineName;
}
}
