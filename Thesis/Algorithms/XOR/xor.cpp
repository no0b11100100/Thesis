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

void Algorithms::XOR::initModel()
{
    initButtons();
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
