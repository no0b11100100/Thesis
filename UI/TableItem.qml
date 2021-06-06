import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: _root

    property int size
    readonly property var tableData: _grid.data
    property var mainModel

    function fill(array) {
        var res = []

        for(var i = 0; i < array.length; ++i)
            res.push(array[i])

        return res
    }

    width: _column.width
    height: _column.height

    Column {
        id: _column
        spacing: 10

        Label {
            id: _header
            text: mainModel[0][0]
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
                            text: index === 0 ? "" : index-1
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
                        model: fill(mainModel[1])

                        Rectangle {
                            width: 40
                            height: 40
                            TextArea {
                                id: _text
                                text: modelData
                                anchors.centerIn: parent
                            }
                            color: "white"
                        }
                    }
                } // Grid
            } // Row
        } // Column
    } // Column
    color: "black"

}
