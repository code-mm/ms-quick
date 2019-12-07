#ifndef ROOMMEMBERDBMODEL_H
#define ROOMMEMBERDBMODEL_H

#include <QObject>
#include <QString>
#include <QSqlQueryModel>
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
#include "events/event.h"
#include "connection.h"
#include "room.h"
#include "user.h"
#include "csapi/room_send.h"
#include "csapi/joining.h"
#include "csapi/leaving.h"
#include "events/simplestateevents.h"
#include "events/eventloader.h"

#include "../common.h"

static const QString _TABLE_NAME_ROOM_MEMBER_ = "_room_member";


static const QString _CREATE_TABLE_ROOM_MEMBER_="CREATE TABLE _room_member"

                                                  "("
                                                  "_id          integer primary key autoincrement,"
                                                  "    _roomid      varchar(64),"
                                                  "    _name        varchar(256),"
                                                  "    _member_id   varchar(256),"
                                                  "    _online      boolean,"
                                                  "    _tvatar      text,"
                                                  "    _base_server varchar(256)"
                                                  ")"


    ;




class RoomMemberDBModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    RoomMemberDBModel();


    enum RoomMemberRoles
    {
        _id = Qt::UserRole + 1,//257
        _roomid,
        _name,
        _member_id,
        _online,
        _tvatar,
        _base_server
    };


    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void     loadMembers(QMatrixClient::Room *room,QMatrixClient::Connection *connection);


public slots:


    void slotsLoadrMember(QString roomid);

    void refresh();


private:

    QString mRoomid;


};

#endif // ROOMMEMBERDBMODEL_H
