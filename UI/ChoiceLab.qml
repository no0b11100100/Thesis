import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property variant listModel: []
    property var callback
    id: _root

    ScrollView{
        anchors.fill: parent
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        Column {
            spacing: 2
            Repeater {
                property int currentButton: 0
                id: _repeater
                model: listModel
                Button {
                    property string backColor: "grey"
                    id: _button
                    width: _root.width
                    text: modelData

                    background: Rectangle {
                        color: backColor
                    }

                    onClicked: {
                        callback(_button.text)
                        _repeater.itemAt(_repeater.currentButton).backColor = "grey"
                        _repeater.currentButton = index
                        _repeater.itemAt(_repeater.currentButton).backColor = "green"
                    }

                    Component.onCompleted: {
                        _repeater.itemAt(_repeater.currentButton).backColor = "green"
                    }
                } // Button
            } // Repeater
        } // Column
    } // ScrollView

    color: "black"
} // Rectangle