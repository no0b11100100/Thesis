#pragma once
#include <QString>
#include <QDebug>
#include <unordered_map>
#include <cmath>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include <algorithm>

#include "consts.h"

class Utils
{
    template<class Iterator>
    static void shift(Iterator start, Iterator end)
    {
        auto tmp = *start;
        for(; start != end; ++start)
            *start = *std::next(start);

        *std::prev(end) = tmp;
    }

    static QChar binToDecimal(const QString& data)
    {
        assert(data.size() % 8 == 0);
        constexpr std::array<int, 8> pow{128, 64, 32, 16, 8, 4, 2, 1};
        int res = 0;

        int i = 0;
        for(const auto& bit : data)
        {
            if(bit == "1")
                res += pow.at(i);
            ++i;
        }

        return QChar(res);
    }

public:
    static QString stringToBin(const QString& str)
    {
        QString res = "";
        for(const auto& v : str.toLatin1())
            res += QString("%1").arg(v, 8, 2, QChar('0'));
        //QString::number(static_cast<int>(v), 2);
        return res;
    }

    static QString binToString(const QString binData)
    {
        assert(binData.size() % 8 == 0);
        QString res = "";

        constexpr int step = 8;
        auto makeChan = [](const QString& data, int currentIndex)
        {
            return data.mid(currentIndex, step);
        };

        for(int index = 0; index < binData.size(); index += step)
            res +=  binToDecimal(makeChan(binData, index));
        return res;
    }

    static QChar hexToChar(const QString hex)
    {
        assert(hex.size() == 2);
        bool status = false;
        unsigned hexValue = hex.toUInt(&status, 16);
        assert(status == true);
        return QChar(hexValue);
    }

    enum class ShiftDirection : bool
    {
        Left,
        Right,
    };

    static QString cycleShift(const QString& str, const ShiftDirection& direction, unsigned loops = 1)
    {
        QString result = str;

        for(unsigned i{0}; i < loops; ++i)
        {
            if(direction == ShiftDirection::Left)
                shift(result.begin(), result.end());
            else
                shift(result.rbegin(), result.rend());

        }
//        qDebug() << result;
        return result;
    }

    static size_t powMod(const size_t& number, const size_t& pow, const size_t& mod)
    {
        if(mod == 0) return 0;
        if(pow == 0) return 1 % mod;
        if(pow == 1) return number % mod;

        auto countBits = [](const size_t& number) -> size_t
        {
            return static_cast<size_t>(log2(number));
        };

        size_t result{1};
        size_t tempResult = number;
        size_t _pow = pow;

        while(_pow)
        {
            if(_pow == 1)
            {
                result = (result * number) % mod;
                break;
            }
            size_t count = countBits(_pow);
            for(size_t i{0}; i < count; ++i)
                tempResult = (tempResult * tempResult) % mod;

            _pow -= 1 << count;
            result = (result * tempResult) % mod;
            tempResult = std::move(number);
        }

        return result;
    }

    static QString prettyHex(const QString& str)
    {
        QString hex = "";
        for(const auto& c : str)
        {
            auto hexValue = c.cell();
            auto convertHex = QString::number(hexValue, 16);
            hex += convertHex.size() == 1 ? "0" + convertHex : convertHex;
        }

        return hex;
    }

    static bool validateString(const QString& text, const QString& alphabet)
    {
        for(const auto& v : text)
            if(!std::any_of(alphabet.cbegin(), alphabet.cend(), [&](const QChar& c)
            {
                return v.toLower() == c;
            }))
                return false;

        return !text.isEmpty();
    }

    static bool validateSequence(const QStringList& sequence)
    {
        qDebug() << "validateSequence" << sequence;
        for(int i = 0; i < sequence.size(); ++i)
            if(std::find(sequence.cbegin(), sequence.cend(), QString::number(i+1)) == sequence.cend() )
                return false;

        return !sequence.isEmpty();
    }

    static bool validateStringList(const QStringList& list)
    {
        int size = list.size();
        if(size == 4 || size == 8 || size == 10)
            return std::is_permutation(list.cbegin(), list.cend(),
                                   size == 4 ? PERMUTATION_4.cbegin() :
                                   size == 8 ? PERMUTATION_8.cbegin() : PERMUTATION_10.cbegin());
        return false;
    }
};
