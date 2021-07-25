import QtQuick 2.15
import QtQuick.Controls 2.15

import Style 1.0

Rectangle {
    property variant model

    id: _root

    color: "grey"

    Column {
        spacing: 1
        Repeater {
            model: _root.model.size

            TextArea {
                readonly property variant label: _root.model.at(index)
                id: _text
                placeholderText: label.placeholderText
                text: label.text
                readOnly: label.isReadOnly
                font.pointSize: Style.labelFontSize

                background: Rectangle {
                    color: "white"
                    width: _root.width
                    height: _text.height
                }

                onTextChanged: {
                    if (_text.label.isEditing === true) {
                        if(_text.text.charAt(_text.text.length-1) == ' ') {
                            _text.text = _text.text.substring(0, _text.text.length-1)
                            _text.cursorPosition = _text.length
                        }
                    }
                }

                onEditingFinished: {
                    if(_text.label.validate(_text.text)) {
                        _text.label.text = _text.text
                        _text.background.color = "white"
                    } else {
                        console.log("validate failed")
                        _text.background.color = "red"
                    }
                }

            } // TextArea
        } // Repeater
    } // Column
}
