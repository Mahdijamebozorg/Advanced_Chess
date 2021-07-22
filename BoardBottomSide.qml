import QtQuick 2.9
import QtQuick.Controls 2.5

Item {
    Rectangle {
        anchors.fill: parent
        color: "white"
        Image {
            width: board.width - 2
            height: 128
            id: wood4
            anchors.centerIn: parent
            source: "qrc:/Assets/Images/Wood5.jpg"

            GridView {
                interactive: false
                id: bottomGrid
                anchors.centerIn: parent
                width: parent.width - 20
                height: parent.height - 20
                model: 16
                cellHeight: bottomGrid.height / 2
                cellWidth: bottomGrid.width / 8

                delegate: Rectangle {
                    id: bottomCell
                    height: bottomGrid.height / 2
                    width: bottomGrid.width / 8
                    color: "#00000000"
                    border.color: "#7c6d43"

                    //outs icons
                    Image {
                        anchors.centerIn: parent
                        source: bknd.getP1OutsIcon(index)
                        width: bottomCell.width * 0.78
                        height: bottomCell.height * 0.8
                    }
                }
            }
        }
    }
}
