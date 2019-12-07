#ifndef ROOMDBMODEL_H
#define ROOMDBMODEL_H


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
#include "sqlconstant.h"


//CREATE TABLE _room
//(
//        _id           integer primary key autoincrement,
//        _roomid       varchar(64),
//_name         varchar(256),
//        _avatar       varchar(1024),
//_membercount  intger,
//        _member_1name varchar(256)
//);





// 创建表语句
const static QString _CREATE_TABLE_ROOM_ = "CREATE TABLE _room"
                                           "("
                                           "    _id           integer primary key autoincrement,    "
                                           "    _roomid       varchar(64),                          "
                                           "    _name         varchar(256),                         "
                                           "    _avatar       varchar(1024),                        "
                                           "    _membercount  intger,                               "
                                           "    _member_1name varchar(256) ,                        "
                                           "    _base_server  varchar(256) ,                        "
                                           "    _room_version varchar(32)                           "
                                           ")";


const static QString _TABLE_NAME_ROOM_ = "_room";




class RoomDBModel : public QSqlQueryModel
{
Q_OBJECT
public:
    RoomDBModel();

    enum RoomRoles
    {
        _id = Qt::UserRole + 1,//257
        // 房间ID
        _roomid,
        // 房间名称
        _name,
        // 房间头像
        _avatar,
        // 房间人员数
        _membercount,
        // 两人对话，的人员名称
        _member_1name
    };




    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void refresh();

    void initModel();

    // 插入房间信息
    Q_INVOKABLE void insert(QMatrixClient::Room *room, QMatrixClient::Connection *connection);
    // 加载房间
    Q_INVOKABLE void loadRoom();
    // 加载好友
    Q_INVOKABLE void loadBuddy();

private:
    // 检查房间是否存在
    bool checkRoomExists(QString roomid);
};

#endif // ROOMDBMODEL_H
