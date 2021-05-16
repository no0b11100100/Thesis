#pragma once
#include <QString>
#include <array>
#include <map>
#include <algorithm>
#include <QDebug>

#include "../common/consts.h"
#include "../common/utils.h"

namespace Algorithm
{

class Vigenere
{
    using TableType = std::array<QString, UKRAINIAN_ALPHABET_SIZE>;

    static TableType fillTable()
    {
        TableType result;
        result[0] = UKRAINIAN_ALPHABET;
        for(int i{1}; i < UKRAINIAN_ALPHABET_SIZE; ++i)
            result[i] = Utils::cycleShift(result[i-1], Utils::ShiftDirection::Left);

        return result;
    }

    static std::pair<int, int> getIndexs(const QChar& textChar, const QChar& keyChar)
    {
        auto keyIt = std::find(UKRAINIAN_ALPHABET.begin(), UKRAINIAN_ALPHABET.end(), keyChar);
        auto firstIndex = std::distance(UKRAINIAN_ALPHABET.begin(), keyIt);
        auto textIt = std::find(UKRAINIAN_ALPHABET.begin(), UKRAINIAN_ALPHABET.end(), textChar);
        auto secondIndex = std::distance(UKRAINIAN_ALPHABET.begin(), textIt);

        return {firstIndex, secondIndex};
    }

public:
    static QString encode(const QString& text, const QString& key)
    {
        if(!Utils::validateString(text, ONLY_UKRAINIAN_LETTERS) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
            return "";

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
};

} // namespace Algorithm

