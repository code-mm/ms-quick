import QtQuick 2.0

// 插件管理
Item {

    width: parent.width

    height: parent.height

    Rectangle{

        width: parent.width
        height: parent.height
        Image {
            width: parent.width
            height: parent.height
            source: "qrc:/images/img_back1.jpg"
        }

    }

    Text {
        text: qsTr("功能开发中...")
        font: font.pixelSize=30
        anchors.centerIn: parent
    }

}
