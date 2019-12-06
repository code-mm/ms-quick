import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.0
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.1

// 头部导航

TabBar {
    width: parent.width
    height: 40
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("消息")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("任务")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("组织")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("部门知识")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("公司知识")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("个人资料")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("通讯录")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("茶饮")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("咖啡")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("酒吧")
    }
    TabButton {
        width: Math.max(80, tabBarHomeHead.width / 6)
        text: qsTr("店铺")
    }
}



