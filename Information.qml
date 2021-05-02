import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: _root

    Column {
        id: _column
        spacing: 2

        TextLabel {
            id: _label
            size: _root.width
            placeholderText: "Введите текст"
        } // TextLabel

        TextLabel {
            placeholderText: "Введите ключ"
            size: _root.width
        } // TextLabel

        TextLabel {
            placeholderText: "Результат"
            size: _root.width
        } // TextLabel

        Row {
            id: _row
            spacing: 2

            Button {
                text: "Сгенерировать ключ"
            }

            Button {
                text: "Зашифровать"
            }

            Button {
                text: "Расшифровать"
            }

            Button {
                text: "Теория"
            }
        } // Row

        TextComponent {
            id: _details
            width: _root.width - 2
            height: _root.height - _row.height - _label.height*3 - 8
            headerModel: ["1", "2", "3", "4"]
            contentModel: ["ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд", "ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд", "ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд", "ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд"]
        } // TextComponent
    } // Column

}
