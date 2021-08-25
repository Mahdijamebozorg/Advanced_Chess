import QtQuick 2.9
import QtQuick.Controls 2.5

Item {
    Rectangle {
        anchors.fill: parent
        color: "white"
        Image {
            //to show a small border around
            width: parent.width - 2
            height: parent.height - 2
            id: wood4
            anchors.centerIn: parent
            source: "qrc:/Assets/Images/Wood5.jpg"

            GridView {
                interactive: false
                id: bottomGrid
                anchors.centerIn: parent
                width: parent.width * 0.98
                height: parent.height * 0.90
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
                        width: bottomCell.width * 0.8
                        height: bottomCell.height * 0.8
                        NumberAnimation on opacity {
                            duration: 600
                            from: 0
                            to: 1
                        }
                    }
                }
            }
        }
    }
}
