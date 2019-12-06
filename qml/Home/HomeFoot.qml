import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.0
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.1

// 底部导航


// 底部导航
TabBar {
    width: parent.width
    height: 40
    TabButton {
        text: qsTr("消息任务")
        width: Math.max(80, tabBarHomeFoot.width / 6)
        onCanceled: {
            swipeViewHomeContent.setCurrentIndex(0)

        }
    }
    TabButton {
        text: qsTr("组织制度")
        width: Math.max(80, tabBarHomeFoot.width / 6)
        onClicked: {

            swipeViewHomeContent.setCurrentIndex(2)
        }
    }
    TabButton {
        text: qsTr("知识业务")
        width: Math.max(80, tabBarHomeFoot.width / 6)
        onCanceled: {

            swipeViewHomeContent.setCurrentIndex(4)
        }
    }
    TabButton {
        text: qsTr("我的资料")
        width: Math.max(80, tabBarHomeFoot.width / 6)
        onCanceled: {
            swipeViewHomeContent.setCurrentIndex(6)
        }

    }
    TabButton {
        text: qsTr("附近发现")
        width: Math.max(80, tabBarHomeFoot.width / 6)
        onCanceled: {
            swipeViewHomeContent.setCurrentIndex(7)
        }
    }
    TabButton {
        text: qsTr("其他功能")
        width: Math.max(80, tabBarHomeFoot.width / 6)
        onCanceled: {
            swipeViewHomeContent.setCurrentIndex(8)
        }
    }
}

