#include "../include/algorithm/AES.h"

using namespace Algorithm;

void AES::SubBytes(Matrix4X4& matrix)
{
    m_description.GetContentDetails() += TAB + "SubBytes:\n";
    m_description.GetContentDetails() += DOUBLE_TAB + "Кожен біт замінюється на значення з таблиці S-BOX: ";
    static auto sBox = initSBox();
    for(int i {0}; i < matrix.rows(); ++i)
        for(int j{0}; j < matrix.columns(); ++j)
            matrix.ChangeAt(sBox.at(matrix.at({i,j})), {i,j});

    m_description.GetContentDetails() += matrix.toString() + "\n";
    qDebug() << "SubBytes";
    matrix.Print();
    qDebug() << "";
}

Matrix4X4 AES::KeyExpanded(const Matrix4X4& key, const int& round)
{
    m_description.GetContentDetails() += TAB + "Згенеруємо ключ для раунду " + QString::number(round+1) + ":\n";
    Matrix4X4 expandedKey = key;
//    qDebug() << "take last column";

//    expandedKey.GetColumn(3).Print();
    m_description.GetContentDetails() += DOUBLE_TAB + "Беремо останю колонку попреденього ключа: " + expandedKey.GetColumn(3).toString() + "\n";
    auto shifted = expandedKey.GetColumn(3);
    shifted.shiftUp();
    m_description.GetContentDetails() += DOUBLE_TAB + "та зсуваємо на одну позицію догори: " + shifted.toString() + "\n";
//    qDebug() << "shiftedUp";
//    shifted.Print();
    static auto sBox = initSBox();

    for(auto& v : shifted)
        v = sBox.at(v);

    m_description.GetContentDetails() += DOUBLE_TAB + "Після цього робимо заміну кожно біта(8 біт) із S-BOX таблиці: " + shifted.toString();
//    qDebug() << "sBox";
//    shifted.Print();

//    qDebug() << "rcon";
//    rcon.at(round).Print();
//    expandedKey.GetColumn(0).Print();
    auto column = expandedKey.GetColumn(0) ^ shifted ^ rcon.at(round);
    m_description.GetContentDetails() += " та робимо XOR між першою колонкою ключа зміненою останньою колонкою  із значенням із таблці RCON: " + column.toString() + " та стаимо ії у першу колонку нового ключа.\n";
//    qDebug() << "XOR";
//    column.Print();
    Matrix4X4 generatedKey;
    generatedKey.ChangeColumn(column, 0);
//    qDebug() << "Set in matrix";
//    generatedKey.GetColumn(0).Print();

    m_description.GetContentDetails() += TAB + "Для завершення формування ключа необхідно зробити XOR між колонками попреднього ключа та новосформованої колонки ключа: ";
    for(int i{1}; i < expandedKey.columns(); ++i)
        generatedKey.ChangeColumn(generatedKey.GetColumn(i-1) ^ expandedKey.GetColumn(i), i);

    m_description.GetContentDetails() += TAB + generatedKey.toString() + "\n";

    qDebug() << "key";
    generatedKey.PrintAsRow();
    qDebug() << "";

    return generatedKey;
}

void AES::ShiftRows(Matrix4X4& matrix)
{
    m_description.GetContentDetails() += TAB + "ShiftRows:\n";
    m_description.GetContentDetails() += DOUBLE_TAB + "Кожна строка зміщується на одну позицію вправо, окрім першої:";
    int i = 0;
    for(auto& row : matrix)
    {
        row.shift(i);
        ++i;
    }

    m_description.GetContentDetails() += matrix.toString() + "\n";
    qDebug() << "ShiftRows";
    matrix.Print();
    qDebug() << "";
}

void AES::MixColumns(Matrix4X4& matrix)
{
    Matrix4X4 state({
            {2,3,1,1},
            {1,2,3,1},
            {1,1,2,3},
            {3,1,1,2},
        });

    m_description.GetContentDetails() += TAB + "MixColumns:\n";
    m_description.GetContentDetails() += DOUBLE_TAB + "Кожен біт стовбеця тексту помножується із бітом із строкі state та робиться XOR :";

    for(int i{0}; i < matrix.rows(); ++i)
    {
        int j = 0;
        Matrix4X4::Line line;
        for(const auto& row : state)
        {
            auto mult = row * matrix.GetColumn(i);
            auto tmp = mult.at(0);
            for(auto it = std::next(mult.cbegin()); it != mult.cend(); ++it)
                tmp ^= *it;
            line.ChangeAt(j, tmp);
            ++j;
        }

        matrix.ChangeColumn(line, i);
    }

    m_description.GetContentDetails() += matrix.toString() + "\n";

    qDebug() << "MixColumns";
    matrix.Print();
    qDebug() << "";
}

