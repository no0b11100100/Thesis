#pragma once

#include <memory>

#include "../../Interface.hpp"
#include "../../../Models/ModelWithTables.hpp"

namespace Algorithms {

class SDES : public Interface
{
    std::unique_ptr<Model::ModelWithTables> m_model;
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
