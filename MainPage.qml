import QtQuick 2.9
import QtQuick.Controls 2.5

Page {
    title: "Wellcome"
    id: mainPage
    anchors.fill: parent
    Rectangle {
        id: rec
        anchors.fill: parent
        Image {
            id: image
            source: "qrc:/Images/Main.jpg"
            anchors.fill: parent

            Rectangle {
                id: rectangle
                x: 29
                y: 54
                width: 202
                height: 82
                border.color: "#182127"
                gradient: Gradient {
                    GradientStop {
                        position: 0.168
                        color: "#182127"
                    }

                    GradientStop {
                        position: 0.499
                        color: "#ffffff"
                    }

                    GradientStop {
                        position: 0.819
                        color: "#000000"
                    }
                }
            }

            Rectangle {
                id: rectangle1
                x: 29
                y: 175
                width: 202
                height: 82
                border.color: "#182127"
                gradient: Gradient {
                    GradientStop {
                        position: 0.168
                        color: "#182127"
                    }

                    GradientStop {
                        position: 0.499
                        color: "#ffffff"
                    }

                    GradientStop {
                        position: 0.819
                        color: "#000000"
                    }
                }
            }
            Button {
                id: start
                x: 29
                y: 40
                width: 202
                height: 103
                text: qsTr("Start")
                font.bold: true
                font.italic: true
                font.underline: false
                font.pointSize: 13
                onClicked: mystack.push("LoginPage.qml")
            }

            Button {
                id: exit
                x: 29
                y: 162
                width: 202
                height: 100
                text: qsTr("Exit")
                font.bold: true
                font.italic: true
                font.pointSize: 13
                onClicked: Qt.quit()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

