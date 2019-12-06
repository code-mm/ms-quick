import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.1
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3

import "../IM"

Item{
    width: stackViewHome.width
    height: stackViewHome.height

    // 头部导航
    TabBar {
        id:tabBarHead
        width: parent.width-100
        height: 40
        anchors.margins: 0
        currentIndex: swipeViewHomeContent.currentIndex

        TabButton {
            text: qsTr("消息WEB")
        }
        TabButton {
            text: qsTr("消息")
        }
        TabButton {

            text: qsTr("任务")

        }
        TabButton {

            text: qsTr("组织")

        }
        TabButton {

            text: qsTr("部门知识")

        }
        TabButton {

            text: qsTr("公司知识")

        }
        TabButton {

            text: qsTr("个人资料")

        }
        TabButton {

            text: qsTr("通讯录")

        }
        TabButton {

            text: qsTr("茶饮")

        }
        TabButton {

            text: qsTr("咖啡")

        }
        TabButton {

            text: qsTr("酒吧")

        }
        TabButton {

            text: qsTr("店铺")

        }
    }

    // 切换卡片
    SwipeView {
        id:swipeViewHomeContent
        width: parent.width
        height: parent.height-80
        anchors.centerIn: parent
        currentIndex: tabBarHead.currentIndex
        onCurrentIndexChanged: {

            console.log(currentIndex)

            switch(currentIndex){
            case 0:
            case 1:
                tabBarFoot.setCurrentIndex(0)
                break
            case 2:
                tabBarFoot.setCurrentIndex(1)
                break
            case 3:
            case 4:
                tabBarFoot.setCurrentIndex(2)
                break
            case 5:
            case 6:
                tabBarFoot.setCurrentIndex(3)
                break
            case 7:
            case 8:
            case 9:
                tabBarFoot.setCurrentIndex(4)
                break
            case 10:
                tabBarFoot.setCurrentIndex(5)
                break
            }
        }

        Message{
        }
        RoomListView{

        }
        Task{
        }
        Organization{
        }
        DepartmentKnowledge{
        }
        CompanyKnowledge{
        }
        PersonalInformation{
        }
        AddressBook{
        }
        TeaDrink{
        }
        Coffee{
        }
        Bar{
        }
        Shop{
        }
    }



    // 底部导航

    TabBar {
        id:tabBarFoot
        anchors.margins: 0
        width: parent.width-100
        height: 40
        anchors.bottom: parent.bottom
        TabButton {
            text: qsTr("消息任务")
            onCanceled: {
                swipeViewHomeContent.setCurrentIndex(0)

            }
        }
        TabButton {
            text: qsTr("组织制度")

            onClicked: {

                swipeViewHomeContent.setCurrentIndex(2)
            }
        }
        TabButton {
            text: qsTr("知识业务")

            onCanceled: {

                swipeViewHomeContent.setCurrentIndex(4)
            }
        }
        TabButton {
            text: qsTr("我的资料")

            onCanceled: {
                swipeViewHomeContent.setCurrentIndex(6)
            }

        }
        TabButton {
            text: qsTr("附近发现")

            onCanceled: {
                swipeViewHomeContent.setCurrentIndex(7)
            }
        }
        TabButton {
            text: qsTr("其他功能")

            onCanceled: {
                swipeViewHomeContent.setCurrentIndex(8)
            }
        }
    }
}
