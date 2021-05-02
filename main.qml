import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    id: _root
    width: 577
    height: 480
    color: "#222222"
    visible: true

    minimumHeight: 400
    minimumWidth: 577

    Row {
        spacing: 2
        ChoiceLab {
            id: _choice
            listModel: ["1", "2", "3", "4"]
            width: 100
            height: _root.height
        }

        Information {
            id: _information
            width: _root.width - _choice.width
            height: _root.height

            Component.onCompleted: {
                console.log(width)
            }
        }

    }


}
