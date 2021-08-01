#pragma once

#include <memory>

#include "../Algorithms/Interface.hpp"
#include "../Algorithms/XOR/xor.h"
#include "../Algorithms/DESes/SDES/SDES.h"
#include "NavigationList/List.hpp"

namespace Model
{

class ViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QObject* view READ view NOTIFY viewChanged)
    Q_PROPERTY(QObject* navigationList READ navigationList CONSTANT)

public slots:
    void changeView(const QString& name)
    {
        qDebug() << "call" << name;
        if(m_currentView != name)
        {
            m_currentView = name;
            emit viewChanged();
        }
    }

signals:
    void viewChanged();

public:
    ViewModel(QObject* parent = nullptr)
        : QObject{parent},
          m_navigationList{new List::NavigationList(parent)},
          m_currentView{SDES}
    {
        m_algorithms.emplace(XOR, new Algorithms::XOR());
        m_algorithms.emplace(SDES, new Algorithms::SDES());

        QObject::connect(m_navigationList.get(), SIGNAL(listChanged(const QString&)), this, SLOT(changeView(const QString&)));
    }

    QObject* view()
    {
        qDebug() << "view" << m_currentView;
        if(m_algorithms.find(m_currentView) != m_algorithms.end())
            return m_algorithms.at(m_currentView)->model();

        qDebug() << "unknown view" << m_currentView;
        return nullptr;
    }

    QObject* navigationList() { return m_navigationList.get(); }

public:
    std::unordered_map<QString, std::unique_ptr<Algorithms::Interface>> m_algorithms;
    std::unique_ptr<List::NavigationList> m_navigationList;
    QString m_currentView;
};

} // namespace Model
