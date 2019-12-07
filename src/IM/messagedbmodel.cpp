#include "messagedbmodel.h"

MessageDBModel::MessageDBModel()
{
    if (QSqlDatabase::database().tables().contains(_TABLE_NAME_MESSAGE_))
    {
        qDebug() << _TABLE_NAME_MESSAGE_ << " 连接成功";
        return;
    } else
    {
        qDebug() << _TABLE_NAME_MESSAGE_ << " 连接失败 ";
        qDebug() << " 创建消息表 ";
        QSqlQuery sqlQuery;
        if (sqlQuery.exec(_CREATE_TAB_MESSAGE_))
        {
            qDebug() << _TABLE_NAME_MESSAGE_ << "  创建成功";
        } else
        {
            qDebug() << _TABLE_NAME_MESSAGE_ << "  创建失败" << sqlQuery.lastError().text();
        }
    }
}

void MessageDBModel::refresh()
{
    setQuery("select * from _message order by _datetime desc");
}

QHash<int, QByteArray> MessageDBModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[_id] = "_id";
    roles[_roomid] = "_roomid";
    roles[_eventid] = "_eventid";
    roles[_sender] = "_sender";
    roles[_type] = "_type";
    roles[_datetime] = "_datetime";
    roles[_read] = "_read";
    roles[_message] = "_message";
    roles[_me] = "_me";
    roles[_base_server]="_base_server";
    roles[_sendstatus]="_sendstatus";
    return roles;
}

QVariant MessageDBModel::data(const QModelIndex &index, int role) const
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

// 选择了房间
void MessageDBModel::slotsSelectRoom(QString roomid)
{
    qDebug() << " slotsSelectRoom : roomid : " << roomid;

    mRoomId = roomid;

    setQuery("select * from _message where _roomid = '" + roomid + "' order by _datetime desc");
}

// 消息
void MessageDBModel::slotsSendMessage(QString roomid, QString message)
{
    qDebug() << "slotsSendMessage : ";
    qDebug() << "roomid : " << roomid;
    qDebug() << "message : " << message;

    //    "    _id       integer primary key autoincrement,"
    //    "    _roomid   varchar(64),"
    //    "    _eventid  varchar(64),"
    //    "    _sender   varchar(64),"
    //    "    _type     varchar(64),"
    //    "    _datetime bigint,"
    //    "    _read     boolean,"
    //    "    _message  text,"
    //    "    _me       boolean ,"
    //    "    _base_server varchar(256)"


    QString sql = "insert into _message"
                  "("
                  "_roomid ,"
                  "_eventid ,"
                  "_sender ,"
                  "_type ,"
                  "_datetime ,"
                  "_read ,"
                  "_message ,"
                  "_me ,"
                  "_base_server ,"
                  ")"
                  " values"
                  "("
                  "'" + roomid + "',"
                             "'" + roomid + "',"
                             "'" + Common::getInstance()->getUserid() + "',"
                                                         "'_text',"
                                                         "'" + QString::number(QDateTime::currentDateTime().toTime_t()) + "',"
                                                                               "" + QString::number(true) + ","
                                            "'" + message + "',"
                              "" + QString::number(true) + ","
                                            "'" +  Common::getInstance()->getBaseUrl() + "'"
                                                          ")";




    qDebug()<<" sql : "<<sql;

    setQuery(sql);

    refresh();


}

void MessageDBModel::slotsSendMessage(QString roomid, QString message, QString eventid)
{
    QString sql = "insert into _message"
                  "("
                  "_roomid ,"
                  "_eventid ,"
                  "_sender ,"
                  "_type ,"
                  "_datetime ,"
                  "_read ,"
                  "_message ,"
                  "_me ,"
                  "_base_server ,"
                  ")"
                  " values"
                  "("
                  "'" + roomid + "',"
                             "'" + eventid + "',"
                              "'" + Common::getInstance()->getUserid() + "',"
                                                         "'_text',"
                                                         "'" + QString::number(QDateTime::currentDateTime().toTime_t()) + "',"
                                                                               "" + QString::number(true) + ","
                                            "'" + message + "',"
                              "" + QString::number(true) + ","
                                            "'" +  Common::getInstance()->getBaseUrl() + "'"
                                                          ")";




    qDebug()<<" sql : "<<sql;

    setQuery(sql);

    refresh();
}

void MessageDBModel::slotsSendMessage(QString roomid, QString message, QString eventid, bool sendstatus)
{

    mRoomId=roomid;

    QString sql = "insert into _message"
                  "("
                  "_roomid ,"
                  "_eventid ,"
                  "_sender ,"
                  "_type ,"
                  "_datetime ,"
                  "_read ,"
                  "_message ,"
                  "_me ,"
                  "_base_server ,"
                  "_sendstatus"
                  ")"
                  " values"
                  "("
                  "'" + roomid + "',"
                             "'" + eventid + "',"
                              "'" + Common::getInstance()->getUserid() + "',"
                                                         "'_text',"
                                                         "'" + QString::number(QDateTime::currentDateTime().toTime_t()) + "',"
                                                                               "" + QString::number(true) + ","
                                            "'" + message + "',"
                              "" + QString::number(true) + ","
                                            "'" +  Common::getInstance()->getBaseUrl() + "',"
                                                          ""+QString::number(sendstatus)+""
                                                  ")";




    qDebug()<<" sql : "<<sql;

    setQuery(sql);

    refresh();
}


//{
//"content": {
//"body": "nihao ",
//"msgtype": "m.text"
//},
//"event_id": "$NsYyloiwucEMZPB8jBuoUVjlsRIlW5GyplOsdZTT2oc",
//"origin_server_ts": 1575702081577,
//"sender": "@maohuawei1:mhw828.com",
//"type": "m.room.message",
//"unsigned": {
//"age": 182
//}
//}

