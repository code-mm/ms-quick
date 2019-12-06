#include "userdb.h"

UserDB::UserDB()
{
    if(QSqlDatabase::database().tables().contains("_user"))
    {
        qDebug()<<"_user 连接成功";
        return;
    }else
    {
        qDebug()<<"_user 连接失败，创建表";
        createTable();
    }
}
void UserDB::insert(QString username, QString password)
{
    bool exists = checkUserExists(username);
    if(exists)
    {
        LogUtils::i(" 账号已经存在更新 ");
        // 存在更新
        QSqlQuery sqlQuery;
        QString sql = "update _user set username='"+username+"', password =  '"+password+"'  where username= '"+username+"'";
        sqlQuery.exec(sql);
    }
    else
    {
        LogUtils::i(" 账号不存在插入数据 ");
        // 不存在 插入数据
        QSqlQuery sqlQuery;
        QString sql = "insert into _user(username, password) values ('"+username+"','"+password+"')";
        sqlQuery.exec(sql);
    }
}


void UserDB::insert(QString username,QString password,bool savePassword,bool autoLogin)
{
    qDebug()<<"UserDB::insert(QString username,QString password,bool savePassword,bool autoLogin)";
    bool exists = checkUserExists(username);
    qDebug()<<"用户是否存在"<<exists;
    // 自动登录
    if(autoLogin)
    {
        qDebug()<<"自动登录";
        // 如果自动登录，保存密码
        if(exists)
        {
            LogUtils::i(" 账号已经存在更新 ");
            // 存在更新
            QSqlQuery sqlQuery;
            QString sql = "update _user set username='"+username+"', password =  '"+password+"' ,autologin = 1 where username= '"+username+"'";
            sqlQuery.exec(sql);
        }
        else
        {
            LogUtils::i(" 账号不存在插入数据 ");
            // 不存在 插入数据
            QSqlQuery sqlQuery;

            QString sql = "insert into _user(username, password,autologin) values ('"+username+"','"+password+"',1)";

            qDebug()<< " 自动登录sql : "<<sql;
            if(sqlQuery.exec(sql))
            {
                qDebug()<< " 插入成功 ";
            }
            else
            {
                qDebug()<< " 插入错误 "<< sqlQuery.lastError().text();
            }
        }
    }
    else
    {
        qDebug()<<"不自动登录";
        // 不自动登录
        if(savePassword)
        {
            // 保存 密码
            if(exists)
            {
                LogUtils::i(" 账号已经存在更新 ");
                // 存在更新
                QSqlQuery sqlQuery;
                QString sql = "update _user set username='"+username+"', password =  '"+password+"'  where username= '"+username+"'";
                sqlQuery.exec(sql);
            }
            else
            {
                LogUtils::i(" 账号不存在插入数据 ");
                // 不存在 插入数据
                QSqlQuery sqlQuery;
                QString sql = "insert into _user(username, password) values ('"+username+"','"+password+"')";
                sqlQuery.exec(sql);
            }
        }else{

            // 不保存密码
            if(exists)
            {
                LogUtils::i(" 账号已经存在更新 ");
                // 存在更新
                QSqlQuery sqlQuery;
                QString sql = "update _user set username='"+username+"' where username= '"+username+"'";
                sqlQuery.exec(sql);
            }
            else
            {
                LogUtils::i(" 账号不存在插入数据 ");
                // 不存在 插入数据
                QSqlQuery sqlQuery;
                QString sql = "insert into _user(username) values ('"+username+"')";
                sqlQuery.exec(sql);
            }
        }
    }
}

QList<User *> UserDB::queryByUserInfo()
{
    QSqlQuery result ;

    result.exec("select * from _user");


    QList<User *> list;

    while (result.next())
    {

        // id
        int id = result.value(0).toInt();
        // 用户名
        QString username = result.value(1).toString();
        // 密码
        QString password =  result.value(2).toString();
        // 用户ID
        QString userid =  result.value(3).toString();
        // 用户TOKEN
        QString access_token=result.value(4).toString();
        // 保存密码
        int savePassword =result.value(5).toInt();
        // 自动登录
        int autoLogin= result.value(6).toInt();
        // 时间
        int _datetime = result.value(7).toInt();

        User *user = new User();

        user->setId(id );
        user->setUserid(userid );
        user->setUsername(username);
        user->setPassword(password);


        if(autoLogin==0)
        {
            user->setAutoLogin(false);
        }
        else
        {
            user->setAutoLogin(true);
        }


        if(savePassword==0)
        {
            user->setSavePassword(false);
        }
        else
        {
            user->setSavePassword(true);
        }

        list.append(user);
    }
    return list;
}

void UserDB::createTable()
{
    QSqlQuery sqlQuery;
    QString sql =  "create table if not exists _user"
                  " ("
                  " id           integer primary key autoincrement , "
                  " username     varchar(64) , "
                  " password     varchar(64) , "
                  " userid       varchar(64) , "
                  " access_token varchar(256) , "
                  " savepassword integer , "
                  " autologin    integer ,"
                  " _datetime    integer "
                  ")";

    qDebug()<< "sql : "<<sql;

    if(sqlQuery.exec(sql))
    {
        qDebug()<<"_user 创建成功";
    }else
    {
        qDebug()<<"_user 创建失败";
        qDebug()<<sqlQuery.lastError().text();
    }
}



// 检查用户是否存在
bool UserDB::checkUserExists(QString username)
{
    QSqlQuery result;
    QString sql = "select username from _user";
    result.exec(sql);
    QList<QString> list;
    while(result.next())
    {
        QString uname= result.value(0).toString();
        list.append(uname);
    }
    for(QString it: list)
    {
        if(it==username)
        {
            return true;
        }
    }
    return false;
}

// 修改保存密码状态
void UserDB::setSavePasswordStatus(QString username, bool status)
{
    QSqlQuery resule;
    if(status)
    {
        QString sql = "update _user set savepassword = 1, _datetime = "+QString::number(QDateTime::currentDateTime().toTime_t())+" where username = '"+username+"'";
        resule.exec(sql);
    }
    else
    {
        QString sql = "update _user set savepassword = 0 , _datetime = "+QString::number(QDateTime::currentDateTime().toTime_t())+" where username = '"+username+"'";
        resule.exec(sql);
    }
}

// 更新自动登录状态
void UserDB::setAutoLoginStatus(QString usernamem, bool status)
{
    QSqlQuery resule ;
    if(status)
    {
        QString sql = "update _user set autologin=1 where username = '"+usernamem+"'";
        resule.exec(sql);
    }
    else
    {
        QString sql = "update _user set autologin=0 where username = '"+usernamem+"'";
        resule.exec(sql);
    }
}

void UserDB::setUserId(QString username, QString userid)
{
    if(checkUserExists(username))
    {
        // 用户存在


    }
    else
    {

    }
}

void UserDB::setAccessToken(QString username, QString accessToken)
{
    if(checkUserExists(username))
    {
        // 用户存在
    }
    else
    {

    }
}


