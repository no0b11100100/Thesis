#pragma once
#include <QObject>

#include "Components/Group.hpp"
#include "Components/Button.hpp"
#include "Components/Label.hpp"

namespace Model {

class ModelWithTables : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path CONSTANT)
    Q_PROPERTY(QObject* labels READ labels CONSTANT)
    Q_PROPERTY(QObject* buttons READ buttons CONSTANT)

public:
    ModelWithTables(QObject* parent = nullptr)
        : QObject{parent},
          m_labels{new Components::Group()},
          m_buttons{new Components::Group()}
    {}

    QObject* labels() { return m_labels.get(); }
    QObject* buttons() { return m_buttons.get(); }

    void addButton(const Components::ButtonInfo& buttonInfo)
    {
        m_buttons->addItem<Components::Button>(buttonInfo);
    }

    void addGroup(const std::vector<Components::LabelInfo>& groupInfo)
    {
        auto group = std::make_unique<Components::Group>();

        for(const auto& info : groupInfo)
            group->addItem<Components::Label>(info);

        m_labels->addGroup(std::move(group));
    }

    QString path() const { return "qrc:/UI/Views/ViewWithTables.qml"; }

private:
    std::unique_ptr<Components::Group> m_labels;
    std::unique_ptr<Components::Group> m_buttons;
    // TODO: add tables for sdoxes
};

} // namespace Model
