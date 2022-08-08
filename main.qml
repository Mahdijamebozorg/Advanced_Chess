import QtQuick 2.9
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

    InfoDialog {
        id: infoDialog
    }

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
        Rectangle {
            anchors.fill: parent
            color: "black"
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
                        this.checked ? window.showFullScreen(
                                           ) : window.showNormal()
                    }
                }
            }
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 8
                width: parent.width * 0.2
                height: parent.height * 0.06
                Image {
                    anchors.fill: parent
                    source: "qrc:/Assets/Icons/info.png"
                }
                Button {
                    anchors.fill: parent
                    flat: true
                    id: infBtn
                    onPressed: {
                        infoDialog.open()
                        drawer.close()
                    }
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

    // replace with MediaPlayer on Qt 6 and above
    Audio {
        id: music
        autoLoad: true
        autoPlay: true
        playlist: Playlist {
            id: playList
            playbackMode: Playlist.Loop
            PlaylistItem {
                source: "qrc:/Assets/Musics/Martin_Kohlstedt_NIODOM.mp3"
            }
            PlaylistItem {
                source: "qrc:/Assets/Musics/Johann_Johannsson_Flight_From_The_City_2021.mp3"
            }
        }
    }
    Audio {
        id: moveSound
        source: "qrc:/Assets/SoundEffects/move.wav"
    }

    Connections {
        target: soundOn
        function onClicked() {
            if (soundOn.checked)
                music.play()
            else
                music.pause()
        }
    }
}
