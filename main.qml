import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtMultimedia 5.9

ApplicationWindow {
    id: window
    visible: true
    width: Screen.width * 0.5
    height: Screen.height * 0.75
    minimumHeight: 700
    minimumWidth: 700
    title: persian.checked ? "شطرنج پیشرفته" : "Advanced Chess"

    header: ToolBar {
        id: toolbar
        height: window.height * 0.05
        contentHeight: toolButton.implicitHeight
        background: Rectangle {
            id: toolbarRec
            anchors.fill: parent
            color: "black"
        }

        ToolButton {
            id: toolButton
            text: "\u2630"
            font.pixelSize: parent.height * 0.6
            anchors.verticalCenter: parent.verticalCenter
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
            Switch {
                text: persian.checked ? "تمام صفحه" : "FullScreen"
                id: fullScreen
                checked: false
                onCheckedChanged: {
                    this.checked ? window.showFullScreen() : window.showNormal()
                }
            }
        }
    }

    StackView {
        id: mystack
        initialItem: "MainPage.qml"
        anchors.fill: parent
    }

    Audio {
        id: music
        autoLoad: true
        autoPlay: true
        playlist: Playlist {
            playbackMode: Playlist.Loop
            PlaylistItem {
                source: "qrc:/Assets/Musics/Johann_Johannsson_Flight_From_The_City_2021.mp3"
            }
        }
    }
    Connections {
        target: soundOn
        onClicked: soundOn.checked ? music.play() : music.pause()
    }
}
