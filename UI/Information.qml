import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    readonly property int minimunWidth: _row.width
    property variant mainModel

    signal resetText

    id: _root

    Loader{
        id: _loader
    }

    Column {
        id: _column
        spacing: 2

        Column
        {
            id: _labelsColumn
            spacing: 2
            Repeater{
                id: _labelsRepeat
                model: mainModel.labelsText
                TextLabel {
                    id: _textLabel
                    size: _root.width
                    model: modelData
                    readOnly: index+1 === _labelsRepeat.count
                } // TextLabel

                Component.onCompleted: {
                    console.log("model", _labelsRepeat.model[0])
                }
            } // Repeater

            Row{
                spacing: 10
                Repeater{
                    id: _tableRepeater
                    model: mainModel.tableInfo
                    TableItem {
//                        texts: modelData//["a", "b", "c", "d", "e", "f", "g", "h", "q", "w", "y", "r", "u", "i", "o", "p"]
                        size: 4
                        mainModel: modelData
//                        title: modelData
                    } // TableItem
                } // Repeater
            } // Row
        } // Column
        Row {
            id: _row
            spacing: 2

            Repeater {
                id: _buttonRepeater
                model: mainModel.buttonsName

                Button {
                    id: _button
                    text: modelData
                    action: Action {
                        onTriggered: {
                            console.log("trigger action")

                            var labels = []
                            for(var i = 0; i < _labelsRepeat.count; ++i)
                            {
                                var labelInfo = [_labelsRepeat.itemAt(i).placeholderText, _labelsRepeat.itemAt(i).text]
                                labels.push(labelInfo)
                            }
                            var tables = []
                            for(i = 0; i < _tableRepeater.count; ++i)
                            {
                                var table = []
                                for(var j = 0; j < _tableRepeater.itemAt(i).texts.length; ++j)
                                    table.push(_tableRepeater.itemAt(i).tableData[j].data[0].text)

                                tables.push(table)
                            }
//                            console.log("tables", _labelsRepeat.itemAt(0).placeholderText)

                            mainModel.trigger(_button.text, tables, labels)
                        }
                    }
                } // Button
            } // Repeater
        } // Row

        TextComponent {
            id: _details
            width: _root.width - 2
            height: _root.height - _row.height - _labelsColumn.height - 9
            headerModel: mainModel.headersName
            contentModel: mainModel.contetntsName
        } // TextComponent
    } // Column

    color: "black"
}
