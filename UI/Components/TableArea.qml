import QtQuick 2.0

Item {
    property variant model
    id: _root

    Grid {
        readonly property variant item: _root.model.at(0)
        id: _grid
        anchors.fill: parent
        columns: _grid.item.columnLimit
        spacing: 2

        LabelArea {
            width: _grid.width
            height: _grid.height
            model: _grid.item.data.at(index)
        }

//        Repeater {
//            model: _grid.item.data.size

//            Text {
//                readonly property variant label: _grid.item.data.at(index)
//                id: _text
//                text: label.text
//                width: 100
//                height: 40
//                font.pointSize: 20
//                color: "green"
//            }
//        }
    }

}
