#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>

#include "include/common/consts.h"

namespace Algorithm
{

struct CaesarCipher
{
    static QString encode(const QString& text, const unsigned& offset)
    {
        QString result = text;
        std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c) -> QChar
        {
            auto it_c = std::find(UKRAINIAN_ALPHABET.cbegin(), UKRAINIAN_ALPHABET.cend(), c.toLower());
            auto index = std::distance(UKRAINIAN_ALPHABET.cbegin(), it_c);
            unsigned newIndex = index + offset;
            if(newIndex < UKRAINIAN_ALPHABET_SIZE)
                return UKRAINIAN_ALPHABET[newIndex];
            else {
                return UKRAINIAN_ALPHABET[newIndex - UKRAINIAN_ALPHABET_SIZE];
            }
        });

        qDebug() << "result" << result;

        return result;
    }
};

} // namespace Algorithm
