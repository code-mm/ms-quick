import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import Qt.labs.platform 1.1
import QtQuick.Layouts 1.3


// 任务
Item {
    width: swipeViewHomeContent.width
    height: swipeViewHomeContent.height
    Rectangle{
        width: parent.width
        height: parent.height
        color: "#ffa001"
    }

    Text {
        text: qsTr("任务")
        anchors.centerIn: parent
        font:font.pixelSize=30
    }
}
