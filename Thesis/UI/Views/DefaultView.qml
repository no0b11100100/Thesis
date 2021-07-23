import QtQuick 2.15

import "../Components/LabelArea.qml" as LabelArea

Rectangle {
    property variant model
    id: _root

    LabelArea{
        model: _root.model
    }
}
