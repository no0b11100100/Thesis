#pragma once
#include <QObject>

namespace Components {

struct ActionButtonInfo {

    using ActionType = std::function<void()>;

    QString _text;
    ActionType _action;

    ActionButtonInfo() = default;

    ActionButtonInfo(const QString& text, ActionType action)
        : _text{text},
          _action{action}
    {}
};

class Button : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text CONSTANT)

    ActionButtonInfo m_info;

public:
    Button(QObject* parent = nullptr)
        : QObject{parent}
    {}

    void setData(const ActionButtonInfo& info) { m_info = info; }

    QString text() { return m_info._text; }

    Q_INVOKABLE void execute() { m_info._action(); }
};

}
