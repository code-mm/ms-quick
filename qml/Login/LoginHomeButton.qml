import QtQuick 2.0
import QtQuick.Layouts 1.3

// 登录按钮
Rectangle {
    radius: 4
    width: 260
    height: 42
    color: "#00A3FF"
    RowLayout{
        anchors.centerIn: parent
        Text {
            id: text
            text: qsTr("登 录")
            color: "#fff"
            font.pixelSize: 16
        }
    }
}
