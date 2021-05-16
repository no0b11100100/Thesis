#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "../common/consts.h"
#include "../common/utils.h"

namespace Algorithm
{

class CaesarCipher
{
    static bool validateKey(const QString& key)
    {
        int intKey = key.toInt();
        if(intKey > UKRAINIAN_ALPHABET_SIZE || intKey < 0)
            return false;

        return true;
    }

public:
    static QString encode(const QString& text, const QString& offset)
    {
        if(!validateKey(offset) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
            return "";

        QString result = text;
        int key = offset.toUInt();
        std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c) -> QChar
        {
            auto it_c = std::find(UKRAINIAN_ALPHABET.cbegin(), UKRAINIAN_ALPHABET.cend(), c.toLower());
            auto index = std::distance(UKRAINIAN_ALPHABET.cbegin(), it_c);
            unsigned newIndex = index + key;
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
