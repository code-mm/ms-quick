#include "common.h"


Common *Common::instance = nullptr;

Common::Common()
{

}

Common *Common::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Common();
    }
    return instance;
}

const QString &Common::getUserid() const
{
    return userid;
}

const QString &Common::getAccessToken() const
{
    return accessToken;
}

const QString &Common::getBaseUrl() const
{
    return baseUrl;
}

void Common::setUserid(const QString &userid)
{
    Common::userid = userid;
}

void Common::setAccessToken(const QString &accessToken)
{
    Common::accessToken = accessToken;
}

void Common::setBaseUrl(const QString &baseUrl)
{
    Common::baseUrl = baseUrl;
}
