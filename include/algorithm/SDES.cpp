#include "SDES.h"

//namespace Algorithm
//{

//class SDES
//{
//    template <size_t N>
//    using permutationType = std::array<short, N>;

//    template<size_t N>
//    static void makePermautation(QString& key, const permutationType<N>& permutation)
//    {
//        QString temp;
//        for(const auto& index : permutation)
//        {
//            temp += key[index-1];
//        }

//        key = std::move(temp);
//    }

//    static std::tuple<QString, QString> divideIntoTwoParts(const QString& str)
//    {
//        const int middle = str.size() / 2;
//        return {str.mid(0, middle), str.mid(middle, str.size()-1)};
//    }

//    static std::tuple<QString, QString> generateKey(const QString& key, const permutationType<10>& permutation)
//    {
//        QString expandedKey = key;
//        makePermautation<10>(expandedKey, permutation);
//        return divideIntoTwoParts(expandedKey);
//    }

//    static void P_blockCompression(QString& key, const permutationType<8>& P_block)
//    {
////        qDebug() << "key" << key;
//        makePermautation<8>(key, P_block);
//    }

//    static QString keyRound1(const QString& leftPart, const QString& rightPart,
//                             const permutationType<8>& P_block)
//    {
//        QString tempKey = Utils::cycleShift(leftPart, Utils::ShiftDirection::Left)+
//                          Utils::cycleShift(rightPart, Utils::ShiftDirection::Right);
//        P_blockCompression(tempKey, P_block);
//        return tempKey;
//    }

//    static QString keyRound2(const QString& leftPart, const QString& rightPart,
//                             const permutationType<8>& P_block)
//    {
//        QString tempKey = Utils::cycleShift(leftPart, Utils::ShiftDirection::Left, 2)+
//                          Utils::cycleShift(rightPart, Utils::ShiftDirection::Right, 2);
////        qDebug() << "tempKey" << tempKey;
//        P_blockCompression(tempKey, P_block);
//        return tempKey;
//    }

//    static QString textPermutation(const QString& text, const permutationType<8>& permutation)
//    {
//        QString temp = text;
//        makePermautation<8>(temp, permutation);
//        return temp;
//    }

//    static void ExpandText(QString& text, const permutationType<8>& expandTable)
//    {
//        makePermautation<8>(text, expandTable);
//    }

//    static QString XOR(const QString& lhs, const QString& rhs)
//    {
//        assert(lhs.size() == rhs.size());

//        QString result;
//        std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), std::back_inserter(result), [](const QChar& lhs, const QChar& rhs)
//        {
//            if(lhs == rhs) return QChar('0');
//            return QChar('1');
//        });

//        return result;
//    }

//    static QString prepareDataForSBox(const QString& text)
//    {
//        assert(text.size() == 4);

//        QString key = text;
//        key.front() = text.front();
//        key[1] = text.back();
//        key[2] = text[1];
//        key[3] = text[2];

//        return key;
//    }

//    static QString SBox1 (const QString& text)
//    {
//        auto key = prepareDataForSBox(text);
//        qDebug() << "S1 box" << key;
//        static std::unordered_map<QString, QString> table{
//            {"0000", "01"},
//            {"0001", "00"},
//            {"0010", "11"},
//            {"0011", "10"},

//            {"0100", "11"},
//            {"0101", "10"},
//            {"0110", "01"},
//            {"0111", "00"},

//            {"1000", "00"},
//            {"1001", "10"},
//            {"1010", "01"},
//            {"1011", "11"},

//            {"1100", "11"},
//            {"1101", "01"},
//            {"1110", "11"},
//            {"1111", "10"},
//        };

//        return table.at(key);
//    }

//    static QString SBox2 (const QString& text)
//    {
//        auto key = prepareDataForSBox(text);
//        qDebug() << "S2 box" << key;
//        static std::unordered_map<QString, QString> table{
//            {"0000", "00"},
//            {"0001", "01"},
//            {"0010", "10"},
//            {"0011", "11"},

//            {"0100", "10"},
//            {"0101", "00"},
//            {"0110", "01"},
//            {"0111", "11"},

//            {"1000", "11"},
//            {"1001", "00"},
//            {"1010", "01"},
//            {"1011", "00"},

//            {"1100", "10"},
//            {"1101", "01"},
//            {"1110", "00"},
//            {"1111", "11"},
//        };

//        return table.at(key);
//    }

//    static void SPermutation(QString& text, const permutationType<4>& permutation)
//    {
//        makePermautation<4>(text, permutation);
//    }

//    static QString Round(const QString& text, const QString& key, const int& round)
//    {
//        assert(round == 0 || round == 1);
//        auto [L, R] = divideIntoTwoParts(text);
//        QString resPart = R;
//        qDebug() << "R" << R;
//        ExpandText(R, EXPANDED);
//        qDebug() << "expanded text" << R;
//        auto xorRes = XOR(R,key);
//        qDebug() << "key" << key << "XOR with key" << xorRes;

//        auto [s1Part, s2Part] = divideIntoTwoParts(xorRes);
//        QString sBoxesResult = SBox1(s1Part) + SBox2(s2Part);
//        qDebug() << "s box result" << sBoxesResult;
//        SPermutation(sBoxesResult, SBOX_PERMUTATION);

//        QString result = ( XOR(sBoxesResult, L) );
//        qDebug() << "XOR" << result;
//        return round == 0 ? resPart + result : result + resPart;
//    }

//    static constexpr int ROUNDS = 2;

//    static constexpr permutationType<8> IP = {2,6,3,1,4,8,5,7};
//    static constexpr permutationType<8> EXPANDED = {4,1,2,3,2,3,4,1};
//    static constexpr permutationType<4> SBOX_PERMUTATION = {2,4,3,1};
//    static constexpr permutationType<8> IP_1 = {4,1,3,5,7,2,8,6};


//    /*key permutations*/
//    static constexpr permutationType<10> P_10 = {3,5,2,7,4,10,1,9,8,6};
//    static constexpr permutationType<8> P_8 = {6,3,7,4,8,5,10,9};
//public:
//    static QString encode(const QString& text, const QString& key)
//    {
//        auto [a,b] = generateKey(key, P_10);
//        qDebug() << a << b;
//        QString round1Key = keyRound1(a,b, P_8);
//        qDebug() << "key1" << round1Key;
//        QString round2Key = keyRound2(a,b, P_8);
//        qDebug() << "key2" << round2Key;
//        QString textPermut = textPermutation(text, IP);
//        qDebug() << "IP" << textPermut;
//        QString encode = textPermut;
//        for(int i{0}; i < ROUNDS; ++i)
//        {
//            qDebug() << "round text" << encode;
//            encode = Round(encode, i == 0 ? round1Key : round2Key, i);
//            qDebug() << "round result" << encode << "\n\n";
//        }
//        QString result = textPermutation(encode, IP_1);
//        qDebug() << "encode text" << result;
//        return result;
//    }
//};

//} // namespace Algorithm

