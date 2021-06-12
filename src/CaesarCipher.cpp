#include "../include/algorithm/CaesarCipher.h"
#include <random>
#include <algorithm>

using namespace Algorithm;

bool CaesarCipher::validateKey(const QString& key)
{
    int intKey = key.toInt();
    if(intKey > UKRAINIAN_ALPHABET_SIZE || intKey < 0)
        return false;

    return true;
}

ReturnType CaesarCipher::encode(const QString& text, const QString& offset)
{
    //        if(!validateKey(offset) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
    //            return "error";

    m_description.Clear();

    m_description.AddHeader(ENCODING);
    QString result = text;

    m_description.GetContentDetails() += "Вхідний текст: " + result + "\nКлюч: " + offset + "\nАбетка: " + UKRAINIAN_ALPHABET + "\nЕтапи:\n";

    int key = offset.toUInt();

    std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c) -> QChar
    {
        m_description.GetContentDetails() += "\tБеремо літеру '" + QString(c.toLower()) + "' зсуваємо на " + offset + " вправо і отримуємо '";
        auto it_c = std::find(UKRAINIAN_ALPHABET.cbegin(), UKRAINIAN_ALPHABET.cend(), c.toLower());
        auto index = std::distance(UKRAINIAN_ALPHABET.cbegin(), it_c);
        unsigned newIndex = index + key;
        if(newIndex < UKRAINIAN_ALPHABET_SIZE)
        {
            m_description.GetContentDetails() += QString(UKRAINIAN_ALPHABET[newIndex]) + "'\n";
            return UKRAINIAN_ALPHABET[newIndex];
        }
        else
        {
            m_description.GetContentDetails() += QString(UKRAINIAN_ALPHABET[newIndex - UKRAINIAN_ALPHABET_SIZE]) + "'\n";
            return UKRAINIAN_ALPHABET[newIndex - UKRAINIAN_ALPHABET_SIZE];
        }
    });

    m_description.GetContentDetails() += "В результаті отримуємо: " + result + "\n";

    qDebug() << "result" << result;

    m_description.AddContent();
    return {result, m_description};
}

ReturnType CaesarCipher::decode(const QString& text, const QString& offset)
{
    //        if(!validateKey(offset) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
    //            return "error";


    QString result = text;

    m_description.Clear();
    m_description.AddHeader(DECODING);
    m_description.GetContentDetails() += "Вхідний текст: " + result + "\nКлюч: " + offset + "\nАбетка: " + UKRAINIAN_ALPHABET + "\nЕтапи:\n";

    int key = offset.toUInt();
    std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c) -> QChar
    {
        m_description.GetContentDetails() += "\tБеремо літеру '" + QString(c.toLower()) + "' зсуваємо на " + offset + " вліво і отримуємо '";
        auto it_c = std::find(UKRAINIAN_ALPHABET.cbegin(), UKRAINIAN_ALPHABET.cend(), c.toLower());
        auto index = std::distance(UKRAINIAN_ALPHABET.cbegin(), it_c);
        int newIndex = index - key;
        qDebug() << "index" << newIndex;
        if(newIndex >= 0)
        {
            m_description.GetContentDetails() += QString(UKRAINIAN_ALPHABET[newIndex]) + "'\n";
            return UKRAINIAN_ALPHABET[newIndex];
        } else
        {
            m_description.GetContentDetails() += QString(UKRAINIAN_ALPHABET[newIndex + UKRAINIAN_ALPHABET_SIZE]) + "'\n";
            return UKRAINIAN_ALPHABET[UKRAINIAN_ALPHABET_SIZE + newIndex];
        }
    });

    m_description.GetContentDetails() += "В результаті отримуємо: " + result + "\n";

    m_description.AddContent();

    return {result, m_description};
}

QString CaesarCipher::generateKey()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::array<QString, 4> keys {"12", "7", "3", "27"};
    std::shuffle(keys.begin(), keys.end(), g);

    return keys.front();
}

bool CaesarCipher::validate(const QString & text, const QString & key)
{
    auto validateKey = [](const QString& key)
    {
        bool isNumbaers;
        int iKey = key.toInt(&isNumbaers);
        return !key.isEmpty() && key.size() <= 2 && isNumbaers && iKey >= 0 && iKey < UKRAINIAN_ALPHABET_SIZE;
    };

    return Utils::validateString(text, UKRAINIAN_ALPHABET) && validateKey(key);
}

Description::Description CaesarCipher::m_description = Description::Description();
