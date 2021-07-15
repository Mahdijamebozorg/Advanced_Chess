import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    Dialog {
        id: wrongChoose
        title: "Error"
        Text {
            text: "Can't go there!"
        }
    }
    id: board
    width: 600
    height: 600
    Image {
        id: boardImage
        anchors.fill: parent
        source: "qrc:/Assets/Images/Board.jpg"

        GridView {
            id: src
            anchors.centerIn: boardImage
            width: boardImage.width - 60
            height: boardImage.height - 60
            cellWidth: width / 8
            cellHeight: height / 8
            model: 64

            delegate: Rectangle {
                id: cellRec
                color: "#00000000"
                width: src.width / 8
                height: src.height / 8
                Button {
                    id: srcCell
                    anchors.fill: parent
                    flat: true
                    onClicked: {
                        bknd.choose(index)
                    }
                    Connections {
                        target: bknd
                        onChoosen: {
                            srcCell.visible = false
                            dest.visible = true
                            if (bknd.isAvailable(index)) {
                                cellRec.color = "#ac8614"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                if (bknd.canHitPiece(index))
                                    cellRec.color = "#811717"
                            }
                        }
                    }
                }
                Image {
                    source: bknd.getIcon(index)
                    anchors.centerIn: parent
                    width: parent.width * 0.85
                    height: parent.height * 0.85
                }
            }
        }
        Rectangle {
            color: "#ac8614"
        }
        GridView {
            id: dest
            visible: false
            anchors.centerIn: boardImage
            width: boardImage.width - 60
            height: boardImage.height - 60
            cellWidth: width / 8
            cellHeight: height / 8
            model: 64

            delegate: Button {
                id: destCell
                width: dest.width / 8
                height: dest.height / 8
                flat: true
                onClicked: {
                    if (bknd.isAvailable(index)) {
                        bknd.move(index)
                        mystack.replace("GamePage.qml")
                    } else
                        wrongChoose.open()
                }
            }
        }
    }
}
