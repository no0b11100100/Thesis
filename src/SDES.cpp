#include "../include/algorithm/SDES.h"

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
    makePermautation<8>(key, P_block);
}

template<size_t N>
QString toStr(const permutationType<N>& data)
{
    QString res = "";

    for(const auto& v : data)
        res += QString::number(v) + ",";

    return res.mid(0, res.size()-1);
}

QString SDES::keyRound1(const QString& leftPart, const QString& rightPart,
                        const permutationType<8>& P_block)
{
    m_description.GetContentDetails() += TAB + "Для формування ключа для першого раунду спочатку необхідно зробити зсув лівої частини на 1 біт вліво: " + Utils::cycleShift(leftPart, Utils::ShiftDirection::Left)
                                      + ", а правою на 1 біт вправо: " + Utils::cycleShift(rightPart, Utils::ShiftDirection::Right) + "\n";
    QString tempKey = Utils::cycleShift(leftPart, Utils::ShiftDirection::Left)+
            Utils::cycleShift(rightPart, Utils::ShiftDirection::Right);
    m_description.GetContentDetails() += TAB +  "Після цього необхідно обрати 8 біт із 10 за заданою таблицею: " + toStr(P_block) + " та отримуємо ключ для першого раунду: ";
    P_blockCompression(tempKey, P_block);
    m_description.GetContentDetails() += tempKey + "\n";
    return tempKey;
}

