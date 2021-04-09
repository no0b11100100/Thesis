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
        using Type = uchar;//QChar;
        QString result = text;
        const Type start = 'a';
        const Type end = 'z';
        auto validateChar = [&](const Type& c){ return c >= start && c <= end;};
        auto toInt = [](const Type& c){ return static_cast<int>(c); };
        auto toChar = [](const int& i) -> Type{ return static_cast<Type>(i); };


        std::transform(text.begin(), text.end(), result.begin(), [&](const QChar& c) -> QChar
        {
            bool isUpper = c.isUpper();
            auto tmp = c.toLower().toLatin1();
            if(validateChar(tmp))
            {
                auto currentIndex = toInt(tmp);
                auto newIndex = currentIndex+offset;
                uchar encodeChar = (newIndex) > end ? toChar( toInt(start) + (  newIndex % (end+1) ) )
                                                    : toChar(newIndex);
                return  isUpper ? QChar(encodeChar).toUpper()
                                : QChar(encodeChar);
            }
            return QChar();
        });

        qDebug() << result;

        return result;
    }
};

} // namespace Algorithm
