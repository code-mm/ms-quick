import QtQuick 2.0

// 自定义背景

Item {
    property alias visibleRec: rec.visible
    property alias source: image.source
    property alias color: rec.color
    width: 30
    height: 30
    visible: true
    Rectangle {
        id: rec
        width: 30
        height: 30
        color: "#bdbdbd"
        opacity: 0.5
        visible: false
    }
    Image {
        anchors.centerIn: parent
        id: image
        source: "qrc:/images/img_qr.png"
    }
}
