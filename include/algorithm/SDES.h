#pragma once
#include <QString>
#include <array>
#include <unordered_map>

#include "../common/utils.h"
#include "../common/consts.h"

namespace Algorithm
{

class SDES
{
    template <size_t N>
    using permutationType = std::array<short, N>;

    template<size_t N>
    static void makePermautation(QString& key, const permutationType<N>& permutation);

    static std::tuple<QString, QString> divideIntoTwoParts(const QString& str);

    static std::tuple<QString, QString> generateKey(const QString& key, const permutationType<10>& permutation);

    static void P_blockCompression(QString& key, const permutationType<8>& P_block);

    static QString keyRound1(const QString& leftPart, const QString& rightPart,
                             const permutationType<8>& P_block);

    static QString keyRound2(const QString& leftPart, const QString& rightPart,
                             const permutationType<8>& P_block);

    static QString textPermutation(const QString& text, const permutationType<8>& permutation);

    static void ExpandText(QString& text, const permutationType<8>& expandTable);

    static QString XOR(const QString& lhs, const QString& rhs);

    static QString prepareDataForSBox(const QString& text);

    static QString SBox1 (const QString& text);

    static QString SBox2 (const QString& text);

    static void SPermutation(QString& text, const permutationType<4>& permutation);

    static QString Round(const QString& text, const QString& key, const int& round,
                         const permutationType<8>& expanded, const permutationType<4>& sbox);

    static Description::Description m_description;

    static constexpr int ROUNDS = 2;

    static constexpr permutationType<8> IP = {2,6,3,1,4,8,5,7};
    static constexpr permutationType<8> EXPANDED = {4,1,2,3,2,3,4,1};
    static constexpr permutationType<4> SBOX_PERMUTATION = {2,4,3,1};
    static constexpr permutationType<8> IP_1 = {4,1,3,5,7,2,8,6};


    /*key permutations*/
    static constexpr permutationType<10> P_10 = {3,5,2,7,4,10,1,9,8,6};
    static constexpr permutationType<8> P_8 = {6,3,7,4,8,5,10,9};

    template<size_t N>
    static std::array<short int, N> toArray(const QString& data)
    {
        auto list = data.split(QString(","));
        std::array<short, N> result;
        int i = 0;
        for(const auto& value : list)
        {
            result[i] = value.toInt();
            ++i;
        }
        return result;
    }

public:
    static ReturnType encode(const QVector<QStringList>&, const TextType&);
};

} // namespace Algorithm

