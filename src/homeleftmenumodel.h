#ifndef HOMELEFTMENUMODEL_H
#define HOMELEFTMENUMODEL_H

#include <QObject>

class HomeLeftMenuModel: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString iconUrl READ iconUrl WRITE setIconUrl NOTIFY iconUrlChanged)
    //![0]

public:
    HomeLeftMenuModel(QObject *parent=0);

    QString name() const;
    void setName(const QString &name);

    QString iconUrl() const;
    void setIconUrl(const QString &iconUrl);

signals:
    void nameChanged();
    void iconUrlChanged();

private:
    QString m_name;
    QString m_iconUrl;
    //![1]
};

#endif // HOMELEFTMENUMODEL_H
