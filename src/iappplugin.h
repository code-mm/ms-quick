#ifndef IAPPPLUGIN_H
#define IAPPPLUGIN_H

#include <QObject>
#include <QString>
class IAppPlugin
{
public:
    IAppPlugin();

protected:
    virtual void loader(QString pluginName);
};

#endif // IAPPPLUGIN_H
