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

    static QChar predicate(const QString& alphabet, const QString& permutation, const QChar& c)
    {
        auto index = std::find(alphabet.cbegin(), alphabet.cend(), c.toLower());
        auto newIndex = std::distance(alphabet.cbegin(), index);
        return permutation.at(newIndex);
    }

public:

    static QString encode(const QString& text, const QString& permutationAlphabet)
    {
//        if(!validateKey(permutationAlphabet) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
//            return "";

        QString result = text;
        std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c)
        {
            return predicate(UKRAINIAN_ALPHABET, permutationAlphabet, c);
        });

        return result;
    }

    static QString decode(const QString& text, const QString& permutationAlphabet)
    {
        QString result = text;
        std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c)
        {
            return predicate(permutationAlphabet, UKRAINIAN_ALPHABET, c);
        });

        return result;
    }
};

} // namespace Algorithm
