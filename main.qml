import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import MyModel 1.0

Window {
    id: _root
    width: _information.minimunWidth + _choice.width
    height: 480
    color: "black"//"#222222"
    visible: true

    minimumHeight: 400
    minimumWidth: _information.minimunWidth + _choice.width
//    maximumWidth: _information .minimunWidth + _choice.width

    Controller {
        id: _model
    }

    Row {
        spacing: 2
        ChoiceLab {
            id: _choice
            listModel: _model.algorithmList()
            width: function (array) {
                const size = array.reduce(function(a,b) {
                    return a.length > b.length ? a.length : b.length
                })
                return size
            } (_model.algorithmList()) * 14
            height: _root.height
            callback: _model.setAlgorigthm
        }

        Information {
            id: _information
            width: _root.width - _choice.width
            height: _root.height
            model: _model

            Component.onCompleted: {
                console.log(width)
            }
        }
    }
}
