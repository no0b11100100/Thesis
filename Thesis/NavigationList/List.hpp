#pragma once
#include <QObject>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace List {

class NavigationList : public QObject
{
    Q_OBJECT
public:
    NavigationList(QObject* parent = nullptr)
        : QObject{parent}
    {

        m_list = {
            {
                item("Crypto", {
                    { item("XOR", {}),
                      item("RSA", {}),
                      item("AES", {}),
                      item("RC", {
                          item("RC2", {}),
                          item("RC4", {}),
                          item("RC5", {}),
                          item("RC6", {})
                      }),
                      item("Vigenere", {})
                    }
                })
            },
        };
    }

private:
    struct item
    {
        QString _title;
        std::vector<item> _list;

        item(const QString& title, const std::vector<item>& list)
            : _title{title},
              _list{list}
        {}

    };

    std::vector<item> m_list;

};

}
