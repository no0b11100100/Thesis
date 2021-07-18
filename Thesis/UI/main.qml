import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import ViewModel 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Model {
        id: _model
    }

    Component.onCompleted: {
        console.log(_model.view.buttonCount)
    }

    Row {
        spacing: 3
        Repeater {
            model: _model.view.buttonCount
            Button {
                id: _button
                text: _model.view.button.text
//                onClicked: _model.view.button(index).validate()
                Component.onCompleted: {
                    console.log(_model.view.button.text)
                }
            }
        }
    }

}
