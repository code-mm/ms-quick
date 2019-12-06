#ifndef LOGUTILS_H
#define LOGUTILS_H


#define DEBUG true

#include <QString>
#include <QDebug>
#include <cstdio>
#include <iostream>
#include "../Logger/Logger.h"
class LogUtils
{
private:
    LogUtils();

public:

    static void print(QString log);

    static void cout(QString log);

    static void i(QString log);

    static void d(QString log);

    static void w(QString log);

    static void c(QString log);

};

#endif // LOGUTILS_H
