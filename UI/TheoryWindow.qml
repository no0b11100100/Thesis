import QtQuick 2.0
import QtQuick.Window 2.15

Window {
    id: _root
    visible: true

    height: 400
    width: 500

    Text {
        id: _text
        textFormat: Text.RichText
        text: "Normal<sub> Subscript</sub> <sup>Superscript</<sup>"
    } // Text

} // Rectangle
