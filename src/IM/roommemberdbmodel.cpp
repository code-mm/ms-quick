#include "roommemberdbmodel.h"

RoomMemberDBModel::RoomMemberDBModel()
{

    if (QSqlDatabase::database().tables().contains(_TABLE_NAME_ROOM_MEMBER_))
    {
        qDebug() << _TABLE_NAME_ROOM_MEMBER_ << " 连接成功";

        return;
    } else
    {
        qDebug() << _TABLE_NAME_ROOM_MEMBER_ << "  连接失败 ";
        qDebug() << " 创建房间表 ";
        QSqlQuery sqlQuery;
        //member_1name 如果房间名称为空，说明是两个人对话，去除里面成员的姓名
        if (sqlQuery.exec(_CREATE_TABLE_ROOM_MEMBER_))
        {
            qDebug() << _TABLE_NAME_ROOM_MEMBER_ << " 创建成功 ";
        } else
        {
            qDebug() << _TABLE_NAME_ROOM_MEMBER_ << " 创建失败 " << sqlQuery.lastError().text();
        }
    }
}
QVariant RoomMemberDBModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> RoomMemberDBModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[_id] = "_id";
    roles[_roomid] = "_roomid";
    roles[_name] = "_name";
    roles[_member_id] = "_member_id";
    roles[_online] = "_online";
    roles[_tvatar] = "_tvatar";
    roles[_base_server]="_base_server";
    return roles;
}

void RoomMemberDBModel::loadMembers(QMatrixClient::Room *room, QMatrixClient::Connection* connection)
{

    auto* r=  connection->room(room->id());

    qDebug()<<"loadMembers";
    qDebug()<<"r->memberNames().size() : "<< r->memberNames().size();
    qDebug()<<"r->joinedCount()"<<r->joinedCount();



    if(!r)
    {
        qDebug()<<"!r";
        return;
    }

    if (r->memberNames().size() >= r->joinedCount())
    {
        return;
    }


    r->setDisplayed();
    connect(r, &QMatrixClient::Room::allMembersLoaded, [this,r] {

        QStringList memberList = r->memberNames();


        for(QString item : memberList)
        {
            qDebug()<<"loadMembers  name : "<<item;


            //insert into _room_member(_roomid, _name, _member_id, _online, _tvatar, _base_server) values ('','','','','','');

            QString sql = "insert into _room_member"
                          "("
                          "_roomid ,"
                          "_name ,"
                          "_member_id ,"
                          "_online ,"
                          "_tvatar ,"
                          "_base_server "
                          ")"
                          "values"
                          "("
                          "'"+r->id()+"',"
                                      "'"+item+"',"
                                   "'""',"
                                   "'""',"
                                   ""+QString::number(true)+","
                                                    "'"+Common::getInstance()->getBaseUrl()+"'"
                                                                  ")"

                ;


            qDebug()<<" sql : " << sql;

            setQuery(sql);

        }
    });



}

void RoomMemberDBModel::slotsLoadrMember(QString roomid)
{

    qDebug()<<"roomid : "<<roomid;

    mRoomid=roomid;
    refresh();
}

void RoomMemberDBModel::refresh()
{
    setQuery("select * from _room_member where _roomid = '"+mRoomid+"'");
}
