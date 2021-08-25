import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtMultimedia 5.9

ApplicationWindow {
    id: window
    visible: true
    width: Screen.width * 0.5
    height: Screen.height * 0.75
    Component.onCompleted: window.showFullScreen()
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
                id: soundOn
                text: persian.checked ? "صدا" : "Sound"
                checked: true
            }
            Switch {
                id: persian
                text: "پارسی"
                checked: false
            }
            Switch {
                id: fullScreen
                text: persian.checked ? "تمام صفحه" : "FullScreen"
                checked: true
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

        //opening page animation
        replaceEnter: Transition {}
        //exiting page animation
        replaceExit: Transition {
            OpacityAnimator {
                from: 1
                to: 1
                duration: 400
            }
        }
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
    Audio {
        id: moveSound
        autoLoad: true
        autoPlay: false
        playlist: Playlist {
            PlaylistItem {
                source: "qrc:/Assets/Sound_Effects/move.mp3"
            }
        }
    }
    Connections {
        target: soundOn
        onClicked: soundOn.checked ? music.play() : music.pause()
    }
}
