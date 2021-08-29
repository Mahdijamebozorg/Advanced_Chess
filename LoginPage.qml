import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

Page {
    id: loginPage
    title: ""
    //Background
    background: Image {
        id: image
        source: "qrc:/Assets/Images/Login.jpg"
    }

    children: [
        //P1 Name
        TextField {
            id: player1
            y: 10
            x: 15
            width: mystack.width * 0.28
            height: mystack.height * 0.06
            clip: true
            placeholderText: persian.checked ? "یازیکن ۱" : "player 1 name"
            placeholderTextColor: "#7c6d43"
            text: ""
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: this.height * 0.3
            maximumLength: 19
        },

        //color
        RadioButton {
            id: white1
            anchors.horizontalCenter: player1.horizontalCenter
            anchors.top: player1.bottom
            height: 20
            text: white2.checked ? persian.checked ? "سیاه" : "Black" : persian.checked ? "سفید" : "White"
            font.pixelSize: 12
        },

        //Game Name
        Rectangle {
            id: gameNameRec
            y: 20
            x: loginPage.width / 2 - width / 2
            width: image.width * 0.25
            height: image.height * 0.07
            color: "#00000000"
            border.color: "#7c6d43"
            border.width: 1
            TextField {
                id: gameName
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
                placeholderText: persian.checked ? "نام بازی(انگلیسی)" : "Game name(English)"
                placeholderTextColor: "#7c6d43"
                text: ""
                width: gameNameRec.width * 0.8
                height: parent.height * 0.8
                font.pixelSize: this.height * 0.3
                maximumLength: 14
            }
        },

        //P2 Name
        TextField {
            id: player2
            placeholderText: persian.checked ? "بازیکن ۲" : "player 2 name"
            placeholderTextColor: "#7c6d43"
            y: 10
            x: image.width - width - 15
            width: image.width * 0.28
            height: image.height * 0.06
            font.pixelSize: this.height * 0.3
            text: ""
            horizontalAlignment: Text.AlignHCenter
            maximumLength: 19
        },

        //color
        RadioButton {
            id: white2
            anchors.horizontalCenter: player2.horizontalCenter
            anchors.top: player2.bottom
            height: 20
            text: white1.checked ? persian.checked ? "سیاه" : "Black" : persian.checked ? "سفید" : "White"
            font.pixelSize: 12
            checked: true
        },

        //login style
        Rectangle {
            id: logrec
            x: image.width - width - 8
            y: image.height - height - 8
            width: image.width * 0.15
            height: image.height * 0.07
            gradient: Gradient {
                GradientStop {
                    position: 0.1
                    color: "#00000000"
                }
                GradientStop {
                    position: 0.175
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
                    position: 95
                    color: "#00000000"
                }
            }

            //login button
            Button {
                id: login
                flat: true
                anchors.fill: parent
                text: persian.checked ? "ورود" : "Login"
                font.bold: true
                font.italic: true
                font.pixelSize: logrec.height * 0.27
                onClicked: {
                    var ok = true

                    //if player 1 name is empty
                    if (player1.text == "") {
                        player1.placeholderTextColor = "red"
                        ok = false
                    }

                    //if player 2 name is empty
                    if (player2.text == "") {
                        player2.placeholderTextColor = "red"
                        ok = false
                    }

                    //if game name is empty
                    if (gameName.text == "" || !bknd.checkInput(
                                gameName.text)) {
                        gameName.clear()
                        gameName.placeholderTextColor = "red"
                        ok = false
                    } //if ok
                    else if (ok) {
                        bknd.setGame(gameName.text)
                        if (white1.checked) {
                            bknd.setP1(player1.text)
                            bknd.setP2(player2.text)
                        } else {

                            bknd.setP1(player2.text)
                            bknd.setP2(player1.text)
                        }
                        bknd.startGame()
                        player1.placeholderTextColor = "#7c6d43"
                        player2.placeholderTextColor = "#7c6d43"
                        gameName.placeholderTextColor = "#7c6d43"
                        player1.clear()
                        player2.clear()
                        gameName.clear()
                        fullScreen.checked = true
                        mystack.push("GamePage.qml")
                    }
                }
            }
        },

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
                    position: 0.175
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
                text: persian.checked ? "بازگشت" : "Back"
                font.bold: true
                font.italic: true
                font.pixelSize: bkRec.height * 0.27
                onClicked: mystack.pop()
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

