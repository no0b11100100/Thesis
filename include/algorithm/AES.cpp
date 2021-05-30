#include "AES.h"

using namespace Algorithm;

void AES::SubBytes()
{
    static auto sBox = initSBox();
    for(int i {0}; i < m_matrix.rows(); ++i)
        for(int j{0}; j < m_matrix.columns(); ++j)
            qDebug() << "SBOX" << sBox.at(m_matrix.at({i,j}));
}

Matrix4X4 AES::KeyExpanded(const QString& key, const int& round)
{
    Matrix4X4 expandedKey(key);
    auto shifted = expandedKey.GetColumn(3);
    shifted.shiftUp();
    static auto sBox = initSBox();

    for(auto& v : shifted)
        v = sBox.at(v);

    auto column = expandedKey.GetColumn(0) ^ shifted ^ rcon.at(round);
    Matrix4X4 generatedKey;
    generatedKey.ChangeColumn(column, 0);

    for(int i{1}; i < expandedKey.columns(); ++i)
        generatedKey.ChangeColumn(generatedKey.GetColumn(i-1) ^ expandedKey.GetColumn(i), i);


    generatedKey.Print();
    qDebug() << "";

    return generatedKey;
}

Matrix4X4 AES::KeyExpanded(const Matrix4X4& key, const int& round)
{
    Matrix4X4 expandedKey = key;
    auto shifted = expandedKey.GetColumn(3);
    shifted.shiftUp();
    static auto sBox = initSBox();

    for(auto& v : shifted)
        v = sBox.at(v);

    auto column = expandedKey.GetColumn(0) ^ shifted ^ rcon.at(round);
    Matrix4X4 generatedKey;
    generatedKey.ChangeColumn(column, 0);

    for(int i{1}; i < expandedKey.columns(); ++i)
        generatedKey.ChangeColumn(generatedKey.GetColumn(i-1) ^ expandedKey.GetColumn(i), i);


    generatedKey.Print();
    qDebug() << "";

    return generatedKey;
}


void AES::ShiftRows()
{
    int i = 0;
    for(auto& row : m_matrix)
    {
        row.shift(i);
        ++i;
    }
}

void AES::MixColumns()
{
    Matrix4X4 state({
            {2,3,1,1},
            {1,2,3,1},
            {1,1,2,3},
            {3,1,1,2},
        });

//    m_matrix = {
//        {135,242,77,151},
//        {110,76,144,236},
//        {70,231,74,195},
//        {166,140,216,149},
//    };

    for(int i{0}; i < m_matrix.rows(); ++i)
    {
        int j = 0;
        for(const auto& row : state)
        {
            auto mult = row * m_matrix.GetColumn(i);
            auto tmp = mult.at(0);
            for(auto it = std::next(mult.cbegin()); it != mult.cend(); ++it)
                tmp ^= *it;

            m_matrix.ChangeAt(tmp, {i,j});
            ++j;
        }
    }
}

void AES::AddRoundKey(const Matrix4X4& key)
{
    m_matrix = m_matrix*key;
}

void AES::EvenRound(const Matrix4X4 &key)
{
    SubBytes();
    ShiftRows();
    AddRoundKey(key);
}

void AES::OddRound(const Matrix4X4 &key)
{
    SubBytes();
    ShiftRows();
    MixColumns();
    AddRoundKey(key);
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
    QString result = "";

    auto keyState = Matrix4X4("TEAMSCORPIAN1234");
    keyState.Print();
    qDebug() << "";

    for(int i{0}; i < rounds; ++i)
        keyState = KeyExpanded(keyState, i);


//    Matrix4X4 _key;
//    AddRoundKey(_key);

//    for(int i{0}; i < rounds; ++i)
//        i&1 ? OddRound(_key) : EvenRound(_key);

    return {result, m_description};
}

Description::Description AES::m_description = Description::Description();
Matrix4X4 AES::m_matrix = Matrix4X4();
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
