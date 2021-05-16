#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>

#include "../common/consts.h"
#include "../common/utils.h"

namespace Algorithm
{

class Replacement
{
    static bool validateKey(const QString& key)
    {
        return std::is_permutation(key.cbegin(), key.cend(), UKRAINIAN_ALPHABET.cbegin());
    }

public:

    static QString encode(const QString& text, const QString& permutationAlphabet)
    {
        if(!validateKey(permutationAlphabet) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
            return "";

        QString result = text;
        std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c)
        {
            auto index = std::find(UKRAINIAN_ALPHABET.cbegin(), UKRAINIAN_ALPHABET.cend(), c.toLower());
            auto newIndex = std::distance(UKRAINIAN_ALPHABET.cbegin(), index);
            return permutationAlphabet.at(newIndex);
        });

        return result;
    }
};

} // namespace Algorithm
