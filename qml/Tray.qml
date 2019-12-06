import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4

import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.1
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3

import "qrc:/qml/Home"

// 托盘
SystemTrayIcon {
    visible: true
    icon.source: "qrc:/images/img_icon_blue.png"
    tooltip: "北斗IM"


    menu: Menu {

        MenuItem {
            text: qsTr("在线")
            onTriggered: {

            }
        }

        MenuItem {
            text: qsTr("忙碌")
            onTriggered: {

            }
        }
        MenuItem {
            text: qsTr("隐藏")
            onTriggered: {

            }
        }
        MenuItem {
            text: qsTr("离线")
            onTriggered: {

            }
        }
        MenuSeparator{
        }
        MenuItem {
            text: qsTr("多窗口聊天")
            onTriggered: {

            }
        }
        MenuItem {
            text: qsTr("任务面板")
            onTriggered: {

            }
        }
        MenuItem {
            text: qsTr("索引面板")
            onTriggered: {

            }
        }
        MenuItem {
            text: qsTr("更新邮件")
            onTriggered: {

            }
        }

        MenuSeparator{
        }

        MenuItem {
            text: qsTr("退出")
            onTriggered: {
                Qt.quit()
            }
        }




    }

    // 点击托盘时显示界面
    onActivated:{





        rootWindow.show()
        rootWindow.raise()
        rootWindow.requestActivate()
    }
}

