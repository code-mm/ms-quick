QT      += core
QT      += gui
QT      += sql
QT      += network
QT      += widgets
QT      += qml
QT      += quick
QT      += webengine
QT      += webchannel
QT      += webenginewidgets
QT      += multimedia

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/IM/im.cpp \
        src/IM/immediaaudio.cpp \
        src/IM/message.cpp \
        src/IM/messagedbmodel.cpp \
        src/IM/roomdbmodel.cpp \
        src/IM/roommemberdbmodel.cpp \
        src/IM/user.cpp \
        src/IM/userdb.cpp \
        src/Utils/logutils.cpp \
        src/Utils/systemutils.cpp \
        src/appquickview.cpp \
        src/common.cpp \
        src/homeleftmenumodel.cpp \
        src/iappplugin.cpp \
        src/main.cpp \
        src/Logger/Logger.cpp

RESOURCES += qml.qrc \
    images.qrc \
    media.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/IM/im.h \
    src/IM/immediaaudio.h \
    src/IM/message.h \
    src/IM/messagedbmodel.h \
    src/IM/roomdbmodel.h \
    src/IM/roommemberdbmodel.h \
    src/IM/sqlconstant.h \
    src/IM/user.h \
    src/IM/userdb.h \
    src/Utils/logutils.h \
    src/Utils/systemutils.h \
    src/appquickview.h \
    src/common.h \
    src/homeleftmenumodel.h \
    src/iappplugin.h \
    src/Logger/Logger.h \
    src/Logger/LoggerTemplate.h



include(libs/libQuotient/libqmatrixclient.pri)
include(libs/QtNetworkService/QtNetworkService.pri)

