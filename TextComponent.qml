import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property variant headerModel
    property variant contentModel
    border.color: "red"
    border.width: 2

    Column {
        spacing: 2
        Repeater {
            model: headerModel
            Column {
                spacing: 1
                Button {
                    property bool isActive: false
                    property string sourceIcon: "close.png"
                    id: _button
                    text: headerModel[index]
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
                } // Button

                Text {
                    text: _button.isActive === true ?
                            index >= contentModel.length ? "" : contentModel[index]
                          : ""
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                } // Text
            } // Column
        } // Repeater
    } // Column
}
