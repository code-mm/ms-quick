#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QGuiApplication>
#include <QObject>
#include <QClipboard>

// 剪切板 复制
class Clipboard : public QObject
{
    Q_OBJECT
public:
    explicit Clipboard(QObject *parent = nullptr);
    Q_INVOKABLE void setText(QString text);
private:
    QClipboard *clipboard;
};

#endif // CLIPBOARD_H

