#pragma once

#include <memory>

#include "../Interface.hpp"
#include "../../Models/DefaultModel.hpp"

namespace Algorithms {

class XOR : public Interface
{
    std::unique_ptr<Model::DefaultView> m_model;
    void initButtons();
    void initLabels();
    void initModel();
public:
    XOR();
    void encode() override;
    void decode() override;
    void generateKey() override;

    QObject *model() override;
};

}
