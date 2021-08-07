#pragma once
#include <QObject>

#include <memory>

#include "Group.hpp"
#include "Label.hpp"

#include <QMetaProperty>

namespace Components {

struct TableInfo
{
    int _size;
    int _columnLimit;
    using TableGrid = std::vector<std::vector<Components::LabelInfo>>;
    TableGrid _items;

    TableInfo(int size, int columnLimit, const TableGrid& labels)
        : _size{size},
          _columnLimit{columnLimit},
          _items{labels}
    {}

    TableInfo() = default;
};

class Table : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int columnLimit READ columnLimit CONSTANT)
//    Q_PROPERTY(int size READ size CONSTANT)
    Q_PROPERTY(QObject* data READ data)
public:
    Table(QObject* parent = nullptr)
        : QObject(parent),
          m_data{new Components::Group(parent)}
    {}

    void setData(const TableInfo& info)
    {
        m_info = info;
        initTable();
    }

    int columnLimit() const { return m_info._columnLimit; }
//    int size() const { return m_info._size; }
    QObject* data() { return m_data.get(); }
private:

    void initTable()
    {
        for(auto group : m_info._items)
        {
            qDebug() << "group" << typeid(m_info._items).name() << typeid(group).name();
            m_data->addGroup<Components::Label>(group);
        }
    }

    std::unique_ptr<Components::Group> m_data;
    TableInfo m_info;
};

}
