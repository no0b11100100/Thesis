#pragma once
#include <QObject>

namespace Components {

struct ListItemInfo {

    using ActionType = std::function<void(const QString&)>;

    QString _text;
    ActionType _action;

    ListItemInfo() = default;

    ListItemInfo(const QString& text, ActionType action)
        : _text{text},
         _action{action}
    {}
};

class ItemButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QChar text READ text CONSTANT)

    ListItemInfo m_info;

public:
    ItemButton(QObject* parent = nullptr)
        : QObject{parent}
    {}

    void setData(const ListItemInfo& info) { m_info = info; }

    QString text() { return m_info._text; }

    Q_INVOKABLE void execute(const QString& name) { m_info._action(name); }
};

}
