#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>

#include "include/common/consts.h"

namespace Algorithm
{

struct Replacement
{
    static QString encode(const QString& text, const QString& permutationAlphabet)
    {
        QString result = text;
        std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c)
        {
            bool isUpper = c.isUpper();
            auto index = std::find(UKRAINIAN_ALPHABET.cbegin(), UKRAINIAN_ALPHABET.cend(), c.toLower());
            auto newIndex = std::distance(UKRAINIAN_ALPHABET.cbegin(), index);
            return isUpper ? UKRAINIAN_ALPHABET.at(newIndex).toUpper()
                           : UKRAINIAN_ALPHABET.at(newIndex);
        });

        return result;
    }
};

} // namespace Algorithm
