#ifndef COMMON_H
#define COMMON_H

#include <QString>


class Common
{


private:
    Common();

    QString userid;
    QString accessToken;
    QString baseUrl;
public:
    void setUserid(const QString &userid);

    void setAccessToken(const QString &accessToken);

    void setBaseUrl(const QString &baseUrl);

private:
    static Common *instance;
public:

    static Common* getInstance();

    const QString &getUserid() const;

    const QString &getAccessToken() const;

    const QString &getBaseUrl() const;

};

#endif // COMMON_H
