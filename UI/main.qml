import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import ViewModel 1.0

import "Views"

import "Components"

Window {
    id: _root
    width: 640
    height: 480
    visible: true
    title: qsTr("CryptoTool")
    color: "black"

    Model {
        id: _model
    }

    Row {
        spacing: 2
        NavigationList {
            id: _list
            width: Math.min(_model.navigationList.length * 15, _root.width-_algo.width)
            height: _root.height
            model: _model.navigationList
        }

        Loader {
            readonly property variant model: _model.view
            id: _algo
            source: _algo.model.path
            width: _root.width - _list.width
            height: _root.height
            onLoaded: {
                item.model = _algo.model
            }
        }
    }
}
