#include "homeleftmenumodel.h"



HomeLeftMenuModel::HomeLeftMenuModel(QObject *parent)
{

}

QString HomeLeftMenuModel::name() const
{
    return m_name;
}

void HomeLeftMenuModel::setName(const QString &name)
{
    if(name!=m_name){
        m_name = name;
        emit nameChanged();
    }

}

QString HomeLeftMenuModel::iconUrl() const
{
    return m_iconUrl;
}

void HomeLeftMenuModel::setIconUrl(const QString &iconUrl)
{
    if(iconUrl!=m_iconUrl){
        m_iconUrl = iconUrl;
        emit iconUrlChanged();
    }

}
