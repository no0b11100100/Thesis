#include "xor.h"

void Algorithms::XOR::initButtons()
{
    Components::ButtonInfo key("generate", [&](){ generateKey(); });
    m_model->addButton(key);

    Components::ButtonInfo enc("encode", [&](){ encode(); });
    m_model->addButton(enc);

    Components::ButtonInfo dec("decode", [&](){ decode(); });
    m_model->addButton(dec);
}

void Algorithms::XOR::initLabels()
{
    Components::LabelInfo label("input", "", "enter string", true, [](const QString&){ return true; });
    m_model->addLabel(label);

    Components::LabelInfo label1("input1", "", "enter string1", false, [](const QString&){ return false; });
    m_model->addLabel(label1);
}

void Algorithms::XOR::initModel()
{
    initButtons();
    initLabels();
}

Algorithms::XOR::XOR()
    : m_model{new Model::DefaultView()}
{
    initModel();
}

void Algorithms::XOR::encode()
{

}

void Algorithms::XOR::decode()
{

}

void Algorithms::XOR::generateKey()
{

}

QObject *Algorithms::XOR::model()
{
    return m_model.get();
}
