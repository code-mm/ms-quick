#ifndef APPQUICKVIEW_H
#define APPQUICKVIEW_H

#include <QQuickView>
#include <QQmlContext>
#include <QVariant>
#include <QDesktopWidget>
#include <QRect>
#include <QApplication>
#include <QTimer>
#include <QSqlDatabase>
#include <QDebug>
#include "homeleftmenumodel.h"

#include "IM/im.h"
#include "SystemFeatures/clipboard.h"
class AppQuickView : public QQuickView
{
public:
    AppQuickView();

private slots :


private:

    IM *im ;

    Clipboard * clipboard;

    // 数据库
    QSqlDatabase database;
};

#endif // APPQUICKVIEW_H
