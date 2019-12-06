cmake_minimum_required(VERSION 3.15)
# 项目名称 修改
project("ms-quick")

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# 配置qt路径
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.13.2/lib/cmake")
# matrix sdk
include_directories("libs/libQuotient/lib")
# 网络请求库
include_directories("libs/QtNetworkService/Src")


# qt 核心控件
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5WebEngine REQUIRED)
find_package(Qt5WebChannel REQUIRED)


set(UI_FILES)
set(RC_FILES)
set(QRC_FILES)


# 添加代码文件
add_executable(ms-quick
        src/main.cpp
        src/common.h
        src/common.cpp
        src/appquickview.h
        src/appquickview.cpp
        src/homeleftmenumodel.h
        src/homeleftmenumodel.cpp
        src/iappplugin.h
        src/iappplugin.cpp
        src/Logger/LoggerTemplate.h
        src/Logger/Logger.h
        src/Logger/Logger.cpp
        src/Utils/systemutils.h
        src/Utils/systemutils.cpp
        src/IM/im.h
        src/IM/im.cpp
        src/IM/message.h
        src/IM/message.cpp
        src/IM/messagedbmodel.h
        src/IM/messagedbmodel.cpp
        src/IM/roomdbmodel.h
        src/IM/roomdbmodel.cpp
        src/IM/user.h
        src/IM/user.cpp
        src/IM/userdb.h
        src/IM/userdb.cpp
        qml.qrc
        images.qrc
        )



# 链接库文件
target_link_libraries(ms-quick Qt5::Core)
target_link_libraries(ms-quick Qt5::Gui)
target_link_libraries(ms-quick Qt5::Widgets)
target_link_libraries(ms-quick Qt5::Quick)
target_link_libraries(ms-quick Qt5::Sql)
target_link_libraries(ms-quick Qt5::Network)
target_link_libraries(ms-quick Qt5::Qt5WebEngine)
target_link_libraries(ms-quick Qt5::Qt5WebChannel)