import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15

Rectangle {
    property variant model

    id: _root

    Column {
        spacing: 1

        Button {
            // TODO
            id: _backButton
            width: 45
            height: 60
            contentItem: Text {
                text: "<"
                font.pointSize: 25
                color: "grey"
            }

            onClicked: _root.model.back()
        }

        Repeater {
            model: _root.model.list.size

            Button {
                id: _item
                text: _root.model.list.at(index)
                width: _root.width
                onClicked: _root.model.forward(_item.text)
            }
        }
    }


}