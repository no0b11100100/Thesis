#pragma once
#include <QString>
#include <array>
#include <map>
#include <algorithm>
#include <QDebug>

namespace Algorithm
{

static QString alphabet = "abcdefghijklmnopqrstuvwxyz";

class Vigenere
{
    static void nextPermutation(QString& text)
    {
        QChar firstElem = text.front();
        for(auto i{0}; i < text.size()-1; ++i)
            text[i] = text[i+1];

        text[text.size()-1] = firstElem;
    }

    static std::array<QString, 26> fillTable()
    {
        std::array<QString, 26> result;
        result[0] = alphabet;
        for(int i{1}; i < alphabet.size(); ++i)
        {
            nextPermutation(alphabet);
            result[i] = alphabet;
        }

        return result;
    }

    static std::pair<int, int> getIndexs(const QChar& textChar, const QChar& keyChar)
    {
        auto keyIt = std::find(alphabet.begin(), alphabet.end(), keyChar);
        auto firstIndex = std::distance(alphabet.begin(), keyIt);
        auto textIt = std::find(alphabet.begin(), alphabet.end(), textChar);
        auto secondIndex = std::distance(alphabet.begin(), textIt);

        return {firstIndex-1, secondIndex-1};
    }

public:
    static QString encode(const QString& text, const QString& key)
    {
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

