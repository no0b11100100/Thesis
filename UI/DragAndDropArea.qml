import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle{
    property string text
    property string filePath : ""
    id: _root

    TextArea {
        placeholderText: _root.text
        anchors.centerIn: parent
        readOnly: true
    }

    DropArea {
        id: dropArea;
        anchors.fill: parent
        onEntered: {
            _root.color = "grey";
            drag.accept (Qt.LinkAction);
        }
        onDropped: {
            console.log(drop.urls)
            filePath = drop.urls[0]
            _root.color = "white"
        }
        onExited: {
            _root.color = "grey";
        }

//        onFocusChanged: {
//            _root.color = "white";
//        }
    }

    //    color: "grey"
}
