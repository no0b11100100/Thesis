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

//    Q_PROPERTY(QObject* button READ button CONSTANT)

    Q_PROPERTY(int buttonCount READ buttonCount CONSTANT)
    Q_PROPERTY(QObject* button READ button CONSTANT)

public:
    DefaultView(QObject* parent = nullptr)
        : QObject{parent},
          m_button{new Components::Button(parent)}
    {
        Components::ButtonInfo key("generate", [&](){});
        m_button->setData(key);
    }

    QObject* button(/*int index*/) {
//        qDebug() << "button" << m_buttons.at(index).get()->text();

//        return m_buttons.at(index).get();
        return m_button.get();
    }
//    Q_INVOKABLE QObject* group(int index) const { return m_labels.at(index).get(); }

    int buttonCount() const { return m_buttons.size(); }

    void addButton(const Components::ButtonInfo& buttonInfo)
    {
        auto item = std::make_unique<Components::Button>();
        item->setData(buttonInfo);
        m_buttons.push_back(std::move(item));

//        qDebug() << m_buttons.back()->text();
    }

private:

    std::unique_ptr<Components::Button> m_button;

    std::vector<std::unique_ptr<Components::Button>> m_buttons;

//    std::vector<std::unique_ptr<Components::Group>> m_labels;
};

} // namespace Model
