import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2

Dialog {

    property var modelCount: bknd.filesCount()

    id: loadGameDialog
    title: persian.checked ? "یک فایل انتخاب کنید" : "Choose a file"

    width: parent.width * 0.67
    height: parent.height * 0.5
    contentItem: Rectangle {
        color: "black"
        Text {
            id: emptyDir
            text: persian.checked ? "ذخیره ای وجود ندارد" : "No save exists"
            color: "white"
            visible: modelCount === 0
            anchors.centerIn: parent
        }
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

                Dialog {
                    id: dltConf
                    title: persian.checked ? "حذف" : "Delete"
                    Text {
                        id: dltTxt
                        text: persian.checked ? "آیا میخواهید این بازی را حذف کنید؟" : "Do you want to delete this game?"
                    }
                    standardButtons: Dialog.Ok | Dialog.Cancel
                    onAccepted: {
                        bknd.deleteFile(index)
                        modelCount = bknd.filesCount()
                        dltConf.close()
                    }
                    onRejected: dltConf.close()
                }

                id: deligateRec
                color: "#00000000"
                border.color: "#716c6c"
                width: grid.width
                height: grid.height / 5
                anchors.horizontalCenter: parent.horizontalCenter

                //background
                Image {
                    id: img
                    source: "qrc:/Assets/Images/wood1.jpeg"
                    width: parent.width - 2
                    height: parent.height - 2
                    anchors.centerIn: parent
                }
                Row {
                    id: row
                    anchors.fill: parent
                    children: [
                        Button {
                            id: filesBtn
                            flat: true
                            onClicked: {
                                bknd.loadGame(index)
                                loadGameDialog.close()
                            }

                            width: parent.width * 0.93
                            height: parent.height

                            //button text
                            Text {
                                id: fileTxt
                                text: bknd.getFileInfo(index)

                                color: "white"
                                font.bold: true
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 5
                                font.pixelSize: 18

                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter

                                width: parent.width * 0.9
                                height: parent.height * 0.9
                            }
                        },
                        Button {
                            id: deleteFIle
                            flat: true
                            width: row.width * 0.05
                            height: row.heigh * 0.5
                            onPressed: dltConf.open()
                            anchors.verticalCenter: parent.verticalCenter

                            Image {
                                id: dlt
                                source: "qrc:/Assets/Icons/delete.png"
                                anchors.fill: deleteFIle
                            }
                        }
                    ]
                }
            }
        } //grid
    } //image
} //content rec
