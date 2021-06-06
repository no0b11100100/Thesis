import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import MyModel 1.0
import QtQuick.Dialogs 1.1

Window {
    id: _root
    width: 1280//_information.minimunWidth + _choice.width
    height: 800
    color: "black"//"#222222"
    visible: true

//    active: _model.error !== ""

    minimumHeight: 400

//    minimumWidth: _information.minimunWidth + _choice.width
//    maximumWidth: _information .minimunWidth + _choice.width


    Controller {
        id: _model
    }

    Row {
        spacing: 2
        ChoiceLab {
            id: _choice
            listModel: _model.algorithmsList
            width: function (array) {
                var size = array[0].length
                for(var i = 0; i < array.size-1; ++i)
                    if(array[i] > array[i+1])
                        size = array[i].length
                console.log("size", size)
                return size
            } (listModel) * 14
            height: _root.height
            callback: _model.setAlgorigthm
        }

        Information {
            id: _information
            width: _root.width - _choice.width
            height: _root.height
            mainModel: _model

            Component.onCompleted: {
                console.log(width)
            }
        }
    }
}
