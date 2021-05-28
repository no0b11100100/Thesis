import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: _root
    property var texts
    property int size
    property string title: "S-Box"

    width: _column.width
    height: _column.height

    Column {
        id: _column
        spacing: 10

        Label {
            id: _header
            text: title
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Column {
            spacing: 2
            Row {
                id: _columnNumbers
                spacing: 2
                Repeater {
                    id: _r
                    model: size+1
                    Rectangle {
                        width: 40
                        height: 40
                        Text {
                            text: index === 0 ? "" : index
                            anchors.centerIn: parent
                        }

                        color: "grey"
                    }
                }

            } // Row

            Row {
                spacing: 2
                Column {
                    id: _rowNumbers
                    spacing: 2
                    Repeater {
                        model: size

                        Rectangle {
                            width: 40
                            height: 40
                            Text {
                                text: index
                                anchors.centerIn: parent
                            }

                            color: "grey"
                        }
                    }
                }

                Grid {
                    id: _grid
                    columns: size
                    //    rows: 4
                    spacing: 2

                    Repeater {
                        model: texts

                        Rectangle {
                            width: 40
                            height: 40
                            TextArea {
                                text: index
                                anchors.centerIn: parent
                            }
                        }
                    }
                } // Grid
            }
        }

    } // Column
    color: "black"

}
