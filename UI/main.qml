import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import MyModel 1.0

Window {
    id: _root
    width: 600//_information.minimunWidth + _choice.width
    height: 480
    color: "black"//"#222222"
    visible: true

//    DropArea {
//           id: dropArea;
//           anchors.fill: parent
//           onEntered: {
//               _root.color = "gray";
//               drag.accept (Qt.LinkAction);
//           }
//           onDropped: {
//               console.log(drop.urls)
//               _root.color = "white"
//           }
//           onExited: {
//               _root.color = "white";
//           }
//       }

    minimumHeight: 400
    minimumWidth: _information.minimunWidth + _choice.width
//    maximumWidth: _information .minimunWidth + _choice.width

    Controller {
        id: _model

        Component.onCompleted: {
            console.log("labels", _model.labelsName)
        }
    }

    Row {
        spacing: 2
        ChoiceLab {
            id: _choice
            listModel: _model.algorithmList()
            width: function (array) {
                var size = array[0].length
                for(var i = 0; i < array.size-1; ++i)
                    if(array[i] > array[i+1])
                        size = array[i].length
                console.log("size", size)
                return size
            } (_model.algorithmList()) * 14
            height: _root.height
            callback: _model.setAlgorigthm

            onCurrentAlgorithmChanged: {
                _information.resetText()
            }
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