QString SDES::keyRound2(const QString& leftPart, const QString& rightPart,
                        const permutationType<8>& P_block)
{
    m_description.GetContentDetails() += TAB + "Для формування ключа для першого раунду спочатку необхідно зробити зсув лівої частини на 2 біт вліво: " + Utils::cycleShift(leftPart, Utils::ShiftDirection::Left, 2)
                                      + ", а правою на 2 біт вправо: " + Utils::cycleShift(rightPart, Utils::ShiftDirection::Right, 2) + "\n";
    QString tempKey = Utils::cycleShift(leftPart, Utils::ShiftDirection::Left, 2)+
            Utils::cycleShift(rightPart, Utils::ShiftDirection::Right, 2);

    m_description.GetContentDetails() += TAB +  "Після цього необхідно обрати 8 біт із 10 за заданою таблицею: " + toStr(P_block) + " та отримуємо ключ для другого раунду: ";
    P_blockCompression(tempKey, P_block);
    m_description.GetContentDetails() += tempKey + "\n";
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

void SDES::SPermutation(QString& text, const permutationType<4>& permutation)
{
    makePermautation<4>(text, permutation);
}

QString SDES::Round(const QString& text, const QString& key, const int& round,
                    const permutationType<8>& expanded, const permutationType<4>& sbox,
                    const std::unordered_map<QString, QString>& sBox1, const std::unordered_map<QString, QString>& sBox2)
{

    assert(round == 0 || round == 1);
    m_description.GetContentDetails() += DOUBLE_TAB + "Вхідний текст для раунду: " + text + "\n"
            + DOUBLE_TAB + "Розіб'ємо текст на дві частини: ";
    auto [L, R] = divideIntoTwoParts(text);
    m_description.GetContentDetails() += L + " " + R;
    QString resPart = R;
    ExpandText(R, expanded);
    m_description.GetContentDetails() += "\n" + DOUBLE_TAB + "Зробимо розширення правої частини до 8 біт за таблицею: " + toStr(expanded) + ": " + R + "\n";
    m_description.GetContentDetails() += DOUBLE_TAB + "Після цього необхідно зробити XOR між розширеною правою частиною та ключем: " +
                                    R + " XOR " + key + " = ";
    auto xorRes = XOR(R,key);
    m_description.GetContentDetails() += xorRes + "\n";
    auto [s1Part, s2Part] = divideIntoTwoParts(xorRes);

    m_description.GetContentDetails() += DOUBLE_TAB + "Далі розбиваємо отриманний результат на дві частини: " + s1Part + " " + s2Part + "\n";

    QString sBoxesResult = sBox1.at(prepareDataForSBox(s1Part)) + sBox2.at(prepareDataForSBox(s2Part));
    m_description.GetContentDetails() += DOUBLE_TAB + "та обираючи значення із SBOX таблиць отримуємо: " +
            sBox1.at(prepareDataForSBox(s1Part)) + " " + sBox2.at(prepareDataForSBox(s2Part)) + "\n";
    SPermutation(sBoxesResult, sbox);
    m_description.GetContentDetails() += DOUBLE_TAB + "об'єднуємо отримані значення і робимо перестановку за таблицею: " + toStr(sbox)+ "\n";
    m_description.GetContentDetails() += DOUBLE_TAB + "Отримуємо " + sBoxesResult + "\n";
    QString result = ( XOR(sBoxesResult, L) );
    m_description.GetContentDetails() += DOUBLE_TAB + "У кінці раунду робимо XOR між отриманими даними та лівою частиною: " + sBoxesResult + "\n";
            m_description.GetContentDetails() += DOUBLE_TAB + "та поєднуємо " + (round == 0 ? "ліву частину із отриманими даними: " + resPart + result
                                                                                            : "отримані дані із лівою: " + result + resPart);
    return round == 0 ? resPart + result : result + resPart;
}

ReturnType SDES::encode(const QVector<QStringList>& tables, const TextType& pack)
{
    constexpr int P_10Index = 6;
    constexpr int P_8Index = 7;
    constexpr int IPIndex = 2;
    constexpr int EXPANDEDIndex = 3;
    constexpr int SBOX_PERMUTATIONIndex = 4;
    constexpr int IP_1Index = 5;
    constexpr int TEXTIndex = 0;
    constexpr int KEYIndex = 1;
    m_description.AddHeader(KEY_GENERATION);
    m_description.GetContentDetails() += TAB + "Зробимо перестановку для ключа: " + pack.at(P_10Index).at(1) + "\n"
            + TAB + "Після перестановки отримуємо: ";
    auto [a,b] = generateKey(pack.at(KEYIndex).at(1), SDES::toArray<10>(pack.at(P_10Index).at(1)));
    m_description.GetContentDetails() += a+b + " та розбиваємо на 2 чистини: " + a + " " + b + "\n";
    QString round1Key = keyRound1(a,b, SDES::toArray<8>(pack.at(P_8Index).at(1)));

    QString round2Key = keyRound2(a,b, SDES::toArray<8>(pack.at(P_8Index).at(1)));
    m_description.AddContent();
    m_description.AddHeader(ENCODING);

    m_description.GetContentDetails() += TAB + "Зробимо перестановку для тексту за таблицею: " + pack.at(IPIndex).at(1) + ". Отримуємо: ";
    QString textPermut = textPermutation(pack.at(TEXTIndex).at(1), SDES::toArray<8>(pack.at(IPIndex).at(1)));
    m_description.GetContentDetails() += textPermut + "\n";
    QString encode = textPermut;
            auto s1 = toMap(tables.at(0));
            auto s2 = toMap(tables.at(1));
    for(int i{0}; i < ROUNDS; ++i)
    {
        m_description.GetContentDetails() += TAB + "Раунд " + QString::number(i+1) + "\n";
        encode = Round(encode, i == 0 ? round1Key : round2Key, i, SDES::toArray<8>(pack.at(EXPANDEDIndex).at(1)),
                       SDES::toArray<4>(pack.at(SBOX_PERMUTATIONIndex).at(1)),
                       s1, s2);
        m_description.GetContentDetails() += "\n" + TAB + "Pезультат раунду " + QString::number(i+1) + ": " + encode + "\n";
    }
    QString result = textPermutation(encode, SDES::toArray<8>(pack.at(IP_1Index).at(1)));
    m_description.GetContentDetails() += TAB + "Для завершення роботи алгоритму необхідно зробити перестановку: " + pack.at(IP_1Index).at(1) + "\n" +
                                      TAB + "В результаті отримуємo " + result;
    m_description.AddContent();
    return {result, m_description};
}

bool SDES::validate(const QVector<QStringList> & tables, const TextType & pack)
{
        constexpr int P_10Index = 6;
        constexpr int P_8Index = 7;
        constexpr int IPIndex = 2;
        constexpr int EXPANDEDIndex = 3;
        constexpr int SBOX_PERMUTATIONIndex = 4;
        constexpr int IP_1Index = 5;
        constexpr int TEXTIndex = 0;
        constexpr int KEYIndex = 1;
    auto validateTable = [](const QStringList& list)
    {
        const int min = 0;
        const int max = 3;
        qDebug() << "validate" << list;
        for(const auto& v : list)
        {
            if(v.size() != 1) return false;
            bool isNumber;
            int iValue = v.toInt(&isNumber);

            if(!isNumber || (iValue < min || iValue > max)) return false;
        }

        qDebug() << "validate" << !list.isEmpty();
        return !list.isEmpty();
    };

    if(tables.isEmpty() || tables.size() != 2) return false;
    if(tables.at(0).isEmpty() || tables.at(1).isEmpty() ||
            !validateTable(tables.at(0)) || !validateTable(tables.at(1)))
        return false;

    return Utils::validateString(pack.at(TEXTIndex).at(1), "01") && Utils::validateString(pack.at(KEYIndex).at(1), "01") &&
            Utils::validateSequence(pack.at(SBOX_PERMUTATIONIndex).at(1).split(QChar(','))) && Utils::validateSequence(pack.at(P_10Index).at(1).split(QChar(','))) &&
            Utils::validateSequence(pack.at(P_8Index).at(1).split(QChar(','))) && Utils::validateSequence(pack.at(IPIndex).at(1).split(QChar(','))) &&
            Utils::validateSequence(pack.at(EXPANDEDIndex).at(1).split(QChar(','))) && Utils::validateSequence(pack.at(IP_1Index).at(1).split(QChar(',')));
}

Description::Description SDES::m_description = Description::Description();
