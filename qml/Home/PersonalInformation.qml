import QtQuick 2.0

//个人资料
Item {
    width: swipeViewHomeContent.width
    height: swipeViewHomeContent.height
    Rectangle{
        width: parent.width
        height: parent.height
        color: "#ffa001"
    }

    Text {
        text: qsTr("个人资料")
        anchors.centerIn: parent
        font:font.pixelSize=30
    }
}
