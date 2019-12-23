cmake_minimum_required(VERSION 3.15)
# 项目名称 修改
project("ms-quick")

# 判断平台
if (CMAKE_HOST_WIN32)
    message("当前平台 : windows")
    set(WINDOWS 1)
elseif (CMAKE_HOST_APPLE)
    message("当前平台 : osx")
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    message("当前平台 : linux")
    set(LINUX 1)
endif ()


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


# c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ui qrc
set(UI_FILES)
set(RC_FILES)
set(QRC_FILES)


if (MACOS)
    # 配置qt路径
    set(CMAKE_PREFIX_PATH "/Users/maohuawei/dev/Qt/5.14.0/clang_64/lib/cmake")
    set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake")
    include_directories("/usr/local/include")
    link_directories(/usr/local/lib)
elseif (LINUX)

elseif (WINDOWS)

endif ()

# qt 核心控件
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5WebEngine REQUIRED)
find_package(Qt5WebChannel REQUIRED)
find_package(Qt5Multimedia REQUIRED)


# 第三方
find_package(Quotient REQUIRED)
find_package(Olm REQUIRED)
find_package(QtOlm REQUIRED)
find_package(yarpl REQUIRED)
find_package(rsocket REQUIRED)


# 添加代码文件
add_executable(ms-quick
        src/Emoji/emojimodel.cpp
        src/Emoji/emojimodel.h
        src/IM/im.cpp
        src/IM/im.h
        src/IM/immediaaudio.cpp
        src/IM/immediaaudio.h
        src/IM/message.cpp
        src/IM/message.h
        src/IM/messagedbmodel.cpp
        src/IM/messagedbmodel.h
        src/IM/roomdbmodel.cpp
        src/IM/roomdbmodel.h
        src/IM/roommemberdbmodel.cpp
        src/IM/roommemberdbmodel.h
        src/IM/sqlconstant.h
        src/IM/user.cpp
        src/IM/user.h
        src/IM/userdb.cpp
        src/IM/userdb.h
        src/Logger/LoggerTemplate.h
        src/Logger/Logger.h
        src/Logger/Logger.cpp
        src/SystemFeatures/clipboard.cpp
        src/SystemFeatures/clipboard.h
        src/Utils/systemutils.h
        src/Utils/systemutils.cpp
        src/Utils/logutils.cpp
        src/Utils/logutils.h
        src/appquickview.h
        src/appquickview.cpp
        src/common.h
        src/common.cpp
        src/homeleftmenumodel.h
        src/homeleftmenumodel.cpp
        src/iappplugin.cpp
        src/iappplugin.h
        src/main.cpp

        qml.qrc
        images.qrc
        media.qrc
        )


# 链接库文件
target_link_libraries(ms-quick Qt5::Core)
target_link_libraries(ms-quick Qt5::Gui)
target_link_libraries(ms-quick Qt5::Widgets)
target_link_libraries(ms-quick Qt5::Quick)
target_link_libraries(ms-quick Qt5::Sql)
target_link_libraries(ms-quick Qt5::Network)
target_link_libraries(ms-quick Qt5::WebEngine)
target_link_libraries(ms-quick Qt5::WebChannel)
target_link_libraries(ms-quick Qt5::Multimedia)

target_link_libraries(ms-quick Quotient)
target_link_libraries(ms-quick QtOlm)
target_link_libraries(ms-quick yarpl)


