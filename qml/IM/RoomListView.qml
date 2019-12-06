import QtQuick 2.0

import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../Home"
// 房间列表

Rectangle {
    width: parent
    height: parent

    // 背景
    Image {
        width: parent.width
        height: parent.height
        source: "qrc:/images/img_back1.jpg"
    }

    property string mRoomId;



    // 房间列表
    Row {
        width: parent.width
        height: parent.height

        Column{
            width: parent.width/4
            height: parent.height

            // 头部选择导航 好友和房间
            Navigation{
                width: parent.width
                height: 80
                id:navigation

                Connections{
                    onChangeItem: {
                        console.log(position)


                        if(position==0)
                        {
                            // 选择房间
                            roomDbModel.loadRoom()
                        }
                        else if(position==1)
                        {
                            // 选择好友
                            roomDbModel.loadBuddy()
                        }
                    }
                }
            }

            ListView{
                id:listViewRoomList
                width: parent.width
                height: parent.height-60
                model: roomDbModel
                spacing: 4
                cacheBuffer: 10
                focus: true
                clip: true
                boundsBehavior:ListView.SnapToItem
                //高亮
                highlight:    Component {
                    Rectangle {
                        width: listViewRoomList.width; height: 50
                        color: "#FFFF88"
                        y: listViewRoomList.currentItem.y;
                        Behavior on y { SpringAnimation { spring: 1; damping: 0.2 } }
                    }
                }

                // 展示
                delegate:Component{
                    Item{
                        width: parent.width
                        height: 100
                        Row{
                            width: parent.width
                            height: parent.height

                            Rectangle{

                                width: 80
                                height: parent.height
                                color: "transparent"

                                // 头像
                                Image {
                                    anchors.centerIn: parent
                                    source: "qrc:/images/img_default.png"
                                    width: 50
                                    height: 50
                                    scale: 0.5
                                }
                            }

                            Column{
                                width: parent.width-80
                                height: parent.height
                                // 房间名称或者人员名称
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.topMargin: 30
                                    text:   name==""? member_1name :name
                                    font: font.pixelSize=18
                                }
                            }
                        }

                        states: State {
                            name: "Current"
                            when: listViewRoomList.isCurrentItem
                            PropertyChanges { target: content; x: 20 }
                        }
                        transitions: Transition {
                            NumberAnimation { properties: "x"; duration: 200 }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onDoubleClicked: {

                            }
                            onClicked: {
                                listViewRoomList.currentIndex = index;
                                mRoomId=roomid;
                                membercount
                                messageDbModel.slotsSelectRoom(roomid)

                                if(!listViewRoomList.activeFocus){
                                    listViewRoomList.forceActiveFocus();
                                }
                            }
                        }
                    }
                }
            }
        }

        // 消息
        // 上 消息
        // 下 输入框

        Row{
            width: parent.width/4*3
            height: parent.height
            // 消息
            Column{
                width: parent.width/4*3
                height: parent.height

                Rectangle{

                    width: parent.width
                    height: 80
                    color: "#0088aa"
                }


                // 消息列表
                ListView {
                    width: parent.width-20
                    height: parent.height/3*2
                    id: listView
                    spacing: 12
                    verticalLayoutDirection: ListView.BottomToTop
                    model: messageDbModel
                    cacheBuffer: 50
                    focus: true
                    clip: true

                    delegate: Column {
                        anchors.right: sentByMe ? parent.right : undefined
                        readonly property bool sentByMe: me==1

                        Row {
                            id: messageRow
                            spacing: 6
                            anchors.right: sentByMe ? parent.right : undefined

                            // 头像
                            Image {
                                id: avatar
                                source: sentByMe ? "qrc:/images/img_default.png" : "qrc:/images/img_icon_blue.png"
                            }

                            Rectangle {
                                width: Math.min(messageText.implicitWidth + 24, listView.width - avatar.width - messageRow.spacing)
                                height: messageText.implicitHeight + 24
                                color: sentByMe ? "lightgrey" : "steelblue"

                                Label {
                                    id: messageText
                                    text: message
                                    color: sentByMe ? "black" : "white"
                                    anchors.fill: parent
                                    anchors.margins: 12
                                    wrapMode: Label.Wrap
                                    font : font.pixelSize=15
                                }
                            }
                        }

                        Label {
                            id: timestampText
                            text: Qt.formatDateTime(new Date(datetime*1000), "d MMM hh:mm")
                            color: "lightgrey"
                            anchors.right: sentByMe ? parent.right : undefined
                        }
                    }
                    ScrollBar.vertical: ScrollBar {}
                }

                Rectangle{
                    width: parent.width-20
                    height: parent.height/3
                    color: "#f5f6f7"
                    ColumnLayout {
                        width: parent.width

                        // 发送文件，语音，视频，表情选择的那一栏
                        Rectangle{
                            width: parent.width
                            height: 40
                            color: "#f8aa00"
                        }

                        // 消息输入框
                        Rectangle{
                            width: parent.width
                            height:140
                            color: "#adadda"
                            TextArea {
                                width: parent.width
                                height: parent.height
                                id: textAreaMessage
                                Layout.fillWidth: true
                                placeholderText: qsTr("请输入消息")
                                wrapMode: TextArea.Wrap
                                font: font.pixelSize=15
                            }
                        }
                        // 发送按钮
                        Rectangle{
                            width: parent.width
                            height:50
                            color: "#050505"
                            Button {
                                id: sendButton
                                width: parent.width
                                Layout.fillWidth: true
                                text: qsTr("发送")
                                enabled: messageField.length > 0
                                onClicked: {
                                    // 发送消息
                                    im.sendMessage(mRoomId,textAreaMessage.text)
                                    // 将消息插入数据库
                                    messageDbModel.slotsSendMessage(mRoomId,textAreaMessage.text)
                                }
                            }
                        }
                    }
                }
            }


            // 最右侧
            Rectangle{
                width: parent.width/4+100
                height: parent.height
                color: "#ff2a11"

                Column{

                }
            }
        }
    }
}

