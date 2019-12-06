#include "logutils.h"

LogUtils::LogUtils()
{
}

void LogUtils::print(QString log)
{
    if (DEBUG)
    {
        printf("%s", log.toStdString().data());
    }
}

void LogUtils::cout(QString log)
{
    if (DEBUG)
    {
        std::cout << log.toStdString() << std::endl;
    }
}

void LogUtils::i(QString log)
{
    if (DEBUG)
    {
        qInfo() << log;
    }
}

void LogUtils::d(QString log)
{
    if (DEBUG)
    {
        qDebug() << log;
    }
}

void LogUtils::w(QString log)
{
    if (DEBUG)
    {
        qWarning() << log;
    }
}

void LogUtils::c(QString log)
{
    if (DEBUG)
    {
        qCritical() << log;
    }
}
