#include "userdb.h"

UserDB::UserDB()
{
    if (QSqlDatabase::database().tables().contains(_TABLE_NAME_))
    {
        qDebug() << _TABLE_NAME_ << " 连接成功 ";
        return;
    } else
    {
        qDebug() << _TABLE_NAME_ << " 连接失败，创建表 ";
        QSqlQuery sqlQuery;

        qDebug() << "sql : " << _CREATE_TABLE_USER_;

        if (sqlQuery.exec(_CREATE_TABLE_USER_))
        {
            qDebug() <<_TABLE_NAME_<< " 创建成功";
        } else
        {
            qDebug() << _TABLE_NAME_ <<" 创建失败";
            qDebug() << sqlQuery.lastError().text();
        }
    }
}

// 检查用户是否存在
bool UserDB::checkUserExists(QString username)
{
    QSqlQuery result;
    QString sql = "select _username from _user";
    result.exec(sql);
    QList<QString> list;
    while (result.next())
    {
        QString uname = result.value(0).toString();
        list.append(uname);
    }
    for (QString it: list)
    {
        if (it == username)
        {
            return true;
        }
    }
    return false;
}



QList<User *> UserDB::queryByUserInfo()
{
    QSqlQuery result;

    result.exec("select * from _user");


    QList<User *> list;

    while (result.next())
    {

        // id
        int id = result.value(0).toInt();
        // 用户名
        QString username = result.value(1).toString();
        // 密码
        QString password = result.value(2).toString();
        // 用户ID
        QString userid = result.value(3).toString();
        // 用户TOKEN
        QString access_token = result.value(4).toString();
        // 保存密码
        int savePassword = result.value(5).toInt();
        // 自动登录
        int autoLogin = result.value(6).toInt();
        // 时间
        int _datetime = result.value(7).toInt();

        User *user = new User();

        user->setId(id);
        user->setUserid(userid);
        user->setUsername(username);
        user->setPassword(password);


        if (autoLogin == 0)
        {
            user->setAutoLogin(false);
        } else
        {
            user->setAutoLogin(true);
        }


        if (savePassword == 0)
        {
            user->setSavePassword(false);
        } else
        {
            user->setSavePassword(true);
        }

        list.append(user);
    }
    return list;
}



// 修改保存密码状态
void UserDB::setSavePasswordStatus(QString username, bool status)
{
    QSqlQuery resule;
    if (status)
    {
        QString sql = "update _user set _savepassword = 1, _laster_update_datetime = " +
                      QString::number(QDateTime::currentDateTime().toTime_t()) + " where _username = '" + username + "'";
        resule.exec(sql);
    } else
    {
        QString sql = "update _user set _savepassword = 0 , _laster_update_datetime = " +
                      QString::number(QDateTime::currentDateTime().toTime_t()) + " where _username = '" + username + "'";
        resule.exec(sql);
    }
}

// 更新自动登录状态
void UserDB::setAutoLoginStatus(QString usernamem, bool status)
{
    QSqlQuery resule;
    if (status)
    {
        QString sql = "update _user set _autologin=1, _laster_update_datetime = " +
                      QString::number(QDateTime::currentDateTime().toTime_t()) + "where _username = '" + usernamem + "'";
        resule.exec(sql);
    } else
    {
        QString sql = "update _user set _autologin=0 , _laster_update_datetime = " +
                      QString::number(QDateTime::currentDateTime().toTime_t()) + "where _username = '" + usernamem + "'";
        resule.exec(sql);
    }
}

// 插入数据
void UserDB::insert(
    QString username,
    QString password,
    QString userid,
    QString accessToken,
    bool savePassword,
    bool autoLogin,
    int lasterUpdateDateTime,
    QString baseUrl
    )
{
    QString sql;
    if(checkUserExists(username))
    {
        qDebug()<<"已经存在账号，更新";
        sql  = "update "+_TABLE_NAME_+
              " set _username = '"+username+"',"
                                                " set _password = '"+password+"',"
                           " set _userid = '"+userid+"',"
                         " set _access_token = '"+accessToken+"',"
                              " set _savepassword = "+savePassword+","
                               " set _autologin = "+autoLogin+","
                            " set _laster_update_datetime = "+lasterUpdateDateTime+","
                                       " set _base_server = '"+baseUrl+"'"
                          " where _username = '"+username+"'";
    }
    else
    {
        qDebug()<<"不存在账号插入";
        sql  = "insert into "+_TABLE_NAME_+
              "("
              " _username,"
              " _password,"
              " _userid,"
              " _access_token,"
              " _savepassword,"
              "_autologin,"
              "_laster_update_datetime,"
              "_base_server"
              ")"
              "values"
              "("
              "'"+username+"',"
                           "'"+password+"',"
                           "'"+userid+"',"
                         "'"+accessToken+"',"
                              ""+QString::number(savePassword)+","
                                                ""+QString::number(autoLogin)+","
                                             ""+QString::number(lasterUpdateDateTime)+","
                                                        "'"+baseUrl+"'"
                          ")";


    }

    qDebug()<<" sql : "<<sql;
    QSqlQuery resule;
    if(resule.exec(sql))
    {
        qDebug()<< "插入成功";
    }
    else
    {
        qDebug()<< "插入失败 "<< resule.lastError().text() ;
    }
}
