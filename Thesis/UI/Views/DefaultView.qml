import QtQuick 2.15

import "../Components"
import Style 1.0

Rectangle {
    property variant model
    id: _root

    Column {

        spacing: 2
        LabelArea {

            function setSize(model)
            {
                // TODO: fix
                return model.size * (40 + model.size)
            }

            id: _labels
            width: _root.width
            height: setSize(_labels.model)
            model: _root.model.labels
        }

        ButtonArea {
            width: _root.width
            height: _root.height - _labels.height
            model: _root.model.buttons
        }
    }
}
