import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.1
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3

// 左侧菜单
Rectangle {


    property int iconwidth: 35
    property int iconheight: 35
    property int fontSize: 18


    width: 100
    height: parent.height
    color: "#999999"

    ListView{
        id:listViewHomeLeftMenu
        width: parent.width
        height: parent.height
        model: homeLeftMenuModel
        spacing: 15
        cacheBuffer: 10
        focus: true
        clip: true
        boundsBehavior:ListView.SnapToItem
        Layout.margins: 10

        highlightFollowsCurrentItem: false
        anchors {
            fill: parent
        }
        highlight: Component {
            id: componentHomeLeftMenuListViewhighlightBar
            Rectangle {
                width: 100
                height: 100
                color: "#676767"
                y: listViewHomeLeftMenu.currentItem.y;
                Behavior on y { SpringAnimation { spring: 1; damping:0.2 } }
            }
        }
        delegate:Component{
            Item{
                anchors.horizontalCenter: parent.horizontalCenter
                width: 100
                height: 100
                Column{
                    Layout.margins: 30
                    anchors.centerIn: parent
                    Image {

                        width: iconwidth
                        height: iconheight
                        anchors.margins: 10
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: model.iconUrl
                    }
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr(model.name)
                        font: font.pixelSize=fontSize
                    }
                }

                states: State {
                    name: "Current"
                    when: listViewHomeLeftMenu.isCurrentItem
                    PropertyChanges {
                        target: content
                        x: 20
                    }
                }

                transitions: Transition {
                    NumberAnimation { properties: "x"; duration: 200 }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log(index)
                        listViewHomeLeftMenu.currentIndex = index;
                        if(!listViewHomeLeftMenu.activeFocus){
                            listViewHomeLeftMenu.forceActiveFocus();
                        }
                        switch(index){
                        case 0:
                            stackViewHome.push("qrc:/qml/Home/HomeContent.qml")
                            break;
                        case 1:
                            stackViewHome.push("qrc:/qml/Home/Email.qml")
                            break;
                        case 2:
                            stackViewHome.push("qrc:/qml/Home/PluginsManager.qml")
                            break;
                        }
                    }
                }
            }
        }
    }
}
