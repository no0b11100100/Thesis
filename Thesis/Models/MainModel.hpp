#pragma once

#include <memory>

#include "../Algorithms/Interface.hpp"
#include "../Algorithms/XOR/xor.h"

namespace Model
{

class ViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QObject* view READ view CONSTANT)

public:
    ViewModel(QObject* parent = nullptr)
        : QObject{parent}
    {
        m_algorithms.emplace("XOR", new Algorithms::XOR());
    }

    QObject* view() { return m_algorithms.at("XOR")->model(); }

public:
    std::unordered_map<QString, std::unique_ptr<Algorithms::Interface>> m_algorithms;
};

} // namespace Model
