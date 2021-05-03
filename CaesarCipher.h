#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>

namespace Algorithm
{

struct CaesarCipher
{
    static QString encode(const QString& text, const unsigned& offset)
    {
        QString result = text;
        const QChar start = u'а';
        const QChar end = u'я';
        const QChar a = u'ё';
        qDebug() << "a" << a;
        auto validateChar = [&](const QChar& c){ return (c.toLower() >= start && c.toLower() <= end); };
        auto validateString = [&](const QString& str){ return std::all_of(str.begin(), str.end(), validateChar); };

        if(!validateString(text))
            return QString();

        std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c) -> QChar
        {
            unsigned _offset = c.unicode() + offset;
            unsigned newLetter = _offset > end.unicode() ? start.unicode() + (_offset - end.unicode()-1)
                                                         : _offset;
            QChar s(newLetter);
            return s;
        });

        qDebug() << "result" << result;

        return result;
    }
};

} // namespace Algorithm
