import QtQuick 2.15
import QtQuick.Controls 2.15

import "../Components"

Rectangle {
    property variant model
    id: _root

    Column {
        spacing: 2
        GroupLabelArea {
            width: _root.width
            height: _root.height-40
            model: _root.model.labels
        }

        ButtonArea {
            width: _root.width
            height: 40
            model: _root.model.buttons
        }
    }
}
