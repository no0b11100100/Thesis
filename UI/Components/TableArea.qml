import QtQuick 2.0

Item {
    property variant model
    id: _root

    Row {
        spacing: 2
        Repeater {
            model: _root.model.size
            GroupLabelArea {
                readonly property variant group: _root.model.at(index).data
                width: _root.width / _root.model.size
                height: _root.height
                model: group
            }
        }
    }
}
