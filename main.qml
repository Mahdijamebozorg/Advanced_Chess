import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

//import QtMultimedia 5.0
ApplicationWindow {
    id: window
    visible: true
    width: Screen.width * 0.5
    height: Screen.height * 0.75
    title: persian.checked ? "شطرنج پیشرفته" : "Advanced Chess"

    header: ToolBar {
        id: toolbar
        contentHeight: toolButton.implicitHeight
        background: Rectangle {
            id: toolbarRec
            anchors.fill: parent
            color: "black"
        }

        ToolButton {
            id: toolButton
            text: "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: drawer.open()
        }

        Label {
            text: mystack.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.25
        height: window.height

        Column {
            anchors.fill: parent

            Switch {
                text: persian.checked ? "صدا" : "Sound"
                id: soundOn
                checked: true
            }
            Switch {
                text: "پارسی"
                id: persian
                checked: false
            }
        }
    }

    StackView {
        id: mystack
        initialItem: "MainPage.qml"
        anchors.fill: parent
    }

    //    Audio {
    //        id: music
    //        autoLoad: true
    //        autoPlay: true
    //        source: "qrc:/Musics/Martin_Kohlstedt_NIODOM.mp3"
    //    }
    //    Connections {
    //        target: soundOn
    //        onClicked: soundOn.checked ? music.play() : music.pause()
    //    }
}
