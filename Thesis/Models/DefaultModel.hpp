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

    Q_PROPERTY(int buttonCount READ buttonCount CONSTANT)

    Q_PROPERTY(QObject* labels READ labels CONSTANT)

public:
    DefaultView(QObject* parent = nullptr)
        : QObject{parent},
          m_labels{new Components::Group{parent}}
    {
    }

    QObject* labels() { return m_labels.get(); }

    Q_INVOKABLE QObject* buttonAt(int index) {
        return m_buttons.at(index).get();
    }

    int buttonCount() const { return m_buttons.size(); }

    void addButton(const Components::ButtonInfo& buttonInfo)
    {
        auto item = std::make_unique<Components::Button>();
        item->setData(buttonInfo);
        m_buttons.push_back(std::move(item));

    }

    void addLabel(const Components::LabelInfo& labelInfo)
    {
//        auto label = std::make_unique<Components::Label>();
//        label->setData(labelInfo);
//        m_labels.push_back(std::move(label));
        m_labels->addItem<Components::Label>(labelInfo);
    }

private:

    std::vector<std::unique_ptr<Components::Button>> m_buttons;
//    std::vector<std::unique_ptr<Components::Label>> m_labels;
    std::unique_ptr<Components::Group> m_labels;
};

} // namespace Model
