import QtQuick 2.9
import QtQuick.Controls 2.5

Page {
    id: loginPage
    title: ""
    anchors.fill: parent

    //Background
    Image {
        id: image
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        source: "qrc:/Assets/Images/Login.jpg"
        anchors.fill: parent

        //P1 Name
        TextField {
            id: player1
            y: 10
            x: 15
            width: mystack.width * 0.2
            height: mystack.height * 0.05
            clip: true
            placeholderText: "player 1 name"
            placeholderTextColor: "#7c6d43"
            horizontalAlignment: Text.AlignHCenter
            maximumLength: 20
        }
        //color
        RadioButton {
            id: white1
            anchors.horizontalCenter: player1.horizontalCenter
            anchors.top: player1.bottom
            text: white2.checked ? "Black" : "White"
            font.pixelSize: 12
        }

        //Game Name
        Rectangle {
            id: gameNameRec
            y: 20
            x: loginPage.width / 2 - width / 2
            width: mystack.width * 0.2
            height: mystack.height * 0.07
            color: "#00000000"
            border.color: "#7c6d43"
            border.width: 1
            TextField {
                id: gameName
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
                placeholderText: "Game name"
                placeholderTextColor: "#7c6d43"
                width: gameNameRec.width * 0.8
                maximumLength: 19
            }
        }

        //P2 Name
        TextField {
            id: player2
            placeholderText: "player 2 name"
            placeholderTextColor: "#7c6d43"
            y: 10
            x: mystack.width - width - 15
            width: mystack.width * 0.2
            height: mystack.height * 0.05
            clip: true
            horizontalAlignment: Text.AlignHCenter
            maximumLength: 20
        }
        //color
        RadioButton {
            id: white2
            anchors.horizontalCenter: player2.horizontalCenter
            anchors.top: player2.bottom
            text: white1.checked ? "Black" : "White"
            font.pixelSize: 12
            checked: true
        }
    }

    //login style
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

        //login button
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

    //back style
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

        //back button
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

