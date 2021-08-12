import QtQuick 2.9
import QtQuick.Controls 2.5

Page {
    title: persian.checked ? "خوش آمدید" : "Wellcome"
    id: mainPage
    anchors.fill: mystack
    background: Image {
        id: image
        source: "qrc:/Assets/Images/Main.jpg"
    }

    children: [

        //start button style
        Rectangle {
            id: startRec
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.05
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.05
            width: parent.width * 0.2
            height: parent.height * 0.1
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

            //start button
            Button {
                id: start
                anchors.fill: parent
                text: persian.checked ? "شروع" : "Start"
                font.bold: true
                font.italic: true
                font.pixelSize: this.height * 0.2
                onClicked: mystack.push("LoginPage.qml")
            }
        },
        //loging button style
        Rectangle {
            id: exitRec
            anchors.top: startRec.bottom
            anchors.topMargin: image.height * 0.05
            anchors.horizontalCenter: startRec.horizontalCenter
            width: parent.width * 0.2
            height: parent.height * 0.1
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

            //loging button
            Button {
                id: exit
                anchors.fill: parent
                text: persian.checked ? "خروج" : "Exit"
                font.bold: true
                font.italic: true
                font.pixelSize: this.height * 0.2
                onClicked: Qt.quit()
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

