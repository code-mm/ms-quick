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


class RoomDBModel : public QSqlQueryModel
{
    Q_OBJECT
public:

    enum RoomRoles
    {
        id = Qt::UserRole + 1,//257
        // 房间ID
        roomid,
        // 房间名称
        name,
        // 房间头像
        avatar,
        // 房间人员数
        membercount,
        // 两人对话，的人员名称
        member_1name
    };

    RoomDBModel();

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    void refresh();

    Q_INVOKABLE void insert(QMatrixClient::Room *room,QMatrixClient::Connection *connection);




    // 加载房间
    Q_INVOKABLE void loadRoom();
    // 加载好友
    Q_INVOKABLE void loadBuddy();

    // 检查房间是否存在
    bool checkRoomExists(QString roomid);



private:
};

#endif // ROOMDBMODEL_H
