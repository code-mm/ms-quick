#include <src/common.h>
#include "roomdbmodel.h"

RoomDBModel::RoomDBModel()
{

    if (QSqlDatabase::database().tables().contains(_TABLE_NAME_ROOM_))
    {
        qDebug() << _TABLE_NAME_ROOM_ << " 连接成功";

        initModel();

        return;
    } else
    {
        qDebug() << _TABLE_NAME_ROOM_ << "  连接失败 ";
        qDebug() << " 创建房间表 ";
        QSqlQuery sqlQuery;
        //member_1name 如果房间名称为空，说明是两个人对话，去除里面成员的姓名
        if (sqlQuery.exec(_CREATE_TABLE_ROOM_))
        {
            qDebug() << _CREATE_TABLE_ROOM_ << " 创建成功 ";
        } else
        {
            qDebug() << _CREATE_TABLE_ROOM_ << " 创建失败 " << sqlQuery.lastError().text();
        }

        initModel();
    }
}


QHash<int, QByteArray> RoomDBModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[_id] = "_id";
    roles[_roomid] = "_roomid";
    roles[_name] = "_name";
    roles[_avatar] = "_avatar";
    roles[_membercount] = "_membercount";
    roles[_member_1name] = "_member_1name";
    return roles;
}


QVariant RoomDBModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if (role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    } else
    {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}


void RoomDBModel::refresh()
{
    setQuery("select * from _room where _name != '' ");
}

void RoomDBModel::initModel()
{
    setQuery("select * from _room where _name != '' ");
}

void RoomDBModel::insert(QMatrixClient::Room *room, QMatrixClient::Connection *connection)
{


    QString roomId = room->id();
    QString roomName = room->name();
    QString roomVersion = room->version();
    QString avatar = room->avatarUrl().toString();
    QString roomTopic = room->topic();
    int roomMemberCount = room->memberCount();
    QString roomMemberName = room->memberNames().value(0);

    // 检查房间是否存在
    bool roomExists = checkRoomExists(room->id());
    // 检查房间名称是否为空
    bool roomNameNull = room->name() == nullptr || room->name() == "";

    QString sql;

    // 数据库中没有房间信息
    if (!roomExists)
    {
        // 更新数据库信息
        if (roomNameNull)
        {


            //            insert into _room(_roomid, _name, _avatar, _membercount, _member_1name, _base_server, _room_version)
            //            values ('', '', '', 1, '', '', '');

            // 两个人房间
            sql = "insert into _room "
                  "("
                  " _roomid , "
                  " _name , "
                  " _avatar , "
                  " _membercount , "
                  " _member_1name , "
                  " _base_server , "
                  " _room_version  "
                  ")"
                  "values"
                  "("
                  "'" + roomId + "',"
                             "'" + roomName + "',"
                               "'" + avatar + "',"
                             "" + QString::number(roomMemberCount) + ","
                                                       "'" +
                  roomMemberName + "',"
                                   "'" +
                  Common::getInstance()->getBaseUrl() + "',"
                                                        "'" + roomVersion + "'"
                                  ")";
        } else
        {
            // 多人房间
            // 两个人房间
            sql = "insert into _room "
                  "("
                  " _roomid , "
                  " _name , "
                  " _avatar , "
                  " _membercount , "
                  " _member_1name , "
                  " _base_server , "
                  " _room_version  "
                  ")"
                  "values"
                  "("
                  "'" + roomId + "',"
                             "'" + roomName + "',"
                               "'" + avatar + "',"
                             "" + QString::number(roomMemberCount) + ","
                                                       "'" +
                  roomMemberName + "',"
                                   "'" +
                  Common::getInstance()->getBaseUrl() + "',"
                                                        "'" + roomVersion + "'"
                                  ")";

        }
    }

    // 房间已经存在数据库
    else
    {
        // 将数据插入数据库
        if (roomNameNull)
        {
            // 两个人房间
            //            update _room
            //            set _roomid='',
            //                    _name='',
            //                    _avatar='',
            //                    _membercount=1,
            //                    _member_1name='',
            //                    _base_server='',
            //                    _room_version=''
            //            where _roomid = '';



            sql = "update _room set "
                  " _roomid = '" + roomId + "' ,"
                             " _name = '" + roomName + "' ,"
                               " _avatar = '" + avatar + "' ,"
                             " _membercount = " +
                  QString::number(roomMemberCount) + " ,"
                                                     " _member_1name = '" + roomMemberName + "' ,"
                                     " _base_server = '" +
                  Common::getInstance()->getBaseUrl() + "' ,"
                                                        " _room_version = '" + roomVersion + "' "
                                  " where _roomid= '" + roomId + "'";

        } else
        {
            // 多人房间
            sql = "update _room set "
                  " _roomid = '" + roomId + "' ,"
                             " _name = '" + roomName + "' ,"
                               " _avatar = '" + avatar + "' ,"
                             " _membercount = " +
                  QString::number(roomMemberCount) + " ,"
                                                     " _member_1name = '" + roomMemberName + "' ,"
                                     " _base_server = '" +
                  Common::getInstance()->getBaseUrl()  + "' ,"
                                                        " _room_version = '" + roomVersion + "' "
                                  " where _roomid= '" + roomId + "'";
        }

    }


    qDebug() << " _room sql : " << sql;
    setQuery(sql);
    refresh();
}

// 加载房间
void RoomDBModel::loadRoom()
{
    setQuery("select  * from _room where _name!=''");
}

// 加载成员
void RoomDBModel::loadBuddy()
{
    setQuery("select  * from _room where _name==''");
}

// 检查房间是否存在
bool RoomDBModel::checkRoomExists(QString roomid)
{
    QSqlQuery result = query();
    result.exec("select _roomid from _room");
    QList<QString> list;
    while (result.next())
    {
        QString rid = result.value(0).toString();
        list.append(rid);
    }
    for (auto it : list)
    {
        if (it == roomid)
        {
            return true;
        }
    }
    return false;
}

