
import QtQuick 2.0

// 通知
Rectangle {
    id: root
    implicitWidth: 200
    implicitHeight: 60
    property var control: parent
    x: control.width * 0.5-100
    y: control.height * 5
    color: gConfig.reserverColor
    opacity: 0.7
    Text {
        id: t
        anchors.centerIn: parent
    }
    SequentialAnimation {
        id: ani
        alwaysRunToEnd: false
        NumberAnimation {
            target: root
            property: "y"
            duration: 500
            easing.type: Easing.Linear
            to: control.height * 0.8
        }

        PauseAnimation {
            duration: 2400
        }
        NumberAnimation {
            target: root
            property: "y"
            duration: 500
            easing.type: Easing.Linear
            to: control.height * 1.1
        }

    }
    function notify(msg) {
        t.text = msg
        ani.start()
    }
}
