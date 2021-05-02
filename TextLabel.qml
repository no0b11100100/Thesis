import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property string placeholderText : ""
    property int size
    id: _root
    width: size
    height: 40

    ScrollView {
        anchors.fill: parent
        clip: true
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        TextArea {
            placeholderText: _root.placeholderText
            font.pointSize: 14
            anchors.verticalCenter: parent.verticalCenter

            background: Rectangle {
                color: "#a0a0a0"
            }
        } // TextArea
    } // ScrollView
}
