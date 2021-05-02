import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    property variant listModel: []
    Column {
        spacing: 1
        Repeater {
            model: listModel
            Button {
                text: listModel[index]

            }
        }
    }
}
