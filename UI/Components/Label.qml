import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property variant model
    id: _root

    function makeRegExp(pattern) {
        return RegExp(pattern)
    }

    TextField {
        id: _label
        placeholderText: _root.model.placeholderText
        text: _root.model.text
        validator: RegExpValidator{
            regExp: makeRegExp("^[a-zA-Z]{7}$") // TODO: take from model
            Component.onCompleted: {
                console.log(regExp)
            }
        }

        background: Rectangle{
            width: _root.width

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _label.focus = true
                }
            }
        }

        onEditingFinished: {
            if(_root.model.validate(_label.text)) {
                _root.model.text = _label.text
                _label.background.color = "white"
            } else {
                console.log("validate failed")
                _label.background.color = "red"
            }
        }
    }
}
