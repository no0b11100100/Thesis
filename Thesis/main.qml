import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import MainModel 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    MyModel {
        id: _model
    }

    Button {
        text: _model.view.text
        onClicked: _model.trigger()
    }
}
