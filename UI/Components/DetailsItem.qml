import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property variant model
    id: _root

    Column {
        Row {
            Button {
                background: Rectangle {
                    color: "red"
                }
            }

            Text {
                text: _root.model.title
            }
        }

        Text {
            text: _root.model.text
        }
    }

//    Component.onCompleted: {
//        console.log("item model ", _root.model)
//    }
}
