#include <QObject>
#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
#include <QQmlEngine>

#include <QSharedMemory>

#include "Logger/Logger.h"

#include "appquickview.h"


int main(int argc, char *argv[])
{
    QtWebEngine::initialize();
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QSharedMemory shareMenory;
    // 使程序只有一个实例
    QSharedMemory shared("ms-app");
    if (shared.attach())
    {
        return 0;
    }
    shared.create(1);

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
