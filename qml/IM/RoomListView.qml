import QtQuick 2.0

import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import EmojiModel 0.1

import "../Home"
import "../BasicComponent/Button"
import "../BasicComponent/PopupFrame"
import "../Emoji"
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

    // 房间ID
    property string mRoomId;
    // 任务
    property bool task: false


    PopupFrame {
        id: popupFrameInfoData
        x: 20
        y: 20
        nowPoint: Qt.point(20,20)
        width: 300
        height: 480
        title: "资料"
        PopupFrameContentItem {
            Text {
                anchors.centerIn: parent
                text: " 房间ID : "+mRoomId
            }
        }
    }

    // 房间列表
    Row {
        width: parent.width
        height: parent.height

        // 左侧显示列表
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
                            navigation.roomColor="#ff00ff"
                            navigation.buddyColor="#11ffaa"
                            // 选择房间
                            roomDbModel.loadRoom()
                        }
                        else if(position==1)
                        {
                            navigation.roomColor="#11ffaa"
                            navigation.buddyColor="#ff00ff"
                            // 选择好友
                            roomDbModel.loadBuddy()
                        }
                    }
                }
            }


            Rectangle{
                width: parent.width
                height: parent.height-60
                color: "#87CEFA"


                ListView{
                    id:listViewRoomList
                    width: parent.width
                    height: parent.height
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
                            height: 80
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
                                        text:   _name==""? _member_1name :_name
                                        font: font.pixelSize=18
                                    }
                                }
                            }

                            // 右键菜单
                            ListMenuRight{
                                backgroundWidth: 100
                                backgroundHeight: 120
                                id:listMenuRight
                                contentItem: ListView {
                                    id: langListView
                                    anchors.fill: parent
                                    anchors.margins: 2
                                    spacing: 4
                                    clip: true
                                    model: ListModel{
                                        ListElement{
                                            name : "查看资料"
                                        }
                                        ListElement{
                                            name : "复制ID"
                                        }
                                        ListElement{
                                            name : "删除"
                                        }
                                    }
                                    delegate: TextButton {
                                        width: langListView.width
                                        height: 36
                                        text: modelData
                                        color: containsMouse ? "lightgray" : listMenuRight.barColor
                                        onClicked: {
                                            // 点击之后让面板隐藏
                                            listMenuRight.hide()

                                            if(index==0)
                                            {
                                                popupFrameInfoData.open();
                                            }else if(index == 1)
                                            {
                                                // 复制房间ID
                                                clipboard.setText(mRoomId)
                                            }else if(index == 2)
                                            {

                                            }
                                        }
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
                                acceptedButtons: Qt.LeftButton | Qt.RightButton // 激活右键（别落下这个）
                                onDoubleClicked: {

                                }
                                onClicked: {
                                    listViewRoomList.currentIndex = index;
                                    mRoomId=_roomid;
                                    if (mouse.button == Qt.RightButton) { // 右键菜单
                                        //
                                        // 鼠标按下的 x y 坐标
                                        console.log("x : "+mouse.x)
                                        console.log("y : "+mouse.y)

                                        // 赋值给 启始 位置的x y 坐标
                                        listMenuRight.startX= mouse.x
                                        listMenuRight.startY= mouse.y

                                        // 显示右键菜单
                                        listMenuRight.show();
                                    }

                                    messageDbModel.slotsSelectRoom(_roomid);
                                    roomMemberDbModel.slotsLoadrMember(_roomid);

                                    if(!listViewRoomList.activeFocus){
                                        listViewRoomList.forceActiveFocus();
                                    }
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

        // 消息区域
        Row{
            width: parent.width/4*3
            height: parent.height
            // 消息
            Column{

                width: parent.width/3*2
                height: parent.height

                Rectangle{
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width-50
                    height: 80
                    color: "#0088aa"

                    Button{
                        text:  "创建任务"
                        onClicked: {
                            task=!task
                        }
                    }
                }

                // 消息列表
                ListView {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width-50
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
                        readonly property bool sentByMe: _me

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
                                    text: _message
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
                            text: Qt.formatDateTime(new Date(_datetime*1000), "d MMM hh:mm")
                            color: "lightgrey"
                            anchors.right: sentByMe ? parent.right : undefined
                        }

                        CheckBox{

                            text: "选择"
                            visible: task
                        }
                    }
                    ScrollBar.vertical: ScrollBar {}
                }






                Rectangle{
                    id:rectangleBottom
                    width: parent.width-50
                    height: parent.height/3-80
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#f0f0f0"



                    Column {
                        width: parent.width
                        height: parent.height
                        // 发送文件，语音，视频，表情选择的那一栏
                        Rectangle{
                            id:rectangleMediaunctions
                            width: parent.width
                            height: parent.height/6
                            color: "#f8aa00"

                            Row{
                                width: parent.width
                                height: parent.height
                                Rectangle{
                                    width: 50
                                    height: parent.height
                                    color: "transparent"
                                    Image {
                                        anchors.centerIn: parent
                                        width: 20
                                        height: 20
                                        source: "qrc:/images/img_emoji.png"

                                        MouseArea{
                                            anchors.fill:parent
                                            onClicked: {
                                                console.log("表情")
                                                rectangleEmoji.visible=!rectangleEmoji.visible
                                            }
                                        }
                                    }
                                }

                                Rectangle{
                                    width: 50
                                    height: parent.height
                                    color: "transparent"
                                    Image {
                                        anchors.centerIn: parent
                                        width: 20
                                        height: 20
                                        source: "qrc:/images/img_file.png"
                                    }
                                }

                                Rectangle{
                                    width: 50
                                    height: parent.height
                                    color: "transparent"
                                    Image {
                                        anchors.centerIn: parent
                                        width: 20
                                        height: 20
                                        source: "qrc:/images/img_video.png"
                                    }
                                }

                                Rectangle{
                                    width: 50
                                    height: parent.height
                                    color: "transparent"
                                    Image {
                                        anchors.centerIn: parent
                                        width: 20
                                        height: 20
                                        source: "qrc:/images/img_voice.png"
                                    }
                                }
                            }
                        }

                        // 消息输入框
                        Rectangle{
                            id: rectangleEditTextFrame
                            width: parent.width
                            height: parent.height/6*4
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "#adadda"
                            //                            TextArea {
                            //                                width: parent.width
                            //                                height: parent.height
                            //                                id: textAreaMessage
                            //                                Layout.fillWidth: true
                            //                                placeholderText: qsTr("请输入消息")
                            //                                wrapMode: TextArea.Wrap
                            //                                font: font.pixelSize=15
                            //                            }

                            Keys.onUpPressed: vbar.decrease()
                            Keys.onDownPressed: vbar.increase()

                            // 可拖放文本控件
                            TextEdit{
                                id: textAreaMessage
                                height: parent.height
                                width: parent.width

                                wrapMode: TextEdit.Wrap
                                selectByKeyboard: true
                                selectByMouse: true
                                font: font.pixelSize=15

                                DropArea{
                                    anchors.fill: parent
                                    onDropped: {
                                        if (drop.hasUrls){
                                            console.debug("拖放了文件: " + drop.urls.length);
                                            for(var i = 0; i < drop.urls.length; i++){
                                                console.debug("文件: " + drop.urls[i]);
                                                textAreaMessage.append("文件: " + drop.urls[i])
                                            }
                                        }
                                        else if (drop.hasText){
                                            console.debug("拖放了本文: " + drop.text.length);
                                            console.debug("文本: " + drop.text);
                                            textAreaMessage.append("文本: " + drop.text)
                                        }
                                    }
                                }

                                MouseArea{
                                    anchors.fill: parent
                                    onWheel: {
                                        if (wheel.angleDelta.y > 0) {
                                            vbar.decrease();
                                        }
                                        else {
                                            vbar.increase();
                                        }
                                    }
                                    onClicked: {
                                        textAreaMessage.forceActiveFocus();
                                    }
                                }
                            }
                            ScrollBar {
                                id: vbar
                                hoverEnabled: true
                                active: hovered || pressed
                                orientation: Qt.Vertical
                                size: rectangleEditTextFrame.height / textAreaMessage.height
                                width: 10
                                anchors.top: parent.top
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                            }
                        }
                        // 发送按钮
                        Rectangle{
                            width: parent.width
                            height: parent.height/6
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "#050505"
                            Button {
                                id: sendButton
                                width: parent.width
                                Layout.fillWidth: true
                                text: qsTr("发送")
                                enabled: textAreaMessage.text.trim().length > 0
                                onClicked: {
                                    // 发送消息
                                    im.sendMessage(mRoomId,textAreaMessage.text)
                                    textAreaMessage.text=''
                                    notificationBox.notify("发送成功")

                                }
                            }
                        }
                    }
                }

                // 表情栏
                Rectangle{
                    id:rectangleEmoji
                    width: parent.width-50
                    height: 230
                    color: "#ffffff"
                    anchors.bottom: rectangleBottom.top
                    anchors.margins: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: false
                    EmojiPicker {
                        width: parent.width
                        height: parent.height
                        anchors.centerIn: parent
                        Layout.fillWidth: true
                        id: emojiPicker
                        visible: true
                        textArea: textAreaMessage
                        emojiModel: EmojiModel { id: emojiModel }
                    }
                }
            }

            // 最右侧
            Rectangle{
                width: parent.width/3-100
                height: parent.height
                color: "#FFFAF0"

                Column{
                    width: parent.width
                    height: parent.height
                    Text {
                        text: qsTr("房间成员")
                        anchors.horizontalCenter:  parent.horizontalCenter
                        font: font.pixelSize=25
                    }

                    // 右侧房间人员
                    ListView{
                        id:listViewRoomMember
                        width: parent.width
                        height: parent.height
                        spacing: 12
                        verticalLayoutDirection: ListView.BottomToTop
                        cacheBuffer: 50
                        focus: true
                        clip: true

                        model: roomMemberDbModel
                        delegate: Component{
                            Item {
                                width: parent.width
                                height: 40

                                Row{
                                    width: parent.width
                                    height: parent.height
                                    Rectangle{
                                        width: 50
                                        height: parent.height
                                        color: "transparent"

                                        Image {
                                            source: "qrc:/images/img_default.png"
                                            width: 20
                                            height: 20
                                            anchors.centerIn: parent
                                            anchors.leftMargin: 10
                                        }
                                    }

                                    Label {
                                        anchors.leftMargin: 10
                                        anchors.verticalCenter:  parent.verticalCenter
                                        text: _name
                                        font: font.pixelSize=15
                                    }
                                }

                                states: State {
                                    name: "Current"
                                    when: listViewRoomMember.isCurrentItem
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
                                        listViewRoomMember.currentIndex = index;
                                        if(!listViewRoomMember.activeFocus){
                                            listViewRoomMember.forceActiveFocus();
                                        }
                                    }
                                }
                            }
                        }
                        ScrollBar.vertical: ScrollBar {}
                        //高亮
                        highlight:    Component {
                            Rectangle {
                                width: listViewRoomMember.width; height: 50
                                color: "#FFFF88"
                                y: listViewRoomMember.currentItem.y;
                                Behavior on y { SpringAnimation { spring: 1; damping: 0.2 } }
                            }
                        }
                    }
                }
            }
        }
    }
}

