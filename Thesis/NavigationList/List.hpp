#pragma once
#include <QObject>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "../Models/Components/Group.hpp"

namespace List {

class NavigationList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int size READ size NOTIFY listChanged)

signals:
    void listChanged();

public:
    NavigationList(QObject* parent = nullptr)
        : QObject{parent}
    {
        m_list = {
            {
                item("Crypto", {
                    item("RC", {
                        item("RC2", {}),
                        item("RC4", {}),
                        item("RC5", {}),
                        item("RC6", {})
                    }),
                    item("XOR", {}),
                    item("RSA", {}),
                    item("AES", {}),
                    item("Vigenere", {})
                })
            },
            {
                item("Hash", {}),
            },
        };


        for(auto& i : m_list)
            createLinks(i);

    }

    int size() const
    {
        if(m_current == nullptr)
            return m_list.size();
        else
            return m_current->_list.size();
    }

    Q_INVOKABLE QString name(int index)
    {
        if(m_current == nullptr)
            return m_list.at(index)._title;
        else
            return m_current->_list.at(index)._title;
    }

    Q_INVOKABLE void back()
    {
        qDebug() << "back" << (m_current == nullptr);
        if(m_current != nullptr)
            m_current = m_current->_prev;
        emit listChanged();
    }

    Q_INVOKABLE void ahead(const QString& name)
    {
        qDebug() << "ahead" << name;
        if(m_current == nullptr)
        {
            auto nameIndex = std::find_if(m_list.cbegin(), m_list.cend(), [name](const item& i){ return i._title == name; });
            if(nameIndex != m_list.cend())
            {
                auto index = std::distance(m_list.cbegin(), nameIndex);
                m_current = &m_list.at(index);
                emit listChanged();
            }
        }
        else
        {
            auto nameIndex = std::find_if(m_current->_list.cbegin(), m_current->_list.cend(), [name](const item& i){ return i._title == name; });
            if(nameIndex != m_current->_list.cend())
            {
                auto index = std::distance(m_current->_list.cbegin(), nameIndex);
                if(!m_current->_list.at(index)._list.empty())
                {
                    m_current = &m_current->_list.at(index);
//                    qDebug() << "check prev" << (m_current->_prev != nullptr);
                    emit listChanged();
                } else {
                    qDebug() << "no forward list";
                }
            } else {
                qDebug() << "can not find" << name;
            }
        }
    }

private:

    struct item
    {
        QString _title;
        std::vector<item> _list;
        item* _prev = nullptr;

        item(const QString& title, const std::vector<item>& list)
            : _title{title},
              _list{list}
        {
//            for(auto& item : _list)
//                item._prev = this;
        }

        void Print()
        {
            qDebug() << "item" << _title << _list.size();
        }
    };

    void createLinks(item& it)
    {
        if(it._list.empty()) return;
        for(auto& el : it._list)
        {
            el._prev = &it;
            createLinks(el);
        }
    }

    std::vector<item> m_list;
    item* m_current = nullptr;
};



}
