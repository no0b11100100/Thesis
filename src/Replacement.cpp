#include "../include/algorithm/Replacement.h"
#include <random>
#include <algorithm>
using namespace Algorithm;

bool Replacement::validateKey(const QString& key)
{
    return std::is_permutation(key.cbegin(), key.cend(), UKRAINIAN_ALPHABET.cbegin());
}

QChar Replacement::predicate(const QString& alphabet, const QString& permutation, const QChar& c)
{
    auto index = std::find(alphabet.cbegin(), alphabet.cend(), c.toLower());
    auto newIndex = std::distance(alphabet.cbegin(), index);
    m_description.GetContentDetails() += "літері '" + QString(c.toLower()) + "' буде відповідати '" + QString(permutation.at(newIndex)) + "'\n";
    return permutation.at(newIndex);
}

ReturnType Replacement::encode(const QString& text, const QString& permutationAlphabet)
{
    //        if(!validateKey(permutationAlphabet) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
    //            return "";

    QString result = text;
    m_description.Clear();
    m_description.AddHeader(ENCODING);
    m_description.GetContentDetails() += "Вхідний текст: " + result + "\nКлюч: " + permutationAlphabet + "\nАбетка: " + UKRAINIAN_ALPHABET + "\nЕтапи:\n";
    std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c)
    {
        return predicate(UKRAINIAN_ALPHABET, permutationAlphabet, c);
    });

    m_description.GetContentDetails() += "В результаті отримуємо: " + result + "\n";

    qDebug() << m_description.GetContentDetails();

    m_description.AddContent();

    qDebug() << m_description.GetContentDetails();

    return {result, m_description};
}

ReturnType Replacement::decode(const QString& text, const QString& permutationAlphabet)
{
    QString result = text;
    m_description.Clear();
    m_description.AddHeader(DECODING);
    m_description.GetContentDetails() += "Вхідний текст: " + result + "\nКлюч: " + permutationAlphabet + "\nАбетка: " + UKRAINIAN_ALPHABET + "\nЕтапи:\n";
    std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c)
    {
        return predicate(permutationAlphabet, UKRAINIAN_ALPHABET, c);
    });

    m_description.GetContentDetails() += "В результаті отримуємо: " + result + "\n";

    m_description.AddContent();

    return {result, m_description};
}

QString Replacement::generateKey()
{
    std::random_device rd;
    std::mt19937 g(rd());
    auto key = UKRAINIAN_ALPHABET;
    std::shuffle(key.begin(), key.end(), g);
    return key;
}

bool Replacement::validate(const QString & text, const QString & key)
{
    auto validateKey = [](const QString& key)
    {
        if(key.size() != UKRAINIAN_ALPHABET_SIZE) return false;
        return std::is_permutation(UKRAINIAN_ALPHABET.cbegin(), UKRAINIAN_ALPHABET.cend(), key.cbegin());
    };
    return Utils::validateString(text, UKRAINIAN_ALPHABET) && validateKey(key);
}

Description::Description Replacement::m_description = Description::Description();
