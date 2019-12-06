import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import Qt.labs.platform 1.1
import QtQuick.Layouts 1.3
import "qrc:/qml/Home"
import "qrc:/qml/Login"
Item{

    objectName: "itemMainRootObject"
    id:itemMainRoot
    width: Screen.width/6*5
    height: Screen.height/6*5

    // 登录成功跳转函数
    function loginSuccess(msg){
        console.log("msg:"+msg)
        home.visible=true
        rectangleLoginHome.visible=false
    }

    // 背景图片
    Image {
        width: parent.width
        height:parent.height
        source: "qrc:/images/img_back1.jpg"
    }


    // 错误提示框
    Toast{
        text: "hint"
        visible: false
        parent: itemMainRoot.overlay
        font.pixelSize: 14
    }


    // 登录界面
    Rectangle{
        id:rectangleLoginHome
        width: 321
        height:481
        anchors.centerIn: parent
        opacity:0.8

        LoginHome{

        }
    }

    Home{
        id:home
        visible: false
    }


    //    Item {
    //        id:itemLoadingMain
    //        visible: false
    //        width: parent.width
    //        height: parent.height
    //        Rectangle{
    //            opacity:0.5
    //            color: "#000000"
    //            visible: true
    //            id:loading
    //            anchors{
    //                centerIn: parent
    //            }
    //            width: parent.width
    //            height: parent.height
    //            Loading{
    //                anchors.centerIn: parent
    //                implicitWidth: 35
    //                implicitHeight: 35
    //            }
    //        }
    //    }

    // 托盘
    Tray{

    }
}
