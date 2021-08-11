import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

//promotion dialog
Dialog {
    id: promotion
    title: persian.checked ? "ارتقا" : "Promotion"
    width: parent.height * 0.35
    height: parent.height * 0.35
    contentItem: Rectangle {
        id: promotionRec
        border.color: "#7c6d43"
        border.width: 2
        anchors.centerIn: parent

        //background
        Image {
            id: name
            source: "qrc:/Assets/Images/Wood2.jpg"
            width: parent.width - 2
            height: parent.height - 2
            anchors.centerIn: parent
        }
        Text {
            id: promotionText
            text: persian.checked ? "به کدام یک میخواهید ارتقا پیدا کنید؟" : "Which one do you want promote to?"
            color: "white"
            textFormat: Text.StyledText
            fontSizeMode: Text.Fit
            minimumPixelSize: 5
            font.pixelSize: 18
            width: parent.width * 0.9
            height: parent.height * 0.3
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        //promotion Grid
        Grid {
            id: promotionGrid
            height: parent.height * 0.7
            width: parent.width * 0.9
            anchors.top: promotionText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: height * 0.1
            rows: 2
            columns: 2
            horizontalItemAlignment: Grid.AlignHCenter
            verticalItemAlignment: Grid.AlignVCenter
            columnSpacing: this.width * 0.1
            rowSpacing: this.height * 0.1

            //promote To Queen
            Rectangle {
                id: queenRec
                color: "#00000000"
                border.color: "#7c6d43"
                width: parent.width * 0.45
                height: parent.height * 0.45
                Image {
                    source: "qrc:/Assets/Images/wood1.jpeg"
                    width: parent.width - 2
                    height: parent.height - 2
                    anchors.centerIn: parent
                }
                Button {
                    id: promoteToQueen
                    flat: true
                    icon.source: "qrc:/Assets/Icons/WQueen.png"
                    icon.width: this.width * 0.9
                    icon.height: this.height * 0.9
                    icon.color: "#9c843c"
                    width: parent.width - 2
                    height: parent.height - 2
                    onClicked: {
                        bknd.promote(4)
                        mystack.replace("GamePage.qml")
                    }
                }
            }

            //promote To Rook
            Rectangle {
                id: rookRec
                color: "#00000000"
                border.color: "#7c6d43"
                width: parent.width * 0.45
                height: parent.height * 0.45
                Image {
                    source: "qrc:/Assets/Images/wood1.jpeg"
                    width: parent.width - 2
                    height: parent.height - 2
                    anchors.centerIn: parent
                }
                Button {
                    id: promoteToRook
                    flat: true
                    icon.source: "qrc:/Assets/Icons/WRook.png"
                    icon.width: this.width * 0.9
                    icon.height: this.height * 0.9
                    icon.color: "#9c843c"
                    width: parent.width - 2
                    height: parent.height - 2

                    onClicked: {
                        bknd.promote(3)
                        mystack.replace("GamePage.qml")
                    }
                }
            }

            //promote To Bishop
            Rectangle {
                id: bihopRec
                color: "#00000000"
                border.color: "#9c843c"
                width: parent.width * 0.45
                height: parent.height * 0.45
                Image {
                    source: "qrc:/Assets/Images/wood1.jpeg"
                    width: parent.width - 2
                    height: parent.height - 2
                    anchors.centerIn: parent
                }
                Button {
                    id: promoteToBishop
                    flat: true
                    icon.source: "qrc:/Assets/Icons/WBishop.png"
                    icon.width: this.width * 0.9
                    icon.height: this.height * 0.9
                    icon.color: "#9c843c"
                    width: parent.width - 2
                    height: parent.height - 2
                    onClicked: {
                        bknd.promote(1)
                        mystack.replace("GamePage.qml")
                    }
                }
            }

            //promote To Knight
            Rectangle {
                id: knightRec
                color: "#00000000"
                border.color: "#7c6d43"
                width: parent.width * 0.45
                height: parent.height * 0.45
                Image {
                    source: "qrc:/Assets/Images/wood1.jpeg"
                    width: parent.width - 2
                    height: parent.height - 2
                    anchors.centerIn: parent
                }
                Button {
                    id: promoteToKnight
                    flat: true
                    icon.source: "qrc:/Assets/Icons/WKnight.png"
                    icon.width: this.width * 0.9
                    icon.height: this.height * 0.9
                    icon.color: "#9c843c"
                    width: parent.width - 2
                    height: parent.height - 2
                    onClicked: {
                        bknd.promote(2)
                        mystack.replace("GamePage.qml")
                    }
                }
            }
        }
    }
}
