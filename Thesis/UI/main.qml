import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import ViewModel 1.0

import "Views"

Window {
    id: _root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Model {
        id: _model
    }

    DefaultView {
        width: _root.width
        model: _model.view
    }

}
