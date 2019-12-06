#include "appquickview.h"

AppQuickView::AppQuickView()
{
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    this->setSource(url);
    this->setResizeMode(SizeRootObjectToView);


    database = QSqlDatabase::database();
    if (!database.isValid())
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid())
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
    }

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!writeDir.mkpath("."))
        qFatal("Failed to create writable directory at %s", qPrintable(writeDir.absolutePath()));

    const QString fileName = writeDir.absolutePath() + "/app-database.sqlite3";

    qDebug() << "数据库位置:" << fileName;

    database.setDatabaseName(fileName);
    if (!database.open())
    {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
        QFile::remove(fileName);
    }


    QDesktopWidget *desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = desktopWidget->availableGeometry();
    //获取主屏幕分辨率
    QRect screenRect = desktopWidget->screenGeometry();
    //获取屏幕数量
    int nScreenCount = desktopWidget->screenCount();

    qDebug() << "width: " << deskRect.width();
    qDebug() << "height: " << deskRect.height();
    qDebug() << "分辨率: " << screenRect;
    qDebug() << "屏幕数量: " << nScreenCount;

    // 设置居中
    this->setX(deskRect.width() / 2 - this->width() / 2);
    this->setY(deskRect.height() / 2 - this->height() / 2);


    QList<QObject *> homeLeftMenuModelList;

    HomeLeftMenuModel *homeLeftMenuModelInfo = new HomeLeftMenuModel();
    homeLeftMenuModelInfo->setName("信息");
    homeLeftMenuModelInfo->setIconUrl("qrc:/images/img_info.png");
    homeLeftMenuModelList.append(homeLeftMenuModelInfo);


    HomeLeftMenuModel *homeLeftMenuModelEmail = new HomeLeftMenuModel();
    homeLeftMenuModelEmail->setName("邮件");
    homeLeftMenuModelEmail->setIconUrl("qrc:/images/img_email.png");
    homeLeftMenuModelList.append(homeLeftMenuModelEmail);

    HomeLeftMenuModel *homeLeftMenuModelPluginManager = new HomeLeftMenuModel();
    homeLeftMenuModelPluginManager->setName("插件管理");
    homeLeftMenuModelPluginManager->setIconUrl("qrc:/images/img_plugin_manager.png");
    homeLeftMenuModelList.append(homeLeftMenuModelPluginManager);


    this->rootContext()->setContextProperty("homeLeftMenuModel", QVariant::fromValue(homeLeftMenuModelList));
    this->rootContext()->setContextProperty("rootWindow", this);

    im = new IM();
    im->setQuickView(this);
    this->rootContext()->setContextProperty("im", im);

}


