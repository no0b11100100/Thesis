import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    readonly property int minimunWidth: _row.width
    property variant mainModel
    id: _root

    Column {
        id: _column
        spacing: 2

        Repeater{
            model: mainModel.labelsName
            TextLabel {
                id: _textLabel
                size: _root.width
                placeholderText: modelData
            } // TextLabel
        }

        Row {
            id: _row
            spacing: 2

            Repeater
            {
                model: mainModel.buttonsName
                Button {
                    text: modelData
                    onClicked: {
                        // emit signal
                    }
                }
            }
        } // Row

        TextComponent {
            id: _details
            width: _root.width - 2
            height: _root.height - _row.height //- _resultLabel.height*3 - 8
            headerModel: mainModel.headerText()//["1", "2", "3", "4"]
            contentModel: mainModel.contetntText()//["ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд", "ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд", "ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд", "ыалдфдталоыварвыоипловытмлдвыопршщуаошлвыдоасьлодвыаошукрашовлыатсамлдвыаьловыптмловмтвыбтлд"]
        } // TextComponent
    } // Column

    color: "black"

}
