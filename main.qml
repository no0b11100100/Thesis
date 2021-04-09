import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    id: _root
    width: 640
    height: 480
    color: "#222222"
    minimumHeight: _column.height
    visible: true

    Column {
        id: _column
        spacing: 2
        TextLabel {
            size: _root.width
            placeholderText: "enter text"
        }

        Label {
            width: _root.width
            height: 20
            color: "#CCCCCC"
            text: "detect language is English"
        }

        TextLabel {
            placeholderText: "enter key"
            size: _root.width
        }

        TextLabel {
            placeholderText: "output text"
            size: _root.width
        }

        Row
        {
            spacing: 2

            ComboBox {
                model: ["RSA", "AES", "DES", "S-DES", "XOR encode", "Vigenere code", "Caesar shift", "Simple permutation", "Simple replacement"]
            }

            Button {
                text: "encode"
            }

            Button {
                text: "decode"
            }

            Button {
                text: "show steps"
            }

            Button {
                text: "theority"
            }
        }
    }
}
