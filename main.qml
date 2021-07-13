import QtQuick 2.12
import QtQuick.Controls 2.5

//import QtMultimedia 5.0
ApplicationWindow {
    id: window
    visible: true
    width: 900
    height: 800
    title: qsTr("Advanced Chess")

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
                text: "Sound ON"
                id: soundOn
                checked: true
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
