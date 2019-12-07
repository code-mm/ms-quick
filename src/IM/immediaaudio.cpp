#include "immediaaudio.h"

IMMediaAudio::IMMediaAudio()
{
    mediaPlay=new QMediaPlayer;

    connect(mediaPlay, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
}

void IMMediaAudio::playMessage()
{
    qDebug()<<"播放消息音乐";
    mediaPlay->setMedia(QUrl::fromLocalFile("/Users/maohuawei/project/qt/ms-quick/media/message.mp3"));
    mediaPlay->setVolume(50);
    mediaPlay->play();
}


IMMediaAudio* IMMediaAudio::instance=nullptr;

IMMediaAudio *IMMediaAudio::getInstance()
{

    if(instance==nullptr)
    {
        instance = new IMMediaAudio;
    }

    return instance;
}

void IMMediaAudio::positionChanged(qint64 position)
{

    qDebug()<<"position : "+position;

}
