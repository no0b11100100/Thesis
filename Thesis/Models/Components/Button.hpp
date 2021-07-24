#pragma once
#include <QObject>

namespace Components {

class ButtonInfo {

    using ActionType = std::function<void()>;

    QString m_text;
    ActionType m_action;

public:
    ButtonInfo() = default;

    ButtonInfo(const QString& text, ActionType action)
        : m_text{text},
          m_action{action}
    {}

    QString getText() { return m_text; }
    void setText(const QString& text) { m_text = text; }

    void executeAction() const { return m_action(); }
    void setAction(ActionType action) { m_action = action; }
};

class Button : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text CONSTANT)

    ButtonInfo m_info;

public:
    Button(QObject* parent = nullptr)
        : QObject{parent}
    {}

    void setData(const ButtonInfo& info) { m_info = info; }

    QString text() { return m_info.getText(); }

    Q_INVOKABLE void execute() { m_info.executeAction(); }
};

}
