#include "xor.h"
#include "const.h"

void Algorithms::XOR::initButtons()
{
    Components::ButtonInfo generateKeyButton(GENERATE_KEY, [&](){ generateKey(); });
    m_model->addButton(generateKeyButton);

    Components::ButtonInfo encodeButton(ENCODE, [&](){ encode(); });
    m_model->addButton(encodeButton);

    Components::ButtonInfo decodeButton(DECODE, [&](){ decode(); });
    m_model->addButton(decodeButton);
}

void Algorithms::XOR::initLabels()
{
    Components::LabelInfo input(INPUT, "", INPUT, true, 3, false, [](const QString&){ return true; });
    m_model->addLabel(input);

    Components::LabelInfo key(KEY, "", KEY, false, 3, false, [](const QString&){ return true; });
    m_model->addLabel(key);

    Components::LabelInfo result(RESULT, "", RESULT, 3, false, true, [](const QString&){ return true; });
    m_model->addLabel(result);
}

void Algorithms::XOR::initModel()
{
    initButtons();
    initLabels();
}

Algorithms::XOR::XOR()
    : m_model{new Model::DefaultView()},
      m_impl{details::XORImpl()}
{
    initModel();
}

void Algorithms::XOR::encode()
{
    std::string text = m_model->findLabelByName(INPUT)->text().toStdString();
    std::string key = m_model->findLabelByName(KEY)->text().toStdString();
    auto result = m_impl.encode(text, key);
    m_model->findLabelByName(RESULT)->setText(QString::fromStdString(result));
    emit m_model->findLabelByName(RESULT)->textChanged();
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
