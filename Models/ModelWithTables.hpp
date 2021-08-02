#pragma once
#include <QObject>

#include "Components/Group.hpp"
#include "Components/Button.hpp"
#include "Components/Label.hpp"
#include "Components/Table.hpp"

namespace Model {

class ModelWithTables : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path CONSTANT)
    Q_PROPERTY(QObject* labels READ labels CONSTANT)
    Q_PROPERTY(QObject* buttons READ buttons CONSTANT)
    Q_PROPERTY(QObject* tables READ tables CONSTANT)

public:
    ModelWithTables(QObject* parent = nullptr)
        : QObject{parent},
          m_labels{new Components::Group()},
          m_buttons{new Components::Group()},
          m_tables{new Components::Group()}
    {}

    QObject* labels() { return m_labels.get(); }
    QObject* buttons() { return m_buttons.get(); }
    QObject* tables() { return m_tables.get(); }

    void addButton(const Components::ButtonInfo& buttonInfo)
    {
        m_buttons->addItem<Components::Button>(buttonInfo);
    }

    void addLabelGroup(const std::vector<Components::LabelInfo>& groupInfo)
    {
        m_labels->addGroup<Components::Label>(groupInfo);
    }

    void addTable(const Components::TableInfo& tableInfo)
    {
        m_tables->addItem<Components::Table>(tableInfo);
    }

    QString path() const { return "qrc:/UI/Views/ViewWithTables.qml"; }

private:
    std::unique_ptr<Components::Group> m_labels;
    std::unique_ptr<Components::Group> m_buttons;
    std::unique_ptr<Components::Group> m_tables;
};

} // namespace Model
