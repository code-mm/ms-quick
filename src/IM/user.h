#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(int id,QString username,QString password);

    int getId() const;
    void setId(int value);

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getUserid() const;
    void setUserid(const QString &value);

    QString getAccess_token() const;
    void setAccess_token(const QString &value);

    bool getAutoLogin() const;
    void setAutoLogin(bool value);

    bool getSavePassword() const;
    void setSavePassword(bool value);

private:
    int id;
    QString username;
    QString password;
    QString userid;
    QString access_token;
    // 是否保存密码
    bool savePassword;
    // 是否自动登录
    bool autoLogin;

};

#endif // USER_H
