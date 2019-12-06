import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4

import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.1
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3


// 登录页面的背面
// 登录中页面

Item{

    width: parent.width
    height: parent.height
    ColumnLayout {
        id:columnLayoutBack
        width: parent.width
        height: parent.height
        anchors{
            fill: parent
            centerIn: parent
        }
        Image {
            id:imageLogo
            source: "qrc:/images/img_im.png"
            width: 30
            height: 30
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.topMargin: 5
        }
        Loading{
            id:loading
            Layout.alignment: imageLogo.bottom |  Qt.AlignHCenter
            Layout.margins: 10
            implicitWidth: 30
            implicitHeight: 30
        }
        Text {
            id:textLoging
            text: qsTr("登录中...")
            font:font.pixelSize=15
            Layout.alignment: loading.bottom | Qt.AlignHCenter
            Layout.margins: 10
        }
        Button{
            objectName: "buttonCancelLogin"
            id:buttonCancelLogin
            Layout.alignment: textLoging.bottom | Qt.AlignHCenter
            Layout.margins: 10

            text: "取消登录"
            onClicked: {

                flipable.flipped = !flipable.flipped
                im.cancelLogin()
            }

            function err(msg){
                console.log(msg)
                flipable.flipped = !flipable.flipped
                textHint.text=msg;
            }
        }
    }
}
