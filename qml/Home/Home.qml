import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.1
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3

Item {
    id:itemHomeRoot
    property bool homeLeftMenuVisible: true
    width: parent.width
    height: parent.height


    StackView{
        id:stackViewHome
        width: parent.width
        height: parent.height
        anchors.left: homeLeftMenu.right
        //默认显示
        initialItem: "qrc:/qml/Home/HomeContent.qml"
        Rectangle{
            width: parent.width
            height: parent.height
            color: "#333333"

        }
    }

    HomeLeftMenu{
        id:homeLeftMenu
        visible: homeLeftMenuVisible
    }

    MenuBar {
        Menu{
            title:"北斗数睿IM";
            MenuItem{
                text:'关于';
            }
            MenuItem{
                text:'检查更新';
            }
            MenuItem{
                text:'BUG反馈';
            }
            MenuItem{
                text:'日志发送';
            }
        }
        Menu{
            title:"网络";
            MenuItem{
                text:'缓冲设置';
            }
            MenuItem{
                text:'代理设置';
            }
        }
        Menu{
            title:"邮件";
            MenuItem{
                text:'更新邮件';
            }
            MenuItem{
                text:'邮件服务器设置';
            }
        }
        Menu{
            title:"设置";
            MenuItem{
                text:'缓冲设置';
            }
            MenuItem{
                text:'皮肤设置';
            }
        }
        Menu{
            title:"插件";
            MenuItem{
                text:'插件管理';
            }
            MenuItem{
                text:'插件更新';
            }
        }
        Menu{
            title:"界面管理";
            MenuItem{
                text:'显示/隐藏 左侧菜单';
                onTriggered: {
                    console.log("onTriggered")
                    homeLeftMenuVisible=!homeLeftMenuVisible
                    if(homeLeftMenuVisible){

                        stackViewHome.anchors.left=homeLeftMenu.right
                    }else{

                        stackViewHome.anchors.left=itemHomeRoot.left
                    }
                }
                onCheckedChanged: {
                    console.log("onCheckedChanged")
                }
            }
            MenuItem{
                text:'显示/隐藏 头部导航';
            }
        }
    }
}
