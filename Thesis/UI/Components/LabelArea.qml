import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property int width
    property int height
    property variant model

    id: _root
    width: _root.width
    height: _root.height

    Column {
        Repeater {
            model: _root.model.size

            TextArea {
                placeholderText: _root.model.at(index).placeholdertext
                font.pointSize: 24
            }
        }
    }
}
