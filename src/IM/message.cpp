#include "message.h"

Message::Message()
{

}

QString Message::getRoomid() const
{
    return roomid;
}

QString Message::getSender() const
{
    return sender;
}

void Message::setSender(const QString &value)
{
    sender = value;
}

QString Message::getMessage() const
{
    return message;
}

void Message::setMessage(const QString &value)
{
    message = value;
}

TYPE Message::getType() const
{
    return type;
}

void Message::setType(const TYPE &value)
{
    type = value;
}

QDateTime Message::getDateTime() const
{
    return dateTime;
}

void Message::setDateTime(const QDateTime &value)
{
    dateTime = value;
}

bool Message::getIsMe() const
{
    return isMe;
}

void Message::setIsMe(bool value)
{
    isMe = value;
}

bool Message::getIsRead() const
{
    return isRead;
}

void Message::setIsRead(bool value)
{
    isRead = value;
}

bool Message::getIsMessageSendSuccess() const
{
    return isMessageSendSuccess;
}

void Message::setIsMessageSendSuccess(bool value)
{
    isMessageSendSuccess = value;
}

QString Message::getEventId() const
{
    return eventId;
}

void Message::setEventId(const QString &value)
{
    eventId = value;
}

void Message::setRoomid(const QString &value)
{
    roomid = value;
}
