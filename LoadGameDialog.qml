import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2

Dialog {
    property var modelCount: bknd.filesCount()

    id: loadGameDialog
    title: persian.checked ? "یک فایل انتخاب کنید" : "Choose a file"

    width: parent.width * 0.6
    height: parent.height * 0.5
    contentItem: Rectangle {
        color: "black"
        GridView {
            id: grid
            interactive: true
            model: modelCount

            width: parent.width * 0.98
            height: parent.height * 0.9
            cellWidth: this.width
            cellHeight: this.height / 4
            anchors.centerIn: parent

            //content
            delegate: Rectangle {
                id: deligateRec
                color: "#00000000"
                border.color: "#716c6c"
                width: grid.width
                height: grid.height / 5
                anchors.horizontalCenter: parent.horizontalCenter

                Image {
                    source: "qrc:/Assets/Images/wood1.jpeg"
                    width: parent.width - 2
                    height: parent.height - 2
                    anchors.centerIn: parent
                }
                Button {
                    id: filesBtn
                    flat: true
                    anchors.fill: parent
                    onClicked: {
                        bknd.loadGame(index)
                        loadGameDialog.close()
                    }

                    //button text
                    Text {
                        id: fileTxt
                        text: bknd.getFileInfo(index)

                        color: "white"
                        font.bold: true
                        textFormat: Text.StyledText
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 3
                        font.pixelSize: 18

                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        width: parent.width * 0.9
                        height: parent.height * 0.9
                    }
                } //btn
            }
        } //grid
    } //image
} //content rec
