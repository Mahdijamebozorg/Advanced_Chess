import QtQuick 2.9
import QtQuick.Controls 2.5

Page {
    id: loginPage
    title: ""
    anchors.fill: parent
    Image {
        id: image
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        source: "qrc:/Images/Login.jpg"
        anchors.fill: parent

        TextField {
            id: player1
            anchors.top: mystack.top
            anchors.topMargin: 15
            x: 15
            width: mystack.width * 0.2
            height: mystack.height * 0.07
            clip: true
            placeholderText: "player 1 name"
            placeholderTextColor: "#7c6d43"
            horizontalAlignment: Text.AlignHCenter
        }
        RadioButton {
            id: white1
            anchors.left: player1.right
            y: player1.y
            clip: true
            text: white2.checked ? "Black" : "White"
        }

        Rectangle {
            id: gameNameRec
            anchors.top: mystack.top
            anchors.topMargin: 50
            x: loginPage.width / 2 - width / 2
            width: mystack.width * 0.2
            height: mystack.height * 0.07
            color: "#00000000"
            border.color: "#7c6d43"
            border.width: 1
            TextField {
                id: gameName
                anchors.centerIn: parent
                placeholderText: "Game name"
                placeholderTextColor: "#7c6d43"
            }
        }
        TextField {
            id: player2
            placeholderText: "player 2 name"
            placeholderTextColor: "#7c6d43"
            anchors.right: white2.left
            anchors.top: mystack.top
            anchors.topMargin: 15
            width: mystack.width * 0.2
            height: mystack.height * 0.07
            clip: true
            horizontalAlignment: Text.AlignHCenter
        }
        RadioButton {
            id: white2
            x: mystack.width - width - 15
            y: player2.y
            clip: true
            text: white1.checked ? "Black" : "White"
            checked: true
        }
    }

    Rectangle {
        id: logrec
        x: mystack.width - width - 8
        y: mystack.height - height - 8
        width: mystack.width * 0.15
        height: mystack.height * 0.07
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#00000000"
            }
            GradientStop {
                position: 0.25
                color: "#000000"
            }

            GradientStop {
                position: 0.5
                color: "#7c6d43"
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
            id: login
            flat: true
            anchors.fill: parent
            text: qsTr("Login")
            font.bold: true
            font.italic: true
            font.pointSize: 13
            onClicked: {
                mystack.push("GamePage.qml")
                window.width = 1200
                window.height = 1000
            }
        }
    }

    Rectangle {
        id: bkRec
        x: 8
        y: mystack.height - height - 8
        width: mystack.width * 0.15
        height: mystack.height * 0.08
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#00000000"
            }
            GradientStop {
                position: 0.25
                color: "#000000"
            }

            GradientStop {
                position: 0.5
                color: "#7c6d43"
            }

            GradientStop {
                position: 0.85
                color: "#000000"
            }
        }
        GradientStop {
            position: 1
            color: "#00000000"
        }

        Button {
            flat: true
            id: back
            anchors.fill: parent
            text: "Back"
            font.bold: true
            font.italic: true
            font.pointSize: 13
            onClicked: mystack.pop()
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

