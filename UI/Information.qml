import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

Rectangle {
    readonly property int minimunWidth: _row.width
    property string value
    property variant mainModel


    signal resetText

    id: _root

    Component {
        id: _theory
        TheoryWindow {
            text: mainModel.theory
        }
    }

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

//            ComboBox {
//                id: _combo
//                model: ["encode", "decode"]
//                visible: _combo.count !== 0

//                Component.onCompleted: {
//                    console.log(_combo.count)
//                }
//            }


            Repeater {
                id: _buttonRepeater
                model: mainModel.buttonsName

                Button {
                    id: _button
                    text: modelData
                    action: Action {
                        onTriggered: {
                            console.log("trigger action")

                            _loader.source = ""
                            if(_button.text == "Теорія")
                            {
//                                _loader.source = "qrc:/UI/TheoryWindow.qml"
                                _loader.sourceComponent = _theory
                            } else
                            {
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
                                    for(var j = 0; j < _tableRepeater.itemAt(i).tableData.length-1; ++j)
                                        table.push(_tableRepeater.itemAt(i).tableData[j].data[0].text)


                                    tables.push(table)
                                }
                                //                            console.log("tables", _labelsRepeat.itemAt(0).placeholderText)

                                mainModel.trigger(_button.text, tables, labels)
                            }
                        }
                    }
                } // Button
            } // Repeater
        } // Row

//        ErrorWindow {
//            id: messageDialog
//            position: [_root.width/2, _root.height/2]
//            errorMessage: mainModel.error
//            visible: messageDialog.errorMessage !== ""
//        }

        MessageDialog {
            id: messageDialog
            title: "Error"
            text: mainModel.error
            icon: StandardIcon.Critical
            visible: mainModel.error !== ""
        }

        TextComponent {
            id: _details
            width: _root.width - 2
            height: _root.height - _row.height - _labelsColumn.height - 9
            headerModel: mainModel.headersName
            contentModel: mainModel.contetntsName
        } // TextComponent
    } // Column

    color: "black"

    Component.onCompleted: {
        console.log("Information", value)
    }
}
