#pragma once
#include <QObject>

namespace Components {

struct BackButtonInfo {

    using ActionType = std::function<void()>;

    QChar symbol = '<';
    ActionType _action;

    BackButtonInfo() = default;

    BackButtonInfo(ActionType action)
          : _action{action}
    {}
};

class BackButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QChar text READ text CONSTANT)

    BackButtonInfo m_info;

public:
    BackButton(QObject* parent = nullptr)
        : QObject{parent}
    {}

    void setData(const BackButtonInfo& info) { m_info = info; }

    QChar text() { return m_info.symbol; }

    Q_INVOKABLE void execute() { m_info._action(); }
};

}
