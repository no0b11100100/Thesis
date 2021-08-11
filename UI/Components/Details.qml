import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    property variant model: []
    property int spacing: 2
    id: _root

    ColumnLayout {
        spacing: 2

        Repeater {
            id: _repeater
            model: _root.model.length

            Loader {
                property variant data: _root.model[index]
                id: _loader
                Layout.leftMargin: _root.spacing
                width: 100
                height: 50
                source: _root.model[index].length === 1 ? "qrc:/UI/Components/DetailsItem.qml"
                                                        : "qrc:/UI/Components/Details.qml"

                onLoaded: {
                    if (_root.model[index].length === 1) {
                        item.model = _loader.data[0]
                    } else {
                        item.model = _loader.data
                        item.spacing = item.spacing + 30
                    }

                    console.log("model ", item.model, _loader.source, _loader.status === Loader.Ready)
                }
            }
        }
    }
}

