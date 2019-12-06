#include "messagedbmodel.h"

MessageDBModel::MessageDBModel()
{
    if (QSqlDatabase::database().tables().contains("_message")) {
        qDebug()<<"_message 连接成功";
        //refresh();
        return;
    }
    else
    {
        qDebug()<< " _message 连接失败 ";
        qDebug()<< " 创建消息表 ";
        QSqlQuery sqlQuery;
        if(sqlQuery.exec(
                "create table if not exists _message"
                "("
                " id       integer primary key autoincrement,"
                " roomid   varchar(64),"
                " eventid  varchar(64),"
                " sender   varchar(64),"
                " type     varchar(64),"
                " datetime bigint,"
                " read     int,"
                " message  text,"
                " me  int "
                " )"
                ))
        {
            qDebug()<<"创建成功" ;
        }else{
            qDebug()<<"创建失败"<<sqlQuery.lastError().text();
        }
    }
}

void MessageDBModel::refresh()
{
    setQuery("select * from _message order by datetime desc");
}
QHash<int, QByteArray> MessageDBModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[id] = "id";
    roles[roomid] = "roomid";
    roles[eventid] = "eventid";
    roles[sender] = "sender";
    roles[type] = "type";
    roles[datetime] = "datetime";
    roles[read] = "read";
    roles[message] = "message";
    roles[me] = "me";
    return roles;
}

QVariant MessageDBModel::data(const QModelIndex &index, int role) const
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

void MessageDBModel::sendMessage(const QString &recipient, const QString &message)
{

}

void MessageDBModel::insert(Message message)
{
    QSqlQuery sqlQuery;
    QString roomid=    message.getRoomid();
    QString sender=  message.getSender();
    QString msg= message.getMessage();
    int datetime=message.getDateTime().toTime_t();
    qDebug()<<"时间戳 : "<<datetime;

    QString type;
    if(message.getType()==TYPE::_TEXT)
    {
        type="_text";
    }
    if(message.getType()==TYPE::_FILE)
    {
        type="_file";
    }

    if(message.getType()==TYPE::_EMAJO)
    {
        type="_emajo";
    }

    int  me=0;


    qDebug()<<"登录的用户ID : "<< Common::userid;
    qDebug()<<"发送者用户ID : "<< sender;


    if(Common::userid==sender)
    {
        qDebug()<<"相等";
        me=1;
    }

    QString sql= "insert into _message (roomid, eventid, sender, type, datetime, read, message, me) values ('"+roomid+"','null','"+sender+"','"+type+"',"+QString::number(datetime)+","+QString::number(1)+",'"+msg+"',"+QString::number(me)+")";

    qDebug()<<"sql : "<<sql;

    if( sqlQuery.exec(sql))
    {

        qDebug()<<"数据存入成功 ";

        setQuery("select * from _message where roomid = '"+mRoomId+"' order by datetime desc");

    }
    else
    {
        qDebug()<<"数据存入失败 : "<< sqlQuery.lastError().text();
    }
}



void  MessageDBModel::slotsSelectRoom(QString roomid)
{
    qDebug()<<" slotsSelectRoom : roomid : "<<roomid;

    mRoomId=roomid;

    setQuery("select * from _message where roomid = '"+roomid+"' order by datetime desc");


}

void MessageDBModel::slotsSendMessage(QString roomid,QString message)
{
    qDebug()<<"slotsSendMessage : ";
    qDebug()<<"roomid : "<< roomid;
    qDebug()<<"message : "<< message;


    Message msg;
    msg.setDateTime(QDateTime::currentDateTime());
    msg.setSender(Common::userid);
    msg.setRoomid(roomid);
    msg.setType(TYPE::_TEXT);
    msg.setMessage(message);
    insert(msg);

}




