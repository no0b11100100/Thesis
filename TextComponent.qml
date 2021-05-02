import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property variant rootModel
    border.color: "red"
    border.width: 2

    Column {
        spacing: 2
        Repeater {
            model: 3 // take from model
            Column {
                spacing: 1
                ToolButton {
                    property bool isActive: false
                    property string sourceIcon: "close.png"
                    id: _button
                    text: index // take from model
                    icon.source: sourceIcon
                    icon.width: 10
                    icon.height: 10
                    background: Rectangle {
                        color: "transparent"
                    }

                    onClicked: {
                        _button.isActive = !_button.isActive
                        _button.sourceIcon = _button.isActive === true ? "open.png" : "close.png"
                    }
                } // ToolButton

                Text {
                    text: _button.isActive === true ? "test data\ntest" : "" // take from model
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                } // Text
            } // Column
        } // Repeater
    } // Column
}
