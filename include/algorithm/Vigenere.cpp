#include "Vigenere.h"
#include <random>
#include <algorithm>

using namespace Algorithm;

Vigenere::TableType Vigenere::fillTable()
{
    Vigenere::TableType result;
    result[0] = UKRAINIAN_ALPHABET;
    for(int i{1}; i < UKRAINIAN_ALPHABET_SIZE; ++i)
        result[i] = Utils::cycleShift(result[i-1], Utils::ShiftDirection::Left);

    return result;
}

std::pair<int, int> Vigenere::getIndexs(const QChar& textChar, const QChar& keyChar)
{
    auto keyIt = std::find(UKRAINIAN_ALPHABET.begin(), UKRAINIAN_ALPHABET.end(), keyChar);
    auto firstIndex = std::distance(UKRAINIAN_ALPHABET.begin(), keyIt);
    auto textIt = std::find(UKRAINIAN_ALPHABET.begin(), UKRAINIAN_ALPHABET.end(), textChar);
    auto secondIndex = std::distance(UKRAINIAN_ALPHABET.begin(), textIt);

    return {firstIndex, secondIndex};
}

void Vigenere::createTableDescription(const Vigenere::TableType& table)
{
    m_description.Clear();

    m_description.AddHeader(VIGENERE_TABLE);
    m_description.GetContentDetails() += TAB + "Сформуємо таблицю Віженера:\n" + DOUBLE_TAB + "   " + UKRAINIAN_ALPHABET + "\n";
    for(const auto& row : table)
        m_description.GetContentDetails() += DOUBLE_TAB + row.at(0) + " " + row + "\n";

    m_description.AddContent();
}

ReturnType Vigenere::encode(const QString& text, const QString& key)
{
    //        if(!Utils::validateString(text, ONLY_UKRAINIAN_LETTERS) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
    //            return "";

    auto table = fillTable();
    auto encodeText = text;
    auto it = key.cbegin();

   createTableDescription(table);

    m_description.AddHeader(ENCODING);
    m_description.GetContentDetails() += "Вхідний текст: " + encodeText + "\nКлюч: " + key + "\nАбетка: " + UKRAINIAN_ALPHABET + "\nЕтапи:\n";

    m_description.GetContentDetails() += TAB + "Для формування літери шифротексту необхідно узять літеру ключа та литеру вікдритого тексту:\n";

    std::transform(encodeText.begin(), encodeText.end(), encodeText.begin(), [&](const QChar& c)
    {
        if(it == key.cend()) it = key.cbegin();
        m_description.GetContentDetails() += DOUBLE_TAB + "літера ключа '" + QString(it->toLower()) +  "' є строчкою в таблиці, а літера тексту '" + QString(c.toLower()) + "' э столбцем.";
        auto [row, column] = getIndexs(c.toLower(), it->toLower());
        ++it;
        m_description.GetContentDetails() += " На перетині цих двох літер знаходиться літера шифротексту '" + QString(table[row][column]) + "'\n";
        return table[row][column];
    });

    m_description.GetContentDetails() += "В результаті отримуємо: " + encodeText + "\n";
    m_description.AddContent();

    return {encodeText, m_description};
}

ReturnType Vigenere::decode(const QString& text, const QString& key)
{
    auto table = fillTable();
    auto encodeText = text;
    auto it = key.cbegin();

    createTableDescription(table);

    m_description.AddHeader(DECODING);
    m_description.GetContentDetails() += "Вхідний текст: " + encodeText + "\nКлюч: " + key + "\nАбетка: " + UKRAINIAN_ALPHABET + "\nЕтапи:\n";
//    m_description.GetContentDetails() += TAB + "Для декодування необхідно знайти строку для літери ключа, в цій строці знайти літеру шифротексту и литера цього стовбця и буде літерою відкритого тексту:\n";

    auto getIndex = [](const QString& alphabet, const QChar& c) -> int
    {
        return std::distance(alphabet.cbegin(), std::find(alphabet.cbegin(), alphabet.cend(), c));
    };

    std::transform(encodeText.begin(), encodeText.end(), encodeText.begin(), [&](const QChar& c)
    {
        if(it == key.cend()) it = key.cbegin();
        int rowIndex = getIndex(UKRAINIAN_ALPHABET, it->toLower());
        auto row = table.at(rowIndex);
        m_description.GetContentDetails() += DOUBLE_TAB + "Знаходимо строку для літері ключа '" + it->toLower() + "' " + row + ".";
        //            qDebug() << it->toLower() << row;
        auto index = getIndex(row, c.toLower());
        m_description.GetContentDetails() += " Після цього знаходимо позицію літери(" + QString(c.toLower()) + ") шифротексту в знайденій строці: " + QString::number(index) + ", що відповідає стовбцю '" + UKRAINIAN_ALPHABET.at(index) + "'\n";
        ++it;
        //            qDebug() << index;
        return UKRAINIAN_ALPHABET.at(index);
    });

    m_description.GetContentDetails() += "В результаті отримуємо: " + encodeText + "\n";
    m_description.AddContent();

        return {encodeText, m_description};
    }

QString Vigenere::generateKey()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::array<QString, 3> keys {"кібербезпека", "криптографія", "криптоаналіз"};
    std::shuffle(keys.begin(), keys.end(), g);

    return keys.front();
}

Description::Description Vigenere::m_description = Description::Description();

