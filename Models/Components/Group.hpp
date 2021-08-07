#pragma once
#include <QObject>
#include <QDebug>

#include <vector>
#include <memory>

namespace Components {


class Group : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int size READ size CONSTANT)

public:
    Group(QObject* parent = nullptr)
        : QObject{parent}
    {}

    int size() const { return m_items.size(); }

    Q_INVOKABLE QObject* at(int index) { return m_items.at(index).get(); }

    template<class T, class Info>
    void addItem(const Info& info)
    {
        auto item = std::make_unique<T>();
        item->setData(info);
        m_items.push_back(std::move(item));
    }

    template<class T, class Info>
    void addGroup(const std::vector<Info>& info)
    {
        auto group = std::make_unique<Components::Group>();
        for(const auto& item : info)
            group->addItem<T>(item);

        m_items.push_back(std::move(group));
    }

private:

    std::vector<std::unique_ptr<QObject>> m_items;
};


}
