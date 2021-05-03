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
                model: listModel
                Button {
                    id: _button
                    width: _root.width
                    text: listModel[index]

                    onClicked: {
                        callback(_button.text)
                    }
                }
            }
        }
    }

    color: "black"
}
