import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import ViewModel 1.0

Window {
    id: _root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Model {
        id: _model
    }

    Rectangle {
        width: _root.width
        height: _root.height

        color: "grey"

        Column {
            Repeater {
                model: _model.view.labels.size

                TextArea {
                    readonly property variant label: _model.view.labels.at(index)
                    id: _text
                    placeholderText: label.placeholderText
                    text: label.text
                    font.pointSize: 24

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



//    Component.onCompleted: {
//        console.log(_model.view.buttonCount)
//    }

//    Loader {
//        id: _loader
////        source:
//    }

//    Row {
//        spacing: 3
//        Repeater {
//            model: _model.view.buttonCount
//            Button {
//                id: _button
//                text: _model.view.buttonAt(index).text
////                onClicked: _model.view.button(index).validate()
//                Component.onCompleted: {
//                    _model.foo(_loader);
//                    console.log(_model.view.buttonAt(index).text)
//                }
//            }
//        }
//    }

}
