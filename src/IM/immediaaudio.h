#ifndef IMMEDIAAUDIO_H
#define IMMEDIAAUDIO_H

#include <QObject>
#include <QMediaPlayer>
#include <QDebug>
#include <QSound>

class IMMediaAudio : public QObject
{

    Q_OBJECT
private :
    IMMediaAudio();
    static IMMediaAudio* instance;
    QMediaPlayer *mediaPlay;



public:
    static IMMediaAudio* getInstance();
    void playMessage();

private slots:
    void positionChanged(qint64 position);
};

#endif // IMMEDIAAUDIO_H
