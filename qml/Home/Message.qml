
import QtQuick 2.0
import QtQuick.Window 2.0
import QtWebEngine 1.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtWebChannel 1.0

// 消息
Item {
    width: swipeViewHomeContent.width-100
    height: swipeViewHomeContent.height
    Rectangle{
        width: parent.width
        height: parent.height
        Image {
            opacity:0.5
            width: parent.width
            height: parent.height
            source: "qrc:/images/img_back1.jpg"
        }
    }

    WebEngineView {
        id: webEngineView
        width: parent.width
        height: parent.height
        // 网页路径
        url:"http://47.94.9.85/#/login"
        anchors.fill: parent
        settings.pluginsEnabled: true
        settings.screenCaptureEnabled: true
        //AllowRunningInsecureContent
        settings.allowRunningInsecureContent: true
        settings.javascriptEnabled: true

        onJavaScriptConsoleMessage: {
            console.log(message)
            if(message.indexOf("welcome")!=-1||message.indexOf("Presence")!=-1){
                itemLoadingMain.visible=false
            }


        }
        onFeaturePermissionRequested: {
            if(feature  == WebEngineView.MediaAudioCapture
                    || feature == WebEngineView.MediaAudioVideoCapture
                    || feature ==  WebEngineView.MediaVideoCapture){
                grantFeaturePermission(securityOrigin,feature,true)
            } else{
                grantFeaturePermission(securityOrigin,feature,false)
            }
        }
    }

    Component.onCompleted: {
        WebEngine.settings.pluginsEnabled = true;
    }
}
