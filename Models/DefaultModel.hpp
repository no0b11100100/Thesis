#pragma once
#include <QObject>

#include <memory>

#include "Components/Button.hpp"
#include "Components/Label.hpp"
#include "Components/Group.hpp"

namespace Model {

class DefaultView : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* labels READ labels CONSTANT)
    Q_PROPERTY(QObject* buttons READ buttons CONSTANT)
    Q_PROPERTY(QString path READ path CONSTANT)

public:
    DefaultView(QObject* parent = nullptr)
        : QObject{parent},
          m_labels{new Components::Group{parent}},
          m_buttons{new Components::Group{parent}}
    {
    }

    QObject* labels() { return m_labels.get(); }
    QObject* buttons() { return m_buttons.get(); }

    void addButton(const Components::ButtonInfo& buttonInfo)
    {
        m_buttons->addItem<Components::Button>(buttonInfo);
    }

    void addLabel(const Components::LabelInfo& labelInfo)
    {
        m_labels->addItem<Components::Label>(labelInfo);
    }

    Components::Label* findLabelByName(const QString& name)
    {
        for(int i{0}; i < m_labels->size(); ++i)
        {
            QObject* object = m_labels->at(i);
            assert(typeid(*object) == typeid(Components::Label));
            Components::Label* label = static_cast<Components::Label*>(object);
//            assert(label != nullptr);
            if(label->name() == name)
                return label;
        }

        qDebug() << "findLabelByName return nullptr for " << name;

        return nullptr;
    }

    QString path() const { return "qrc:/UI/Views/DefaultView.qml"; }

private:

    std::unique_ptr<Components::Group> m_labels;
    std::unique_ptr<Components::Group> m_buttons;
};

} // namespace Model
