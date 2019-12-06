import QtQuick 2.0


// 加载中
Item {
    Rectangle{
        visible: false
        id:loading
        anchors{
            centerIn: parent
        }

        color: "#fff"
        width: 200
        height: 200
        Loading{
            anchors.centerIn: parent
            implicitWidth: 35
            implicitHeight: 35
        }
    }
}
