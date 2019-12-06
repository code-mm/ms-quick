#ifndef USERDB_H
#define USERDB_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QList>
#include "user.h"
#include "../Utils/logutils.h"
class UserDB
{
public:
    UserDB();
    // 插入用户
    void insert(QString username,QString password);
    // 插入用户，保存密码，自动登录
    void insert(QString username,QString password,bool savePassword,bool autoLogin);
    // 查询用户
    QList<User*> queryByUserInfo();
    // 检查用户名称是否存在
    bool checkUserExists(QString username);
    // 修改保存密码状态
    void setSavePasswordStatus(QString username,bool status);
    // 修改自动登录状态
    void setAutoLoginStatus(QString usernamem,bool status);
    // 设置用户ID
    void setUserId(QString username,QString userid);
    // 设置用户TOKEN
    void setAccessToken(QString username,QString accessToken);

private:
    // 创建表
    void createTable();
};

#endif // USERDB_H
