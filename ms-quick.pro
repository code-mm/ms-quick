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

CONFIG += c++17

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        src/IM/im.cpp \
        src/IM/immediaaudio.cpp \
        src/IM/message.cpp \
        src/IM/messagedbmodel.cpp \
        src/IM/roomdbmodel.cpp \
        src/IM/roommemberdbmodel.cpp \
        src/IM/user.cpp \
        src/IM/userdb.cpp \
        src/SystemFeatures/clipboard.cpp \
        src/Utils/logutils.cpp \
        src/Utils/systemutils.cpp \
        src/appquickview.cpp \
        src/common.cpp \
        src/homeleftmenumodel.cpp \
        src/iappplugin.cpp \
        src/main.cpp \
        src/Logger/Logger.cpp \
        src/Emoji/emojimodel.cpp

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
    src/SystemFeatures/clipboard.h \
    src/Utils/logutils.h \
    src/Utils/systemutils.h \
    src/appquickview.h \
    src/common.h \
    src/homeleftmenumodel.h \
    src/iappplugin.h \
    src/Logger/Logger.h \
    src/Logger/LoggerTemplate.h \
    src/Emoji/emojimodel.h


LIBS += -L/usr/local/lib/ -lQuotient
LIBS += -L/usr/local/lib/ -lQtOlm
LIBS += -L/usr/local/lib/ -lolm.3
