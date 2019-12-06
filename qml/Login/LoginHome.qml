import QtQuick 2.12
import QtQuick.Window 2.12
import QtQml 2.13

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4

import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.1
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3


// 登录页面 可翻转
Flipable {

    width: 320
    height: 480

    id: flipable
    property bool flipped: false
    clip: true
    front: Item {
        width: parent.width
        height: parent.height
        //Logo
        Image {
            id: imageLogo
            source: "qrc:/images/img_im.png"
            width: 80
            height: 80
            anchors {
                margins: 100
                top: parent.top
                horizontalCenter: parent.horizontalCenter
                topMargin: 35
            }
        }

        // 错误提示
        Text {
            objectName: "textHintObj"
            id: textHint
            text: ""
            anchors {
                top: imageLogo.bottom
                horizontalCenter: parent.horizontalCenter
                topMargin: 15
            }
            function changeHintText(msg) {
                textHint.text = msg
            }
        }

        ColumnLayout {
            anchors {
                //            centerIn: parent
                top: textHint.bottom
                horizontalCenter: parent.horizontalCenter
                topMargin: 15
            }
            RowLayout {
                LoginHomeField {

                    objectName: "LoginHomeField"
                    id: field

                    // 数据库读取账号回显
                    function setUsername(values)
                    {
                        console.log("setUsername")
                        field.usernametext=values
                    }
                    // 数据库读取密码回显
                    function setPassword(values)
                    {
                        console.log("setPassword")
                        field.passwordtext=values
                    }
                }
                ColumnLayout {

                }
            }
            RowLayout {
                objectName: "CheckBoxSavePasswordAutoLogin"
                CheckBox {
                    id: checkBoxSavePassword
                    scale: 1
                    text: "记住密码"
                    onCheckStateChanged: {
                        im.setSavePasswordStatus(field.usernametext,checkBoxSavePassword.checked)
                    }
                }
                CheckBox {
                    id: checkBoxAutoLogin
                    scale: 1
                    text: "自动登录"
                    onCheckStateChanged: {
                        im.setAutoLoginStatus(field.usernametext,checkBoxAutoLogin.checked)
                        if(checkBoxAutoLogin.checked)
                        {
                            checkBoxSavePassword.checked=true
                        }
                    }
                }
                function savePassword(s)
                {
                    console.log("保存密码勾选")
                    checkBoxSavePassword.checked=true
                }

                function autoLogin(s)
                {
                    console.log("自动登录勾选")
                    checkBoxAutoLogin.checked=true
                    flipable.flipped = !flipable.flipped

                }

            }

            LoginHomeButton {
                id: loginButton
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {

                        if (field.usernametext.trim().length == 0) {
                            textHint.text = "请输入账号"
                            return
                        }
                        if (field.usernametext.trim().length < 6) {
                            textHint.text = "请输合法的账号"
                            return
                        }

                        if (field.passwordtext.trim().length == 0) {
                            textHint.text = "请输入密码"
                            return
                        }

                        if (field.passwordtext.trim().length < 6) {
                            textHint.text = "请输入合法的密码"
                            return
                        }


                        im.login(field.usernametext.trim(),
                                 field.passwordtext.trim(),
                                 checkBoxSavePassword.checkState,
                                 checkBoxAutoLogin.checkState
                                 )

                        flipable.flipped = !flipable.flipped
                    }
                    onEntered: {
                        loginButton.color = "#3CC3F5"
                    }
                    onExited: {
                        loginButton.color = "#00A3FF"
                    }
                }
            }
        }

        // 用户名输入处理
        Connections {
            target: field.username
            onUsernameChange: {
                console.log(field.usernametext)
            }
        }
        // 密码输入处理
        Connections {
            target: field.password
            onPasswordChange: {
                console.log(field.passwordtext)
            }
        }

        RowLayout {

            anchors {
                left: parent.left
                leftMargin: 20
                bottom: parent.bottom
                bottomMargin: 20
            }

            Item {
                width: 100
                height: 20

                Text {
                    id: textRegisterAccount
                    text: qsTr("注册账号")
                    color: "#00A3FF"
                    font.pixelSize: 15
                    MouseArea {
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: Qt.openUrlExternally(
                                       "https://www.baidu.com/")
                        onEntered: {
                            textRegisterAccount.color = "#3CC3F5"
                        }
                        onExited: {
                            textRegisterAccount.color = "#00A3FF"
                        }
                    }
                }
            }
            Item {
                width: 100
                height: 20
                Text {
                    id: textFindPassword
                    text: qsTr("找回密码")
                    color: "#00A3FF"
                    font.pixelSize: 15
                    MouseArea {
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: Qt.openUrlExternally(
                                       "https://www.baidu.com/")
                        onEntered: {
                            textFindPassword.color = "#3CC3F5"
                        }
                        onExited: {
                            textFindPassword.color = "#00A3FF"
                        }
                    }
                }
            }
        }

        ImageBackColor {
            id: imageQr
            source: "qrc:/images/img_qrcode.png"
            anchors {
                right: parent.right
                rightMargin: 20
                bottom: parent.bottom
                bottomMargin: 20
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    imageQr.visibleRec = true
                }
                onExited: {
                    imageQr.visibleRec = false
                }
                onClicked: {

                    textHint.text = "功能暂未开发，尽情期待"
                }
            }
        }
    }
    back: LoginHomeBack {}

    transform: Rotation {
        id: rotation
        origin.x: flipable.width / 2
        origin.y: flipable.height / 2
        axis.x: 0
        axis.y: 1
        axis.z: 0
        angle: 0
    }

    states: State {
        name: "back"
        PropertyChanges {
            target: rotation
            angle: 180
        }
        when: flipable.flipped
    }
    transitions: Transition {
        NumberAnimation {
            target: rotation
            properties: "angle"
            duration: 500
        }
    }
}
