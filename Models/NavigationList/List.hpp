#pragma once
#include <QObject>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "../../common/const.hpp"

namespace List {

class StringList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int size READ size CONSTANT);

public:
    StringList(QObject* parent = nullptr)
        : QObject(parent)
    {}

    void add(const QString& str) { m_list.push_back(str); }
    void clear() { m_list.clear(); }
    int size() const { return m_list.size(); }
    Q_INVOKABLE QString at(int index) const { return m_list.at(index); }

private:
    std::vector<QString> m_list;
};

class NavigationList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* list READ list NOTIFY listChanged)
    Q_PROPERTY(int length READ maxLength CONSTANT)

signals:
    void listChanged(const QString&);

public:

    NavigationList(QObject* parent = nullptr)
        : QObject{parent},
          m_currentList{new StringList{parent}},
          m_maxLength{0}
    {
        m_list = {
            {
                item(CRYPTOGRAPHY_GROUP, {
                    item(RC, {
                        item(RC2, {}),
                        item(RC4, {}),
                        item(RC5, {}),
                        item(RC6, {})
                    }),
                    item(XOR, {}),
                    item(PERMUTATION, {}),
                    item(REPLACEMENT, {}),
                    item(RSA, {}),
                    item(AES, {}),
                    item(VIGENERE, {})
                })
            },
            {
                item(HASH_GROUP, {}),
            },
        };

        setCurrentList(m_list);

        for(auto& i : m_list)
            createLinks(i);

    }

    QObject* list() { return m_currentList.get(); }

    int maxLength() const { return m_maxLength; }

    Q_INVOKABLE void back()
    {
        qDebug() << "back" << (m_current == nullptr);
        if(m_current != nullptr)
        {
            m_current = m_current->_prev;
            if(m_current == nullptr)
                setCurrentList(m_list);
            else
                setCurrentList(m_current->_list);

            emit listChanged(TRANSIENT);
        }
    }

    Q_INVOKABLE void forward(const QString& name)
    {
        qDebug() << "forward" << name;
        if(m_current == nullptr)
        {
            auto nameIndex = std::find_if(m_list.cbegin(), m_list.cend(), [name](const item& i){ return i._title == name; });
            if(nameIndex != m_list.cend())
            {
                auto index = std::distance(m_list.cbegin(), nameIndex);
                m_current = &m_list.at(index);
                setCurrentList(m_current->_list);
                emit listChanged(TRANSIENT);
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
                    setCurrentList(m_current->_list);
                    emit listChanged(TRANSIENT);
                } else {
                    qDebug() << "no forward list";
                    emit listChanged(name);
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
        {}
    };

    void createLinks(item& it)
    {
        if(it._list.empty()) return;
        for(auto& el : it._list)
        {
            el._prev = &it;
            if(auto elSize = el._title.size(); elSize > m_maxLength)
                m_maxLength = elSize;
            createLinks(el);
        }
    }

    void setCurrentList(const std::vector<item>& items)
    {
        m_currentList->clear();
        for(const auto& item : items)
            m_currentList->add(item._title);
    }

    std::vector<item> m_list;
    std::unique_ptr<StringList> m_currentList;
    item* m_current = nullptr;
    int m_maxLength;
};



}