void MessageDBModel::insert(QMatrixClient::Room *room)
{
    // 连接信号
    QObject::connect(room,
                     &QMatrixClient::Room::aboutToAddNewMessages,
                     room,
                     [this, room](QMatrixClient::RoomEventsRange timeline)
                     {



                         // 别名
                         QString canonical_alias = room->canonicalAlias();
                         // 房间ID
                         QString roomId = room->id();

                         QString eventId;

                         QString senderId;

                         QDateTime datetime;

                         QString type;

                         QString message;

                         qDebug() << " canonical_alias ： " << canonical_alias;

                         qDebug() << " roomId " << roomId;


                         for (const auto &item : timeline)
                         {
                             QString id = item.get()->id();
                             // 消息发送者
                             senderId = item.get()->senderId();
                             datetime = item.get()->timestamp();
                             std::cout << " id : " << id.toStdString() << std::endl;
                             std::cout << " senderId : " << senderId.toStdString() << std::endl;
                             std::cout << " From : " << room->roomMembername(item->senderId()).toStdString()
                                       << std::endl;
                             std::cout << " Timestamp : " << item->timestamp().toString().toStdString() << std::endl;
                             std::cout << " JSON : " << std::endl << item->originalJson().toStdString() << std::endl;

                             // 获取Object 对象
                             QJsonObject object = item->originalJsonObject();

                             if (object.contains("content"))
                             {
                                 QJsonValue values = object.value("content");
                                 QJsonObject object1 = values.toObject();

                                 if (object1.contains("body"))
                                 {
                                     QJsonValue values = object1.value("body");
                                     std::cout << "body :" << values.toString().toStdString() << std::endl;
                                     message = values.toString();
                                 } else
                                 {
                                     std::cout << "不包含: body" << std::endl;
                                 }
                                 if (object1.contains("msgtype"))
                                 {
                                     QJsonValue values = object1.value("msgtype");
                                     std::cout << "msgtype :" << values.toString().toStdString() << std::endl;

                                     type = values.toString();
                                     // 设置消息类型
                                     if (values.toString() == "m.text")
                                     {
                                         // 新消息音频提醒
                                         IMMediaAudio::getInstance()->playMessage();
                                     }
                                 } else
                                 {
                                     std::cout << "不包含: msgtype" << std::endl;
                                 }
                             } else
                             {
                                 std::cout << "不包含: content" << std::endl;
                             }


                             if (object.contains("event_id"))
                             {
                                 eventId = object.value("event_id").toString();
                                 qDebug() << " 事件ID : " << eventId;
                             } else
                             {
                                 qDebug() << "不包含 : " << "event_id";
                             }

                             if (object.contains("origin_server_ts"))
                             {

                                 int origin_server_ts = object.value("origin_server_ts").toInt();
                                 qDebug() << " origin_server_ts : " << origin_server_ts;
                             } else
                             {
                                 qDebug() << "不包含 : " << "origin_server_ts";
                             }

                             if (object.contains("sender"))
                             {
                                 QString sender = object.value("sender").toString();
                                 qDebug() << " sender : " << sender;
                             } else
                             {
                                 qDebug() << "不包含 : " << "sender";
                             }

                             if (object.contains("type"))
                             {
                                 QString type = object.value("type").toString();
                                 qDebug() << " type : " << type;
                             } else
                             {
                                 qDebug() << "不包含 : " << "type";
                             }

                             if (object.contains("unsigned"))
                             {
                                 QJsonValue values = object.value("unsigned");
                                 QJsonObject object1 = values.toObject();

                                 if (object1.contains("age"))
                                 {
                                     int age = object1.value("age").toInt();
                                     qDebug() << " age : " << age;
                                 } else
                                 {
                                     qDebug() << "不包含 : " << "age";
                                 }

                             } else
                             {
                                 qDebug() << "不包含 : " << "unsigned";
                             }

                             if (item->isCallEvent())
                             {
                                 qDebug() << "此事件为电话事件";
                                 QJsonObject obj = item->originalJsonObject();
                                 if (obj.contains(""))
                                 {
                                     QString callId = obj.value("").toString();
                                     // 接听
                                     // 拒绝
                                 }
                             }




                             //insert into _message(_roomid, _eventid, _sender, _type, _datetime, _read, _message, _me, _base_server) values
                             //
                             //
                             //
                             //
                             // ('','','','',1,false,'',false,'');





                             qDebug()<<"localUserid" <<Common::getInstance()->getUserid();
                             qDebug()<<"senderId "<<senderId;

                             bool me = Common::getInstance()->getUserid() == senderId;


                             QString sql = "insert into _message"
                                           "("
                                           " _roomid ,"
                                           " _eventid ,"
                                           " _sender ,"
                                           " _type ,"
                                           " _datetime ,"
                                           " _read ,"
                                           " _message ,"
                                           " _me ,"
                                           " _base_server "

                                           ")"
                                           "values"
                                           "("
                                           "'" + roomId + "',"
                                                      "'" + eventId + "',"
                                                       "'" + senderId + "',"
                                                        "'" + type + "',"
                                                    "" +
                                           QString::number(datetime.toTime_t()) + " ,"
                                                                                  "" + QString::number(true) + " ,"
                                                                     "'" + message + "',"
                                                       "" + QString::number(me) +
                                           " ,"
                                           "'" + Common::getInstance()->getBaseUrl() + "'"
                                                                                   ")";

                             qDebug() << " sql : " << sql;
                             setQuery(sql);
                             refresh();

                         }
                     });
}
