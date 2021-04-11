#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>

namespace Algorithm
{

struct Replacement
{
    static QString encode(const QString& text, const QString& permutationAlphabet)
    {
        QString result = text;
        const QChar firstLetter = u'а';

        std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c)
        {
            bool isUpper = c.isUpper();
            unsigned index = c.toLower().unicode() - firstLetter.unicode();
            QChar newChar = permutationAlphabet.at(index);
            return  isUpper ? newChar.toUpper() : newChar;
        });

        return result;
    }
};

} // namespace Algorithm
