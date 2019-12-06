import QtQuick 2.0

import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

// 用户名密码输入框
Rectangle {
    id:root
    radius: 4
    width: 260
    height: 80
    border.color: "#bdbdbd"
    border.width: 1

    property alias username: username
    property alias password: password

    property alias usernametext: username.text
    property alias passwordtext: password.text


    ColumnLayout{
        spacing: 0
        TextField{
            id:username
            placeholderText: qsTr("账号/手机/邮箱")

            signal usernameChange(string usernamestr)
            background: Rectangle{
                implicitWidth: root.width
                implicitHeight: root.height/2 //此时用width 和height 输入有问题？？？
                opacity: 0 //为0 是看不见
            }
            validator: RegExpValidator {
                regExp: /^([a-zA-Z0-9]+[_|\_|\.]?)*[a-zA-Z0-9]+@([a-zA-Z0-9]+[_|\_|\.]?)*[a-zA-Z0-9]+\.[a-zA-Z]{2,3}$/
            }

            onTextChanged: username.usernameChange(username.text)
        }
        //中间的横线
        Rectangle{
            width: root.width
            height: 1
            color: root.border.color
        }
        TextField{
            id:password
            signal passwordChange(string passwordstr)
            placeholderText: qsTr("密码")

            echoMode: TextInput.Password

            background: Rectangle{
                implicitWidth: root.width
                implicitHeight: root.height/2
                opacity: 0
            }
            validator: RegExpValidator {
                regExp: /^([a-zA-Z0-9]+[_|\_|\.]?)*[a-zA-Z0-9]+@([a-zA-Z0-9]+[_|\_|\.]?)*[a-zA-Z0-9]+\.[a-zA-Z]{2,3}$/
            }
            onTextChanged: password.passwordChange(password.text)
        }
    }
}
