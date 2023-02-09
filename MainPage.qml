import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Page {

    title: persian.checked ? "خوش آمدید" : "Wellcome"
    id: mainPage
    background: Image {
        id: image
        source: "qrc:/Assets/Images/Main.png"
    }

    Dialog {
        id: fileErr
        title: persian.checked ? "خظای فایل" : "File Error"
        Text {
            id: fileErrTxt
            text: persian.checked ? "برخی اطلاعات این فایل اشتباه هستند" : "Some of this file's details are invalid"
        }
    }

    Dialog {
        id: folderErr
        title: persian.checked ? "خظای فایل" : "File Error"
        Text {
            id: folderErrTxt
            text: persian.checked ? "نمیتوان پوشه ی بازی های ذخیره شده را باز کرد!" : "Can't open GameSave folder!"
        }
    }

    Connections {
        target: bknd
        function onGameLoaded() {
            mystack.push("GamePage.qml")
        }
    }
    Connections {
        target: bknd
        function onFileError() {
            fileErr.open()
        }
    }

    LoadGameDialog {
        id: loadGameDialog
    }

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
            text: persian.checked ? "بازی جدید" : "New game"
            font.bold: true
            font.italic: true
            font.pixelSize: this.height * 0.2
            onClicked: mystack.push("LoginPage.qml")
        }
    }

    // Load game button
    Rectangle {
        id: loadRec
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
            id: load
            anchors.fill: parent
            text: persian.checked ? "بارگیری بازی" : "Load game"
            font.bold: true
            font.italic: true
            font.pixelSize: this.height * 0.2
            onClicked: {
                if (bknd.readSaveFiles()) //get files in directory
                {
                    loadGameDialog.modelCount = 0 //to refresh
                    loadGameDialog.modelCount = bknd.filesCount() //get files count
                    loadGameDialog.open()
                } else
                {
                    folderErr.open()
                }
            }
        }
    }
    //Exit button style
    Rectangle {
        id: exitRec
        anchors.top: loadRec.bottom
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

        //Exit button
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
}
