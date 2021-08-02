#pragma once

#include <memory>
#include <array>

#include "../../Interface.hpp"
#include "../../../Models/ModelWithTables.hpp"
#include "../../../Models/Components/Table.hpp"

namespace Algorithms {

class SDES : public Interface
{
    static constexpr int tableCount = 2;
    std::unique_ptr<Model::ModelWithTables> m_model;
    std::array<std::unique_ptr<Components::Table>, 2> m_sBox;
    void initTables();
    void initButtons();
    void initLabels();
    void initModel();
public:
    SDES();
    void encode() override;
    void decode() override;
    void generateKey() override;

    QObject *model() override;
};

}
