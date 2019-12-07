#include "im.h"


IM::IM()
{
    qDebug() << "IM::IM";

    // 实例化IM客户端
    connection = new QMatrixClient::Connection();
    // 设置域名
    connection->setHomeserver(QUrl(BASE_URL));

    Common::getInstance()  ->setBaseUrl(BASE_URL);


    // 关联信号
    connect(connection, &QMatrixClient::Connection::loginError, this, &IM::loginError);
    connect(connection, &QMatrixClient::Connection::connected, this, &IM::loginSuccess);
    connect(connection, &QMatrixClient::Connection::loadedRoomState, this, &IM::onNewRoom);
    connect(connection, &QMatrixClient::Connection::networkError, this, &IM::networkError);
    connect(connection, &QMatrixClient::Connection::syncError, this, &IM::syncError);
    connect(connection, &QMatrixClient::Connection::turnServersChanged, this, &IM::turnServersChanged);
    connect(connection, &QMatrixClient::Connection::requestFailed, this, &IM::requestFailed);

    // 实例化MODEL
    roomDbModel = new RoomDBModel;
    messageDbModel = new MessageDBModel;
    roomMemberDbModel=  new RoomMemberDBModel;

}

QJsonObject IM::getTurnServers()
{
    return mTurnServers;
}

void IM::login(const QString username, const QString password)
{
    qDebug() << "IM::login";
    QString device = utils::SystemUtils::getDevice();
    std::cout << "username : " << username.toStdString() << std::endl;
    std::cout << "password : " << password.toStdString() << std::endl;
    std::cout << "device : " << device.toStdString() << std::endl;

    mUsername = username;
    mPassword = password;

    connection->connectToServer(username, password, device);
}

void IM::login(const QString username, const QString password, bool savePassword, bool autoLogin)
{


    qDebug() << "是否保存密码 : " << savePassword;
    qDebug() << "是否自动登录 : " << autoLogin;
    mSavePassword = savePassword;
    mAutoLogin = autoLogin;
    qDebug() << "IM::login";
    QString device = utils::SystemUtils::getDevice();
    std::cout << "username : " << username.toStdString() << std::endl;
    std::cout << "password : " << password.toStdString() << std::endl;
    std::cout << "device : " << device.toStdString() << std::endl;

    mUsername = username;
    mPassword = password;

    mCancelLogin = false;
    connection->connectToServer(username, password, device);

}

void IM::setQmlApplicationEngine(QQmlApplicationEngine engine)
{

}

void IM::setQuickView(QQuickView *view)
{
    qDebug() << "setQuickView";
    quickView = view;
    QList<User *> userList = userDb.queryByUserInfo();
    qDebug() << "查询长度 : " << userList.size();
    if (userList.size() > 0)
    {
        QString username = userList[0]->getUsername();
        QString password = userList[0]->getPassword();
        bool autologin = userList[0]->getAutoLogin();
        bool savePassword = userList[0]->getSavePassword();

        QObject *CheckBoxSavePasswordAutoLogin = quickView->findChild<QObject *>("CheckBoxSavePasswordAutoLogin");
        QVariant val;

        if (autologin)
        {

            // TODO , 更新界面的 正在登录中 ...
            QMetaObject::invokeMethod(
                CheckBoxSavePasswordAutoLogin,
                "savePassword",
                Q_RETURN_ARG(QVariant, val),
                Q_ARG(QVariant, QVariant(""))
                );

            QMetaObject::invokeMethod(
                CheckBoxSavePasswordAutoLogin,
                "autoLogin",
                Q_RETURN_ARG(QVariant, val),
                Q_ARG(QVariant, QVariant(""))
                );


            // TODO 勾选记住密码，自动登录
            login(username, password);

        } else
        {
            if (savePassword)
            {
                QMetaObject::invokeMethod(
                    CheckBoxSavePasswordAutoLogin,
                    "savePassword",
                    Q_RETURN_ARG(QVariant, val),
                    Q_ARG(QVariant, QVariant(""))
                    );
            }
        }

        QObject *LoginHomeField = quickView->findChild<QObject *>("LoginHomeField");
        QVariant variantValuesUsername;
        QMetaObject::invokeMethod(
            LoginHomeField,
            "setUsername",
            Q_RETURN_ARG(QVariant, variantValuesUsername),
            Q_ARG(QVariant, QVariant(username))
            );

        QVariant variantValuesPassword;
        QMetaObject::invokeMethod(
            LoginHomeField,
            "setPassword",
            Q_RETURN_ARG(QVariant, variantValuesPassword),
            Q_ARG(QVariant, QVariant(password))
            );
    } else
    {
        qDebug() << " 数据库 没有 信息";
    }

    // 数据库房间
    quickView->rootContext()->setContextProperty("roomDbModel", roomDbModel);
    // 注册消息MODEL
    quickView->rootContext()->setContextProperty("messageDbModel", messageDbModel);
    // 房间成员
    quickView->rootContext()->setContextProperty("roomMemberDbModel",roomMemberDbModel);


}

void IM::setQmlObject(QObject *object)
{

}

void IM::setQmlContext(QQmlContext *qmlContext)
{

}

