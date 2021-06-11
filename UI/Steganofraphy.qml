import QtQuick 2.0
import QtQuick.Controls 2.15 as Controls2
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.15

Rectangle {
    property var trigger
    property string text: "asd"
    id: _root

    function createModel(count) {
        var items = []
        const prefix = "Drag image "
        for(var i = 0; i < count; ++i)
            items.push(prefix + (i+1))
        return items
    }

    Column {
        spacing: 1

        Controls2.TextArea {
            id: _text
            width: _root.width
            placeholderText: _root.text
            readOnly: _repeater.count !== 1
            background: Rectangle {
                color: "grey"
            }
        }

        Row {
            spacing: 2
            Controls1.GroupBox {
                id: _groupBox
                property string activeAction: _encode.action
                signal actionChaged()
                RowLayout {
                    Controls1.ExclusiveGroup {
                        id: tabPositionGroup

                        onCurrentChanged: {
                            console.log("change", tabPositionGroup.current.action)
                            _groupBox.activeAction = tabPositionGroup.current.action
                            _groupBox.actionChaged()
                        }
                    }

                    Controls1.RadioButton {
                        readonly property string action: "Зашифрувати"
                        id: _encode
                        checked: true
                        exclusiveGroup: tabPositionGroup
                        style: RadioButtonStyle {
                            label: Text {
                                text: _encode.action
                                color: "black"
                            }
                        }

                        Component.onCompleted: {
                            console.log("text")
                        }
                    }
                    Controls1.RadioButton {
                        readonly property string action: "Розшифрувати"
                        id: _decode
                        exclusiveGroup: tabPositionGroup
                        style: RadioButtonStyle {
                            label: Text {
                                text: _decode.action
                                color: "black"
                            }
                        }
                    }
                }

                onActionChaged: {
                    _text.text = "";
                }
            }

            Controls2.Button {
                text: "Виконати"
                height: _groupBox.height

                onPressed: {
                    if(_groupBox.activeAction === "Зашифрувати")
                        _root.trigger(_groupBox.activeAction, _repeater.itemAt(0).filePath, _text.text)
                    else
                         _root.trigger(_groupBox.activeAction, _repeater.itemAt(0).filePath, _repeater.itemAt(1).filePath)
                }
            }
        }

        Row {
            spacing: 1
            Repeater{
                id: _repeater
                model: createModel(_groupBox.activeAction === "Зашифрувати" ? 1 : 2)

                DragAndDropArea {
                    height: _root.height
                    width: _root.width / _repeater.count
                    text: modelData
                }
            }
        }
    }
}
