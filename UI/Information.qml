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

        signal buttonPressed

        Column
        {
            id: _labelsColumn
            spacing: 2
            Repeater{
                id: _labelsRepeat
                model: mainModel.labelsName
                TextLabel {
                    id: _textLabel
                    size: _root.width
                    placeholderText: modelData
                } // TextLabel
            }
        }
        Row {
            id: _row
            spacing: 2

            Repeater {
                id: _buttonRepeater
                model: mainModel.buttonsName

                Button {
                    id: _button
                    text: modelData
                    onClicked: {
                         _loader.source = ""
                        if(_button.text === "Теорія")
                        {
                            _loader.source = "qrc:/UI/TheoryWindow.qml"
                            console.log("pressed")
                        }
                        else if(_button.text === "Зашифрувати" || _button.text === "Розшифрувати")
                        {
                            _column.buttonPressed()
                            _labelsRepeat.itemAt(2).normalText =
                                    mainModel.triggerButton(_button.text, _labelsRepeat.itemAt(0).normalText, _labelsRepeat.itemAt(1).normalText)
                        }
                    }
                } // Button
            } // Repeater

            Component.onCompleted: {
                _root.resetText.connect(function() {
                    console.log("processResetText", _labelsRepeat.count)
                    for(var i = 0; i < _labelsRepeat.count; ++i)
                        _labelsRepeat.itemAt(i).normalText = ""
                })
            }
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
