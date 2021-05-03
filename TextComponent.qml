import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property variant headerModel
    property variant contentModel
    id: _root
    border.color: "red"
    border.width: 2

    ScrollView {
        id: _scroll
        anchors.fill: parent
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        Column {
            spacing: 2
            Repeater {
                model: headerModel
                Column {
                    spacing: 1
                    Button {
                        property bool isActive: false
                        id: _button
                        text: headerModel[index]
                        font.pointSize: 14
                        icon.source:  _button.isActive === true ? "open.png" : "close.png"
                        icon.width: 10
                        icon.height: 10
                        background: Rectangle {
                            color: "transparent"
                        }

                        onClicked: {
                            _button.isActive = !_button.isActive
                        }
                    } // Button

                    Text {
                        id: _text
                        width: _button.isActive === true ? _root.width : 0
                        leftPadding: 8
                        rightPadding: _button.isActive === true ? 15 : 0
                        text: _button.isActive === true ?
                                  index >= contentModel.length ? "" :
                                         contentModel[index] !== "" ? contentModel[index] : "Данные недоступны"
                        : ""

                        font.pointSize: 14
                        wrapMode: Text.Wrap
                        lineHeight: 1
                    } // Text
                } // Column
            } // Repeater
        } // Column
    } // ScrollView
}
