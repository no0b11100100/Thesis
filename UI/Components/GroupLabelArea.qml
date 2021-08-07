import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property variant model

    id: _root
    color: "grey"

    Column {
        spacing: 2
        Repeater {
            id: _rows
            model: _root.model.size

            Row {
                readonly property variant row: _root.model.at(index)
                spacing: 2
                Repeater {
                    model: row.size

                    TextArea {
                        readonly property variant label: row.at(index)
                        id: _text
                        width: (_root.width / row.size) - row.size - 1
                        height: 35
                        text: label.text
                        placeholderText: label.placeholderText

                        background: Rectangle {
                            color: "green"
                        }
//                        background: Rectangle {
//                            color: index === 0 ? "green" : "red"
//                        }

//                        onPressed: {
//                            console.log(_text.placeholderText)
//                        }
                    }
                }
            }
        }
    }
}
