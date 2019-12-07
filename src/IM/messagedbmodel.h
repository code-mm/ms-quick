#ifndef MESSAGEDBMODEL_H
#define MESSAGEDBMODEL_H

#include <QObject>
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

#include <iostream>


#include "events/event.h"
#include "connection.h"
#include "room.h"
#include "user.h"
#include "csapi/room_send.h"
#include "csapi/joining.h"
#include "csapi/leaving.h"
#include "events/simplestateevents.h"
#include "events/eventloader.h"


#include "message.h"
#include "../common.h"
#include "sqlconstant.h"
#include "immediaaudio.h"


//CREATE TABLE _message
//(
//        _id       integer primary key autoincrement,
//        _roomid   varchar(64),
//_eventid  varchar(64),
//        _sender   varchar(64),
//_type     varchar(64),
//        _datetime bigint,
//_read     int,
//_message  text,
//        _me       int
//);



// 创建表
const static QString _CREATE_TAB_MESSAGE_ = "CREATE TABLE _message"
                                            "("
                                            "    _id       integer primary key autoincrement,"
                                            "    _roomid   varchar(64),"
                                            "    _eventid  varchar(64),"
                                            "    _sender   varchar(64),"
                                            "    _type     varchar(64),"
                                            "    _datetime bigint,"
                                            "    _read     boolean,"
                                            "    _message  text,"
                                            "    _me       boolean ,"
                                            "    _base_server varchar(256) ,"
                                            "    _sendstatus boolean "
                                            
                                            ")";

const static QString _TABLE_NAME_MESSAGE_ = "_message";


class MessageDBModel : public QSqlQueryModel
{
    Q_OBJECT
public:

    enum MessageRoles
    {
        _id = Qt::UserRole + 1,//257
        _roomid,
        _eventid,
        _sender,
        _type,
        _datetime,
        _read,
        _message,
        _me,
        _base_server,
        _sendstatus
    };

    MessageDBModel();

    void refresh();

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    // 将房间信息消息插入数据库
    void insert(QMatrixClient::Room *room);


signals:

public slots:

    void slotsSelectRoom(QString roomid);

    void slotsSendMessage(QString roomid, QString message);

    void slotsSendMessage(QString roomid, QString message,QString eventid);

     void slotsSendMessage(QString roomid, QString message,QString eventid,bool sendstatus);

private:

    QString mRoomId;
};

#endif // MESSAGEDBMODEL_H
