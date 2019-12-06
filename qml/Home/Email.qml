
import QtQuick 2.0
import QtQuick.Window 2.0
import QtWebEngine 1.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtWebChannel 1.0

Item {
    width: parent.width
    height: parent.height

    Rectangle{

        width: parent.width
        height: parent.height
        Image {
            width: parent.width
            height: parent.height
            source: "qrc:/images/img_back1.jpg"
        }

    }
    WebEngineView {
        id: webEngineView
        // 网页路径
        url:   "https://qiye.aliyun.com/alimail/auth/login"
        anchors.fill: parent
        settings.pluginsEnabled: true
        settings.screenCaptureEnabled: true
        //AllowRunningInsecureContent
        settings.allowRunningInsecureContent: true

        settings.javascriptEnabled: true

        onJavaScriptConsoleMessage: {
            console.log(message)
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
}
