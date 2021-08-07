#include "SDES.h"

#include <QDebug>

void Algorithms::SDES::initTables()
{
    Components::TableInfo::TableGrid a {
        {Components::LabelInfo("", "text", "", true, 1, false, [](const QString&){ return true; })},
        {Components::LabelInfo("", "text", "", true, 1, false, [](const QString&){ return true; })},
        {Components::LabelInfo("", "text", "", true, 1, false, [](const QString&){ return true; })},
    };

    Components::TableInfo sbox(3,1, a);
    m_model->addTable(sbox);
    m_model->addTable(sbox);
}

void Algorithms::SDES::initButtons()
{
    Components::ButtonInfo generateKeyButton("Key", [&](){ generateKey(); });
    m_model->addButton(generateKeyButton);

    Components::ButtonInfo encodeButton("encode", [&](){ encode(); });
    m_model->addButton(encodeButton);

    Components::ButtonInfo decodeButton("decode", [&](){ decode(); });
    m_model->addButton(decodeButton);
}

void Algorithms::SDES::initLabels()
{
    m_model->addLabelGroup({Components::LabelInfo("Text", "", "Text", true, 1, false, [](const QString&){ return true; })});
    m_model->addLabelGroup({Components::LabelInfo("Key", "", "Key", true, 1, false, [](const QString&){ return true; })});
    m_model->addLabelGroup({
                Components::LabelInfo("IP", "", "IP", true, 1, false, [](const QString&){ return true; }),
                Components::LabelInfo("EXPANDED", "", "EXPANDED", true, 1, false, [](const QString&){ return true; }),
                      });
    m_model->addLabelGroup({
                Components::LabelInfo("SBOX_PERMUTATION", "", "SBOX_PERMUTATION", true, 1, false, [](const QString&){ return true; }),
                Components::LabelInfo("IP_1", "", "IP_1", true, 1, false, [](const QString&){ return true; }),
                      });
    m_model->addLabelGroup({
                Components::LabelInfo("P_10", "", "P_10", true, 1, false, [](const QString&){ return true; }),
                Components::LabelInfo("P_8", "", "P_8", true, 1, false, [](const QString&){ return true; }),
                      });
    m_model->addLabelGroup({Components::LabelInfo("RESULT", "", "RESULT", true, 1, false, [](const QString&){ return true; })});
}

void Algorithms::SDES::initModel()
{
    initLabels();
    initButtons();
    initTables();
}

Algorithms::SDES::SDES()
    : m_model{new Model::ModelWithTables()}
{
    for(auto& el : m_sBox)
        el = std::make_unique<Components::Table>();

    initModel();
}

void Algorithms::SDES::encode()
{}

void Algorithms::SDES::decode()
{}

void Algorithms::SDES::generateKey()
{}

QObject *Algorithms::SDES::model() { qDebug() << (m_model.get() == nullptr);  return m_model.get(); }
