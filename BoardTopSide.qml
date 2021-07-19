import QtQuick 2.9
import QtQuick.Controls 2.5

Item {
    Rectangle {
        anchors.fill: parent
        color: "white"
        Image {
            width: board.width - 2
            height: 128
            id: wood3
            anchors.centerIn: parent
            source: "qrc:/Assets/Images/Wood5.jpg"

            GridView {
                id: topGrid
                anchors.centerIn: parent
                width: parent.width - 20
                height: parent.height - 20
                model: 16
                cellHeight: topGrid.height / 2
                cellWidth: topGrid.width / 8

                delegate: Rectangle {
                    id: topCell
                    height: topGrid.height / 2
                    width: topGrid.width / 8
                    color: "#00000000"
                    border.color: "#7c6d43"

                    //return outs
                    Button {
                        id: p2Outs
                        height: topCell.height
                        width: topCell.width
                        flat: true
                        onClicked: {
                            mystack.replace("GamePage.qml")
                        }
                    }

                    //outs icons
                    Image {
                        source: ""
                        height: topCell.height * 0.8
                        width: topCell.width * 0.8
                    }
                }
            }
        }
    }
}
