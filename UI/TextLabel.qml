import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property var model
    property int size
    property bool readOnly

    readonly property string text: _text.text
    readonly property string placeholderText: _text.placeholderText

    id: _root
    width: size
    height: 40

    ScrollView {
        anchors.fill: parent
        clip: true
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        TextArea {
            id: _text
            placeholderText: model[0]
            font.pointSize: 14
            anchors.verticalCenter: parent.verticalCenter
            text: model[1]
            readOnly: _root.readOnly
            background: Rectangle {
                color: "#a0a0a0"
            }
        } // TextArea
    } // ScrollView
}
