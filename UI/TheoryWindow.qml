import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    property string text
    id: _root
    visible: true

    ScrollView {
        id: _scroll
        anchors.fill: parent
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        Text {
            id: _text
            width: _root.width
            leftPadding: 8
            rightPadding: 15
            topPadding: 10
            text: _root.text

            font.pointSize: 14
            font.family: "Courier"
            textFormat: Text.RichText
            wrapMode: Text.Wrap
            lineHeight: 1
        } // Text
    } // ScrollView
} // Rectangle
