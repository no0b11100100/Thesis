import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property variant model
    id: _root

    TextField {
        id: _label
        placeholderText: "text"
        validator: RegExpValidator{regExp: /^[a-zA-Z]{7}$/}
        background: Rectangle{
            width: _root.width

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _label.focus = true
                }
            }
        }
    }
}
