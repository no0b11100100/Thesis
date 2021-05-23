#include "Replacement.h"

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

Description::Description Replacement::m_description = Description::Description();
