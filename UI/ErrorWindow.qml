import QtQuick 2.0
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    property bool isVisible
    property string errorMessage
    property var position: []

    id: _root
    x: position[0]
    y: position[1]

    width: dialog.width
    height: dialog.height

    modality: Qt.ApplicationModal

    title: "Error"

    Dialog {
        id: dialog
//        width: _root.width
//        height: _root.height
        standardButtons: Dialog.Ok
        anchors.centerIn: parent
        height: _contentItem.lineCount * 20
        width: errorMessage.length * _contentItem.font.pointSize
        modal: true
        visible: true
        contentItem: Text {
            id: _contentItem
            text: errorMessage
            font.pointSize: 20
            color: "red"
            anchors.verticalCenter: parent.verticalCenter
            lineHeight: 1
        }
        onAccepted: _root.visible = false

        Component.onCompleted: {
            console.log("popup", _contentItem.lineCount)
        }
    }
}
