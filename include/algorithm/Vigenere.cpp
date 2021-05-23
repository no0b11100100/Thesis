#include "Vigenere.h"

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

QString Vigenere::encode(const QString& text, const QString& key)
{
    //        if(!Utils::validateString(text, ONLY_UKRAINIAN_LETTERS) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
    //            return "";

    auto table = fillTable();
    auto encodeText = text;
    auto it = key.cbegin();

    std::transform(encodeText.begin(), encodeText.end(), encodeText.begin(), [&](const QChar& c)
    {
        if(it == key.cend()) it = key.cbegin();
        auto [row, column] = getIndexs(c.toLower(), it->toLower());
        ++it;
        return table[row][column];
    });

    return encodeText;
}

QString Vigenere::decode(const QString& text, const QString& key)
{
    auto table = fillTable();
    auto encodeText = text;
    auto it = key.cbegin();

    auto getIndex = [](const QString& alphabet, const QChar& c) -> int
    {
        return std::distance(alphabet.cbegin(), std::find(alphabet.cbegin(), alphabet.cend(), c));
    };

    std::transform(encodeText.begin(), encodeText.end(), encodeText.begin(), [&](const QChar& c)
    {
        if(it == key.cend()) it = key.cbegin();
        int rowIndex = getIndex(UKRAINIAN_ALPHABET, it->toLower());
        auto row = table.at(rowIndex);
        //            qDebug() << it->toLower() << row;
        auto index = getIndex(row, c.toLower());
        ++it;
        //            qDebug() << index;
        return UKRAINIAN_ALPHABET.at(index);
    });

    return encodeText;
}

