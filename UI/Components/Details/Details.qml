import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4

Rectangle {
    property variant model
    id: _root
    TreeView {
        width: _root.width
        height: _root.height
        TableViewColumn {
               role: "display"
        }

        model: _root.model

        itemDelegate: Item{
            Text {
                text: styleData.value
                font.pointSize: 10
                color: "black"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
