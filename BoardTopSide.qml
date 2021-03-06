import QtQuick 2.9
import QtQuick.Controls 2.5

Item {
    Rectangle {
        anchors.fill: parent
        color: "white"
        Image {
            width: parent.width - 2
            height: parent.height - 2
            id: wood3
            anchors.centerIn: parent
            source: "qrc:/Assets/Images/Wood5.jpg"

            GridView {
                interactive: false
                id: topGrid
                anchors.centerIn: parent
                width: parent.width * 0.98
                height: parent.height * 0.90
                model: 16
                cellHeight: topGrid.height / 2
                cellWidth: topGrid.width / 8

                delegate: Rectangle {
                    id: topCell
                    height: topGrid.height / 2
                    width: topGrid.width / 8
                    color: "#00000000"
                    border.color: "#7c6d43"

                    //outs icons
                    Image {
                        id: image
                        anchors.centerIn: parent
                        source: bknd.getP2OutsIcon(index)
                        width: topCell.width * 0.78
                        height: topCell.height * 0.8
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
