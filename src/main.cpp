#include <QObject>
#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <QQmlEngine>
#include "Logger/Logger.h"

#include "appquickview.h"


int main(int argc, char *argv[])
{
    QtWebEngine::initialize();
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    app.setOrganizationName("ms");
    app.setOrganizationDomain("com");
    app.setApplicationName("ms");
    // 设置ICON
    app.setWindowIcon(QIcon("qrc:/images/favicon.ico"));

    // 初始化日志
    Logger::initLog();

    AppQuickView *view = new AppQuickView();
    view->show();

    // 关联信号(退出)
    QObject::connect(view->engine(), SIGNAL(quit()), &app, SLOT(quit()));
    return app.exec();
}
