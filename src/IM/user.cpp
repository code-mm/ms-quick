#include "user.h"

User::User()
{

}

User::User(int id, QString username, QString password)
{
    this->id=id;
    this->username=username;
    this->password=password;
}

int User::getId() const
{
    return id;
}

void User::setId(int value)
{
    id = value;
}

QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &value)
{
    username = value;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &value)
{
    password = value;
}

QString User::getUserid() const
{
    return userid;
}

void User::setUserid(const QString &value)
{
    userid = value;
}

QString User::getAccess_token() const
{
    return access_token;
}

void User::setAccess_token(const QString &value)
{
    access_token = value;
}

bool User::getAutoLogin() const
{
    return autoLogin;
}

void User::setAutoLogin(bool value)
{
    autoLogin = value;
}

bool User::getSavePassword() const
{
    return savePassword;
}

void User::setSavePassword(bool value)
{
    savePassword = value;
}
