#pragma once
#include <QString>
#include <array>
#include "utils.h"
#include <unordered_map>

// https://www.geeksforgeeks.org/data-encryption-standard-des-set-1/
// https://github.com/MLuchette/SDES/blob/master/SDES.cpp
namespace Algorithm
{

class SDES
{
    template <size_t N>
    using permutationType = std::array<short, N>;

    template<size_t N>
    static void makePermautation(QString& key, const permutationType<N>& permutation)
    {
        QString temp;
        for(const auto& index : permutation)
        {
            temp += key[index-1];
        }

        key = std::move(temp);
    }

    static std::tuple<QString, QString> divideIntoTwoParts(const QString& str)
    {
        const int middle = str.size() / 2;
        return {str.mid(0, middle), str.mid(middle, str.size()-1)};
    }

    static std::tuple<QString, QString> generateKey(const QString& key, const permutationType<10>& permutation)
    {
        QString expandedKey = '1' + key + '1';
        makePermautation<10>(expandedKey, permutation);
        return {expandedKey.mid(0,5), expandedKey.mid(5,10)};
    }

    static void P_blockCompression(QString& key, const permutationType<8>& P_block)
    {
//        qDebug() << "key" << key;
        makePermautation<8>(key, P_block);
    }

    static QString keyRound1(const QString& leftPart, const QString& rightPart,
                             const permutationType<8>& P_block)
    {
        QString tempKey = Utils::cycleShift(leftPart, Utils::ShiftDirection::Left)+
                          Utils::cycleShift(rightPart, Utils::ShiftDirection::Right);
        P_blockCompression(tempKey, P_block);
        return tempKey;
    }

    static QString keyRound2(const QString& leftPart, const QString& rightPart,
                             const permutationType<8>& P_block)
    {
        QString tempKey = Utils::cycleShift(leftPart, Utils::ShiftDirection::Left, 2)+
                          Utils::cycleShift(rightPart, Utils::ShiftDirection::Right, 2);
//        qDebug() << "tempKey" << tempKey;
        P_blockCompression(tempKey, P_block);
        return tempKey;
    }

    static QString textPermutation(const QString& text, const permutationType<8>& permutation)
    {
        QString temp = text;
        makePermautation<8>(temp, permutation);
        return temp;
    }

    static void ExpandText(QString& text, const permutationType<8>& expandTable)
    {
        qDebug() << "Expanded" <<text;
        makePermautation<8>(text, expandTable);
    }

    static QString XOR(const QString& lhs, const QString& rhs)
    {
        assert(lhs.size() == rhs.size());

        QString result;

        std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), std::back_inserter(result), [](const QChar& lhs, const QChar& rhs)
        {
            if(lhs == rhs) return QChar('0');
            return QChar('1');
        });

        return result;
    }

    static QString SBox1 (const QString& text)
    {
        qDebug() << "S1" << text;
        static std::unordered_map<QString, QString> table{
            {"0000", "11"},
            {"0001", "11"},
            {"0010", "11"},
            {"0011", "11"},
            {"0100", "11"},
            {"0101", "11"},
            {"0110", "11"},
            {"0111", "11"},
            {"1000", "11"},
            {"1001", "11"},
            {"1010", "11"},
            {"1011", "11"},
            {"1100", "11"},
            {"1101", "11"},
            {"1110", "11"},
            {"1111", "11"},
        };

        return table.at(text);
    }

    static QString SBox2 (const QString& text)
    {
        qDebug() << "S2" << text;
        static std::unordered_map<QString, QString> table{
            {"0000", "11"},
            {"0001", "11"},
            {"0010", "11"},
            {"0011", "11"},
            {"0100", "11"},
            {"0101", "11"},
            {"0110", "11"},
            {"0111", "11"},
            {"1000", "11"},
            {"1001", "11"},
            {"1010", "11"},
            {"1011", "11"},
            {"1100", "11"},
            {"1101", "11"},
            {"1110", "11"},
            {"1111", "11"},
        };

        return table.at(text);
    }

    static QString Round(const QString& text, const QString& key)
    {
        auto [L, R] = divideIntoTwoParts(text);

        ExpandText(R, permutationType<8>{1,2,3,4,4,3,2,1});
        qDebug() << "R" << R;
        auto xorRes = XOR(R,key);

        auto [s1Part, s2Part] = divideIntoTwoParts(xorRes);

        auto s1 = SBox1(s1Part);
        auto s2 = SBox2(s2Part);

        QString result = ( XOR((s1+s2), L) ) + L;
        std::tie(L, R) = divideIntoTwoParts(result);
        return R+L;
    }

    static constexpr int ROUNDS = 2;

public:
    static QString encode(const QString& text, const QString& key)
    {
        auto [a,b] = generateKey(key, permutationType<10> {3,5,2,7,4,10,1,9,8,6});
        qDebug() << a << b;
        QString round1Key = keyRound1(a,b, permutationType<8> {6,3,7,4,8,5,10,9});
        qDebug() << round1Key;
        QString round2Key = keyRound2(a,b, permutationType<8> {6,3,7,4,8,5,10,9});
        qDebug() << round2Key;
        QString textPermut = textPermutation(text, permutationType<8> {3,7,2,1,5,8,6,4});
        qDebug() << textPermut;
        QString encode = textPermut;
        for(int i{0}; i < ROUNDS; ++i)
        {
            encode = Round(textPermut, i == 0 ? round1Key : round2Key);
            qDebug() << encode;
        }
        QString result = textPermutation(encode, permutationType<8> {3,7,2,1,5,8,6,4});
        return "";
    }
};

} // namespace Algorithm

