import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import ViewModel 1.0

import "Components"

Window {
    id: _root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Model {
        id: _model
    }

    Column {

        spacing: 2
        LabelArea {
            id: _labels
            width: _root.width
            height: _root.height-100
            model: _model.view.labels
        }

        ButtonArea {
            width: _root.width
            height: 50
            model: _model.view.buttons
        }

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
