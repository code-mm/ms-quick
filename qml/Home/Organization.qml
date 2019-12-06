import QtQuick 2.0

// 组织
Item {
    width: swipeViewHomeContent.width
    height: swipeViewHomeContent.height
    Rectangle{
        width: parent.width
        height: parent.height
        color: "#ffa001"
    }

    Text {
        text: qsTr("组织")
        anchors.centerIn: parent
        font:font.pixelSize=30
    }
}
