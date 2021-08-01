import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property variant model

    id: _root

    Row {
        spacing: 1
        Repeater {
            model: _root.model.size

            Button {
                readonly property variant button: _root.model.at(index)
                text: button.text
                onClicked: button.execute()
            }
        }
    }

}