void AES::AddRoundKey(Matrix4X4& matrix, const Matrix4X4& key)
{
    m_description.GetContentDetails() += TAB + "AddRoundKey:\n";
    m_description.GetContentDetails() += DOUBLE_TAB + "Робиться XOR тексту та ключа:";
    qDebug() << "AddRoundKey key";
    key.Print();
    qDebug() << "";
    matrix = matrix^key;
    qDebug() << "AddRoundKey";
    matrix.Print();
    qDebug() << "";
    m_description.GetContentDetails() += matrix.toString() + "\n";
}

void AES::FinalRound(Matrix4X4& matrix, const Matrix4X4 &key)
{
    m_description.GetContentDetails() += TAB + "Раунд 10:\n";
    SubBytes(matrix);
    ShiftRows(matrix);
    AddRoundKey(matrix, key);
}

void AES::Round(Matrix4X4& matrix, const Matrix4X4 &key)
{
    SubBytes(matrix);
    ShiftRows(matrix);
    MixColumns(matrix);
    AddRoundKey(matrix, key);
}

std::array<uint8_t, 256> AES::initSBox()
{
    std::array<uint8_t, 256> sBox;
    uint8_t p = 1, q = 1;

    auto ROTL8 = [](const uint8_t& x, const int& shift)
    {
        return (x << shift) | (x >> (8 - shift));
    };

    do {
        p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);

        q ^= q << 1;
        q ^= q << 2;
        q ^= q << 4;
        q ^= q & 0x80 ? 0x09 : 0;

        uint8_t xformed = q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);

        sBox[p] = xformed ^ 0x63;
    } while (p != 1);

    sBox[0] = 0x63;

    return sBox;
}

ReturnType AES::encode(const QString& text, const QString& key)
{
    m_description.AddHeader(ENCODING);
    auto keyState = Matrix4X4(key);
//    keyState.Print();
//    qDebug() << "";
    QString expanded = "";
    if(text.size() != 16)
        for(int i = 0; i < 16 - text.size(); ++i)
            expanded.push_back("0");

    auto textState = Matrix4X4(text + expanded);
//    textState.Print();
//    qDebug() << "";
    m_description.GetContentDetails() += TAB + "Initial round: робимо XOR тексту та ключа:\n" +
                                    TAB + textState.toString() + " XOR " +keyState.toString() + " = ";
    textState = keyState^textState;
//    textState.Print();
    m_description.GetContentDetails() += textState.toString() + "\n";

    for(int i{0}; i < rounds-1; ++i)
    {
        m_description.GetContentDetails() += TAB + "Раунд " + QString::number(i+1) + "\n";
//        qDebug() << "round" << i;
        keyState = KeyExpanded(keyState, i);
        Round(textState, keyState);
    }

    FinalRound(textState, KeyExpanded(keyState, 9));

//    textState.Print();
//    qDebug() << textState.toString();
    m_description.AddContent();
    return {textState.toString(), m_description};
}

bool AES::validate(const QString & text, const QString & key)
{
    if(key.size() != 16 || text.size() > 16) return false;
    auto tmpText = text;
    auto tmpKey = key;
    tmpText.remove(QChar(' '));
    tmpKey.remove(QChar(' '));
    return Utils::validateString(tmpText.simplified(), ENGLISH_ALPHABET) && Utils::validateString(tmpKey.simplified(), ENGLISH_ALPHABET);
}

Description::Description AES::m_description = Description::Description();
std::array<Matrix4X4::Line, 10> AES::rcon{
    Matrix4X4::Line({1,0,0,0}),
    Matrix4X4::Line({2,0,0,0}),
    Matrix4X4::Line({4,0,0,0}),
    Matrix4X4::Line({8,0,0,0}),
    Matrix4X4::Line({16,0,0,0}),
    Matrix4X4::Line({32,0,0,0}),
    Matrix4X4::Line({64,0,0,0}),
    Matrix4X4::Line({128,0,0,0}),
    Matrix4X4::Line({27,0,0,0}),
    Matrix4X4::Line({54,0,0,0}),
};
