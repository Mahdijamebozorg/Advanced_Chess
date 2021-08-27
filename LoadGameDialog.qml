import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2

Dialog {
    property var modelCount: bknd.filesCount()

    id: loadGameDialog
    title: persian.checked ? "یک فایل انتخاب کنید" : "Choose a file"

    width: 600
    height: 300
    contentItem: Rectangle {
        color: "black"

        GridView {
            id: grid
            interactive: true
            width: parent.width
            height: parent.height
            model: modelCount
            cellHeight: this.height / 3
            cellWidth: this.width * 0.98
            delegate: Rectangle {
                id: deligateRec
                color: "#00000000"
                width: grid.width * 0.98
                height: grid.height / 3
                anchors.horizontalCenter: parent.horizontalCenter
                Button {
                    id: filesBtn
                    width: parent.width
                    height: parent.height
                    background: Image {
                        source: "qrc:/Assets/Images/wood1.jpeg"
                    }
                    Text {
                        id: fileTxt
                        color: "white"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: bknd.getFileName(
                                  index) + "  :   " + bknd.getFilePlayers(index)
                        font.pixelSize: parent.height * 0.15
                        font.bold: true
                    } //text
                    onClicked: {
                        bknd.loadGame(index)
                        loadGameDialog.close()
                    }
                } //btn
            } //deligate
        } //grid
    } //image
} //content rec
