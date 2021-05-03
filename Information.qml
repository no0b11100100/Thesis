import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    readonly property int minimunWidth: _row.width
    property variant model
    id: _root

    Column {
        id: _column
        spacing: 2

        TextLabel {
            id: _textLabel
            size: _root.width
            placeholderText: "Введите текст"
        } // TextLabel

        TextLabel {
            id: _keyLabel
            placeholderText: "Введите ключ"
            size: _root.width
        } // TextLabel

        TextLabel {
            id: _resultLabel
            placeholderText: "Результат"
            size: _root.width
        } // TextLabel

        Row {
            id: _row
            spacing: 2

            Button {
                text: "Сгенерировать ключ"
                onClicked: {
                    _keyLabel.normalText = model.getGenerateKey()
                }
            }

            Button {
                text: "Зашифровать"
                onClicked: {
                    _resultLabel.normalText = model.encode(_textLabel.normalText, _keyLabel.normalText)
                }
            }

            Button {
                text: "Расшифровать"
                onClicked: {
//                   _resultLabel.normalText = model.decode(_textLabel.normalText, _keyLabel.normalText)
                }
            }

            Button {
                text: "Теория"
            }
        } // Row

        TextComponent {
            id: _details
            width: _root.width - 2
            height: _root.height - _row.height - _resultLabel.height*3 - 8
            headerModel: model.headerText()//["1", "2", "3", "4"]
            contentModel: model.contetntText()//["ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд", "ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд", "ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд", "ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд"]
        } // TextComponent
    } // Column

    color: "black"

}
