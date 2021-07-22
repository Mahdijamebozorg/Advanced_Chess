import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    Dialog {
        id: wrongChoose
        title: "Error"
        Text {
            id: errText
            text: "An error!"
        }
    }
    id: board
    width: 600
    height: 600
    Image {
        id: boardImage
        anchors.fill: parent
        source: "qrc:/Assets/Images/Board.jpg"

        //a grid of buttons for move source
        GridView {
            interactive: false
            id: src
            anchors.centerIn: boardImage
            width: boardImage.width - 60
            height: boardImage.height - 58
            cellWidth: width / 8
            cellHeight: height / 8
            model: 64

            delegate: Rectangle {
                id: cellRec

                width: src.width / 8
                height: src.height / 8
                border.width: bknd.isMoved(index) ? 3.4 : 0.5

                border.color: bknd.isMoved(index) ? "#42e7ac" : "black"
                color: "#00000000"
                Button {
                    id: srcCell
                    anchors.fill: parent
                    flat: true
                    onClicked: {

                        switch (bknd.choose(index)) {
                            //OK
                        case 2:
                            //used "Connections" to prevent crowdness
                            break

                            //unaccessable
                        case 1:
                            errText.text = "Can't move this color now!"
                            wrongChoose.open()
                            break

                            //empty
                        case 0:
                            errText.text = "This tile is empty!"
                            wrongChoose.open()
                            break
                        }
                    }

                    //highlight canGo and canHit cells on choose
                    Connections {
                        target: bknd
                        onChoosen: {

                            //shows second choose buttons
                            srcCell.visible = false
                            dest.visible = true

                            switch (bknd.cellState(index)) {
                                //is selected
                            case 3:

                                cellRec.color = "#bca972"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                break

                                //can hit
                            case 2:

                                cellRec.color = "#811717"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                break

                                //can go
                            case 1:

                                cellRec.color = "#a4883d"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                break

                                //unavailable
                            case 0:
                                //can set a color for unavailabe squares
                            }
                        }
                    }

                    //unchoose the piece
                    Connections {
                        target: bknd
                        onUnchoosen: {
                            srcCell.visible = true
                            dest.visible = false
                            cellRec.color = "#00000000"

                            cellRec.border.color = bknd.isMoved(
                                        index) ? "#42e7ac" : "balck"

                            cellRec.border.width = bknd.isMoved(
                                        index) ? 3.4 : 0.5
                        }
                    }
                }
                Image {
                    id: chessmanIcon
                    source: bknd.getIcon(index)
                    anchors.centerIn: parent
                    width: parent.width * 0.85
                    height: parent.height * 0.85
                }
            }
        }

        //for setting colors
        Rectangle {
            color: "#42e7ac"
            width: 0
            height: 0
        }
        //new grid buttons for destination
        GridView {
            interactive: false
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

                    //if piece can go there
                    if (bknd.move(index)) {
                        mystack.replace("GamePage.qml")
                    } else {
                        //if piece can't go there and it's not its current square
                        if (!bknd.unchoosePiece(index)) {
                            errText.text = "Can't move there!"
                            wrongChoose.open()
                        }
                    }
                }
            }
        }
    }
}
