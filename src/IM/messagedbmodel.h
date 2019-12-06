#ifndef MESSAGEDBMODEL_H
#define MESSAGEDBMODEL_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QDir>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QStringListModel>
#include "message.h"
#include "../common.h"

class MessageDBModel : public QSqlQueryModel
{
    Q_OBJECT
public:

    enum MessageRoles
    {
        id =Qt::UserRole + 1,//257
        roomid,
        eventid,
        sender,
        type,
        datetime,
        read,
        message,
        me
    };

    MessageDBModel();

    void refresh();

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void sendMessage(const QString &recipient, const QString &message);

    Q_INVOKABLE void insert(Message message);

signals:

public slots:

    void  slotsSelectRoom(QString roomid);

    void slotsSendMessage(QString roomid,QString message);

private:

    QString mRoomId;
};

#endif // MESSAGEDBMODEL_H
