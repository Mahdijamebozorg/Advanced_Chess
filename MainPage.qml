import QtQuick 2.9
import QtQuick.Controls 2.5

Page {
    title: "Wellcome"
    id: mainPage
    anchors.fill: mystack
    Image {
        id: image
        source: "qrc:/Assets/Images/Main.jpg"
        anchors.fill: parent

        Rectangle {
            id: rectangle
            x: 29
            y: 54
            width: 202
            height: 82
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#00000000"
                }
                GradientStop {
                    position: 0.175
                    color: "#182127"
                }

                GradientStop {
                    position: 0.5
                    color: "#ffffff"
                }

                GradientStop {
                    position: 0.85
                    color: "#000000"
                }
                GradientStop {
                    position: 1
                    color: "#00000000"
                }
            }
            Button {
                id: start
                anchors.fill: parent
                text: qsTr("Start")
                font.bold: true
                font.italic: true
                font.pointSize: 13
                onClicked: mystack.push("LoginPage.qml")
            }
        }

        Rectangle {
            id: rectangle1
            x: 29
            y: 175
            width: 202
            height: 82
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#00000000"
                }
                GradientStop {
                    position: 0.175
                    color: "#182127"
                }

                GradientStop {
                    position: 0.5
                    color: "#ffffff"
                }

                GradientStop {
                    position: 0.85
                    color: "#000000"
                }
                GradientStop {
                    position: 1
                    color: "#00000000"
                }
            }
            Button {
                id: exit
                anchors.fill: parent
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

