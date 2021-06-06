#include "SDES.h"

using namespace Algorithm;

template <size_t N>
using permutationType = std::array<short, N>;

template<size_t N>
void SDES::makePermautation(QString& key, const permutationType<N>& permutation)
{
    QString temp;
    for(const auto& index : permutation)
    {
        temp += key[index-1];
    }

    key = std::move(temp);
}

std::tuple<QString, QString> SDES::divideIntoTwoParts(const QString& str)
{
    const int middle = str.size() / 2;
    return {str.mid(0, middle), str.mid(middle, str.size()-1)};
}

std::tuple<QString, QString> SDES::generateKey(const QString& key, const permutationType<10>& permutation)
{
    QString expandedKey = key;
    makePermautation<10>(expandedKey, permutation);
    return divideIntoTwoParts(expandedKey);
}

void SDES::P_blockCompression(QString& key, const permutationType<8>& P_block)
{
    //        qDebug() << "key" << key;
    makePermautation<8>(key, P_block);
}

QString SDES::keyRound1(const QString& leftPart, const QString& rightPart,
                        const permutationType<8>& P_block)
{
    QString tempKey = Utils::cycleShift(leftPart, Utils::ShiftDirection::Left)+
            Utils::cycleShift(rightPart, Utils::ShiftDirection::Right);
    P_blockCompression(tempKey, P_block);
    return tempKey;
}

QString SDES::keyRound2(const QString& leftPart, const QString& rightPart,
                        const permutationType<8>& P_block)
{
    QString tempKey = Utils::cycleShift(leftPart, Utils::ShiftDirection::Left, 2)+
            Utils::cycleShift(rightPart, Utils::ShiftDirection::Right, 2);
    //        qDebug() << "tempKey" << tempKey;
    P_blockCompression(tempKey, P_block);
    return tempKey;
}

QString SDES::textPermutation(const QString& text, const permutationType<8>& permutation)
{
    QString temp = text;
    makePermautation<8>(temp, permutation);
    return temp;
}

void SDES::ExpandText(QString& text, const permutationType<8>& expandTable)
{
    makePermautation<8>(text, expandTable);
}

QString SDES::XOR(const QString& lhs, const QString& rhs)
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

QString SDES::prepareDataForSBox(const QString& text)
{
    assert(text.size() == 4);

    QString key = text;
    key.front() = text.front();
    key[1] = text.back();
    key[2] = text[1];
    key[3] = text[2];

    return key;
}

QString SDES::SBox1 (const QString& text)
{
    auto key = prepareDataForSBox(text);
    qDebug() << "S1 box" << key;
    static std::unordered_map<QString, QString> table{
        {"0000", "01"},
        {"0001", "00"},
        {"0010", "11"},
        {"0011", "10"},

        {"0100", "11"},
        {"0101", "10"},
        {"0110", "01"},
        {"0111", "00"},

        {"1000", "00"},
        {"1001", "10"},
        {"1010", "01"},
        {"1011", "11"},

        {"1100", "11"},
        {"1101", "01"},
        {"1110", "11"},
        {"1111", "10"},
    };

    return table.at(key);
}

QString SDES::SBox2 (const QString& text)
{
    auto key = prepareDataForSBox(text);
    qDebug() << "S2 box" << key;
    static std::unordered_map<QString, QString> table{
        {"0000", "00"},
        {"0001", "01"},
        {"0010", "10"},
        {"0011", "11"},

        {"0100", "10"},
        {"0101", "00"},
        {"0110", "01"},
        {"0111", "11"},

        {"1000", "11"},
        {"1001", "00"},
        {"1010", "01"},
        {"1011", "00"},

        {"1100", "10"},
        {"1101", "01"},
        {"1110", "00"},
        {"1111", "11"},
    };

    return table.at(key);
}

void SDES::SPermutation(QString& text, const permutationType<4>& permutation)
{
    makePermautation<4>(text, permutation);
}

QString SDES::Round(const QString& text, const QString& key, const int& round,
                    const permutationType<8>& expanded, const permutationType<4>& sbox)
{
    assert(round == 0 || round == 1);
    auto [L, R] = divideIntoTwoParts(text);
    QString resPart = R;
    qDebug() << "R" << R;
    ExpandText(R, expanded);
    qDebug() << "expanded text" << R;
    auto xorRes = XOR(R,key);
    qDebug() << "key" << key << "XOR with key" << xorRes;

    auto [s1Part, s2Part] = divideIntoTwoParts(xorRes);
    QString sBoxesResult = SBox1(s1Part) + SBox2(s2Part);
    qDebug() << "s box result" << sBoxesResult;
    SPermutation(sBoxesResult, sbox);

    QString result = ( XOR(sBoxesResult, L) );
    qDebug() << "XOR" << result;
    return round == 0 ? resPart + result : result + resPart;
}

ReturnType SDES::encode(const QVector<QStringList>& tables, const TextType& pack)
{
    qDebug() << "SDES" << tables;
    constexpr int P_10Index = 6;
    constexpr int P_8Index = 7;
    constexpr int IPIndex = 2;
    constexpr int EXPANDEDIndex = 3;
    constexpr int SBOX_PERMUTATIONIndex = 4;
    constexpr int IP_1Index = 5;
    constexpr int TEXTIndex = 0;
    constexpr int KEYIndex = 1;
    qDebug() << pack.at(KEYIndex);
    auto [a,b] = generateKey(pack.at(KEYIndex).at(1), SDES::toArray<10>(pack.at(P_10Index).at(1)));
    qDebug() << a << b;
    QString round1Key = keyRound1(a,b, SDES::toArray<8>(pack.at(P_8Index).at(1)));
    qDebug() << "key1" << round1Key;
    QString round2Key = keyRound2(a,b, SDES::toArray<8>(pack.at(P_8Index).at(1)));
    qDebug() << "key2" << round2Key;
    QString textPermut = textPermutation(pack.at(TEXTIndex).at(1), SDES::toArray<8>(pack.at(IPIndex).at(1)));
    qDebug() << "IP" << textPermut;
    QString encode = textPermut;
    for(int i{0}; i < ROUNDS; ++i)
    {
        qDebug() << "round text" << encode;
        encode = Round(encode, i == 0 ? round1Key : round2Key, i, SDES::toArray<8>(pack.at(EXPANDEDIndex).at(1)),
                       SDES::toArray<4>(pack.at(SBOX_PERMUTATIONIndex).at(1)));
        qDebug() << "round result" << encode << "\n\n";
    }
    QString result = textPermutation(encode, SDES::toArray<8>(pack.at(IP_1Index).at(1)));
    qDebug() << "encode text" << result;
    return {"", m_description};
}

Description::Description SDES::m_description = Description::Description();
