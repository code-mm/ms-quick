#ifndef IM_H
#define IM_H

#include <QObject>
#include <QString>
#include <QtDebug>
#include <QQmlContext>
#include <QQuickView>
#include <QUuid>
#include <QNetworkInterface>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QScreen>
#include <QDesktopWidget>
#include <QApplication>
#include <QCoreApplication>
#include <QGuiApplication>
#include<QQuickItem>

#include<iostream>

#include "events/event.h"
#include "connection.h"
#include "room.h"
#include "user.h"
#include "csapi/room_send.h"
#include "csapi/joining.h"
#include "csapi/leaving.h"
#include "events/simplestateevents.h"
#include "events/eventloader.h"


#include "../Utils/systemutils.h"
#include "roommodel.h"
#include "message.h"
#include "../common.h"
#include "userdb.h"
#include "messagedbmodel.h"
#include "roomdbmodel.h"




#if 0
static const QString BASE_URL= "https://matrix-client.matrix.org";
#else
static const QString BASE_URL= "https://www.mhw828.com";
#endif


class IM : public QObject
{

    // 方法
    Q_OBJECT
public:
    IM();

    QJsonObject getTurnServers();

    // 登录
    Q_INVOKABLE void login(const QString username,const  QString password);
    Q_INVOKABLE void login(const QString username,const  QString password,bool savePassword,bool autoLogin);
    void setQmlApplicationEngine(QQmlApplicationEngine engine);
    void setQuickView(QQuickView *view);
    void setQmlObject(QObject *object);
    void setQmlContext(QQmlContext *qmlContext);





    // 语音通话
    void voice(QString sdp);
    // 发送语音
    void  sendCallCandidates(const QJsonArray& candidates);

public slots:

    void sendMessage(QString roomid,QString message);

    // 登录失败
    void loginError(QString message, QString details);
    // 登录成功
    void loginSuccess();
    // 房间新事件
    void onNewRoom(QMatrixClient::Room *room);
    // 网络错误
    void networkError(QString message, QString details,int retriesTaken, int nextRetryInMilliseconds);
    // 开始同步
    void sync();
    // 同步错误
    void syncError(QString message, QString details);
    // turn 服务器地址变化监听
    void turnServersChanged(const QJsonObject& servers);
    // 新消息通知
    void aboutToAddNewMessages(QMatrixClient::RoomEventsRange events);

    void requestFailed(QMatrixClient::BaseJob* request);
    // 取消登录
    void cancelLogin();

    // 勾选保存密码
    void setSavePasswordStatus(QString username,bool status);

    // 勾选自动登录 选择 与 取消选择
    void setAutoLoginStatus(QString username,bool status);

private:

    QQuickView *quickView;
    //
    QMatrixClient::Connection *connection;
    // 房间列表
    QList<QMatrixClient::Room *> roomList;
    // callid
    QString mCallId;
    // turn 服务器
    QJsonObject mTurnServers;

    // 存储用户信息的数据库
    UserDB userDb;

    // 用户名
    QString mUsername;
    // 密码
    QString mPassword;
    // 数据库RoomModel
    RoomDBModel *roomDbModel;

    // 数据库消息MODEL
    MessageDBModel *messageDbModel;

    // 保存密码
    bool mSavePassword=false;

    // 自动登录
    bool mAutoLogin=false;

    // 点击取消登录按钮后， 不在登录 true 不登录，false 登录
    bool mCancelLogin=false;

};

#endif // IM_H