// 发送消息
void IM::sendMessage(QString roomid, QString message)
{

    qDebug() << "sendMessage";

    qDebug() << "roomid  : " << roomid;
    for (auto it:roomList)
    {

        qDebug() << "it roomid  : " << it->id();

        if (it->id() == roomid)
        {
            qDebug() << "找到房间";
            auto txnId = it->postMessage(message, QMatrixClient::MessageEventType::Text);
            QMatrixClient::connectUntil(it,
                                        &QMatrixClient::Room::pendingEventAboutToMerge,
                                        this,
                                        [this, roomid, message, it, txnId](const QMatrixClient::RoomEvent *evt,
                                                                           int pendingIdx)
                                        {

                                            qDebug() << "pendingIdx : " << pendingIdx;


                                            QString eventId =  evt->id();

                                            qDebug()<< " 事件ID " <<eventId;


                                            const auto &pendingEvents = it->pendingEvents();


                                            qDebug()<< " evt->transactionId()  " <<evt->transactionId() ;
                                            qDebug()<< " txnId  " <<txnId ;

                                            // 判断消息是否发送成功
                                            if (evt->transactionId() != txnId)
                                            {
                                                // 将消息插入数据库
                                                messageDbModel->slotsSendMessage(roomid,message,eventId,false);

                                                // 发送失败
                                                return false;


                                            } else
                                            {
                                                // 发送成功

                                                messageDbModel->slotsSendMessage(roomid,message,eventId,true);

                                            }
                                        });

        }
    }
}

void IM::voice(QString sdp)
{

}

void IM::sendCallCandidates(const QJsonArray &candidates)
{

}

void IM::loginError(QString message, QString details)
{
    qDebug() << "IM::loginError";
    QQuickItem *quickItem = quickView->rootObject();
    QObject *buttonCancelLogin = quickItem->findChild<QObject *>("buttonCancelLogin");
    QVariant variantValues;
    QMetaObject::invokeMethod(
        buttonCancelLogin,
        "err",
        Q_RETURN_ARG(QVariant, variantValues),
        Q_ARG(QVariant, QVariant(message))
        );
}

void IM::loginSuccess()
{
    qDebug() << "IM::loginSuccess";
    std::cout << "连接服务器成功" << std::endl;
    std::cout << "服务器域名:" << connection->homeserver().toDisplayString().toStdString() << std::endl;
    std::cout << "用户ACCESS_TOKEN" << connection->accessToken().toStdString() << std::endl;
    std::cout << "用户UserId" << connection->userId().toStdString() << std::endl;


    mUserid=connection->userId();
    mAccessToken=connection->accessToken();

    Common::getInstance()->setAccessToken(mAccessToken);
    Common::getInstance()->setUserid(mUserid);

    // 获取时间戳
    int time = QDateTime::currentDateTime().toTime_t();
    // 插入数据
    userDb.insert(mUsername,mPassword,mUserid,mAccessToken,mSavePassword,mAutoLogin,time,BASE_URL);

    // 点击取消登录后,不继续登录
    if (!mCancelLogin)
    {

        QObject *itemMainRootObject = quickView->findChild<QObject *>("itemMainRootObject");
        QVariant variantValues;
        QMetaObject::invokeMethod(
            itemMainRootObject,
            "loginSuccess",
            Q_RETURN_ARG(QVariant, variantValues),
            Q_ARG(QVariant, QVariant("loginsuccess"))
            );


        // 开始同步
        sync();
        // 获取turn服务器地址
        connection->getTurnServers();

    }
}

void IM::onNewRoom(QMatrixClient::Room *room)
{

    qDebug() << "onNewRoom";
    std::cout << "id : " << room->id().toStdString() << "  name : " << room->name().toStdString() << std::endl;

    // 将房间添加到Lits
    roomList.append(room);
    // 将房间信息插入数据库
    roomDbModel->insert(room, connection);
    // 将消息存入数据库
    messageDbModel->insert(room);
    // 加载房间成员
    roomMemberDbModel->loadMembers( room,connection);

}

// 网络错误
void IM::networkError(QString message, QString details, int retriesTaken, int nextRetryInMilliseconds)
{
    qDebug() << "networkError";
    qDebug() << "message : " << message;
    qDebug() << "details : " << details;
    qDebug() << "retriesTaken : " << retriesTaken;
    qDebug() << "nextRetryInMilliseconds : " << nextRetryInMilliseconds;
}

// 同步
void IM::sync()
{
    qDebug() << "开始同步";

    // 设置延迟加载
    connection->setLazyLoading(true);
    //开始同步
    connection->syncLoop();

    connect(connection, &QMatrixClient::Connection::syncDone, connection, [this]
            {
                // std::cout << "同步完成, "  <<std:: endl;
            });
}

void IM::syncError(QString message, QString details)
{
    qDebug() << "同步错误 syncError";
    qDebug() << " message " << message;
    qDebug() << " details " << details;
}

void IM::turnServersChanged(const QJsonObject &servers)
{
    qDebug() << "turnServersChanged";
    this->mTurnServers = servers;
}

void IM::aboutToAddNewMessages(QMatrixClient::RoomEventsRange events)
{
    qDebug() << "aboutToAddNewMessages";

}

void IM::requestFailed(QMatrixClient::BaseJob *request)
{
    qDebug() << "requestFailed";
    qDebug() << request->errorString();
}

void IM::cancelLogin()
{
    mCancelLogin = true;
}

// 勾选保存密码 与 取消勾选保存密码
void IM::setSavePasswordStatus(QString username, bool status)
{
    if (username != nullptr && username != "")
    {
        userDb.setSavePasswordStatus(username, status);
    }
}

// 勾选自动登录选择与取消选择
void IM::setAutoLoginStatus(QString username, bool status)
{
    if (username != nullptr && username != "")
    {
        // TODO 更新数据库，将自动登录状态改为0
        userDb.setAutoLoginStatus(username, status);
    }
}


