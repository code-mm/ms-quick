#include "roomdbmodel.h"

RoomDBModel::RoomDBModel()
{

    if (QSqlDatabase::database().tables().contains("_room")) {
        qDebug()<<"_room 连接成功";
        refresh();
        return;
    }
    else
    {
        qDebug()<< " _room 连接失败 ";
        qDebug()<< " 创建房间表 ";
        QSqlQuery sqlQuery;
        //member_1name 如果房间名称为空，说明是两个人对话，去除里面成员的姓名
        if(sqlQuery.exec(
                "create table if not exists _room"
                "("
                " id       integer primary key autoincrement,"
                " roomid   varchar(64),"
                " name  varchar(256),"
                " avatar   varchar(1024),"
                " membercount     intger,"
                " member_1name     varchar(256)"
                " )"
                ))
        {
            qDebug()<<"创建成功" ;
        }else{
            qDebug()<<"创建失败"<<sqlQuery.lastError().text();
        }
    }
}


QHash<int, QByteArray> RoomDBModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[id] = "id";
    roles[roomid] = "roomid";
    roles[name] = "name";
    roles[avatar] = "avatar";
    roles[membercount] = "membercount";
    roles[member_1name] = "member_1name";
    return roles;
}

void RoomDBModel::refresh()
{
    setQuery("select * from _room where name != '' ");
}

void RoomDBModel::insert(QMatrixClient::Room *room,QMatrixClient::Connection *connection)
{

    bool exists=checkRoomExists(room->id());

    if(room->name()==nullptr||room->name()=="")
    {

        qDebug()<<"房间名称为空 两人对话: ";

        // 如果房间名称为空
        auto r= connection->room(room->id());
        QString member_1name =  r->memberNames().value(0);

        if(exists)
        {
            qDebug()<<"房间已经存在 更新信息";
            // 有 更新
            QString sql = "update _room set name='"+room->name()+"',avatar='"+room->avatarUrl().toString()+"',membercount="+QString::number(  room->memberCount())+" member_1name = '"+member_1name+"' where roomid = '"+room->id()+"'";
            qDebug()<<"sql : "<<sql;
            setQuery(sql);
        }
        else{
            qDebug()<<"房间不存在 插入";
            // 没有 插入
            QString sql = "insert into _room(roomid,name,avatar,membercount,member_1name) values('"+room->id()+"','"+room->name()+"','"+room->avatarUrl().toString()+"',"+QString::number(room->memberCount())+", '"+member_1name+"')";
            qDebug()<<"sql : "<<sql;
            setQuery(sql);
        }
    }
    else
    {
        if(exists)
        {
            qDebug()<<"房间已经存在 更新信息";
            // 有 更新
            QString sql = "update _room set name='"+room->name()+"',avatar='"+room->avatarUrl().toString()+"',membercount="+QString::number(  room->memberCount())+" where roomid = '"+room->id()+"'";
            qDebug()<<"sql : "<<sql;
            setQuery(sql);
        }
        else{
            qDebug()<<"房间不存在 插入";
            // 没有 插入
            QString sql = "insert into _room(roomid,name,avatar,membercount) values('"+room->id()+"','"+room->name()+"','"+room->avatarUrl().toString()+"',"+QString::number(room->memberCount())+")";
            qDebug()<<"sql : "<<sql;
            setQuery(sql);
        }


    }

}

void RoomDBModel::loadRoom()
{
    setQuery("select  * from _room where name!=''");
}

void RoomDBModel::loadBuddy()
{
    setQuery("select  * from _room where name==''");
}

// 检查房间是否存在
bool RoomDBModel::checkRoomExists(QString roomid)
{
    QSqlQuery result=query();
    result.exec("select roomid from _room");
    QList<QString> list;
    while(result.next())
    {
        QString rid= result.value(0).toString();
        list.append(rid);
    }

    for(auto it : list)
    {
        if(it==roomid)
        {
            return true;
        }
    }
    return  false;
}

QVariant RoomDBModel::data(const QModelIndex &index, int role) const
{
    //qDebug()<<" index : "<<index <<"   role : "<<role;
    QVariant value = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole)
    {
        // qDebug()<<" if : ";
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        //qDebug()<<" else : ";
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}
