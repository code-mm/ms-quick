#ifndef USERDB_H
#define USERDB_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QList>
#include "user.h"
#include "../Utils/logutils.h"
#include "sqlconstant.h"


//CREATE TABLE _user
//(
//        _id                     integer primary key autoincrement,
//        _username               varchar(64),
//_password               varchar(64),
//        _userid                 varchar(64),
//_access_token           varchar(256),
//        _savepassword           integer,
//_autologin              integer,
//        _laster_update_datetime integer,
//_base_server            varchar(256)
//);


// 表名称
const static QString _TABLE_NAME_ = "_user";


// 创建表语句
const static QString _CREATE_TABLE_USER_ = "CREATE TABLE _user"
                                           "("
                                           "     _id                     integer primary key autoincrement, "
                                           "     _username               varchar(64), "
                                           "     _password               varchar(64), "
                                           "     _userid                 varchar(64), "
                                           "     _access_token           varchar(256), "
                                           "     _savepassword           boolean, "
                                           "     _autologin              boolean, "
                                           "     _laster_update_datetime integer, "
                                           "     _base_server            varchar(256) "
                                           ")";


class UserDB
{
public:
    UserDB();


    // 插入用户信息
    void insert(
            QString username,
            QString password,
            QString userid,
            QString accessToken,
            bool savePassword,
            bool autoLogin,
            int lasterUpdateDateTime,
            QString baseUrl
            );

    // 查询用户
    QList<User *> queryByUserInfo();

    // 检查用户名称是否存在
    bool checkUserExists(QString username);

    // 修改保存密码状态
    void setSavePasswordStatus(QString username, bool status);

    // 修改自动登录状态
    void setAutoLoginStatus(QString usernamem, bool status);

private:

};

#endif // USERDB_H
