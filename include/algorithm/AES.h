#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>
#include <array>

#include "../common/consts.h"
#include "../common/utils.h"

#include "../Description.h"
#include "Matrix.h"

namespace Algorithm
{

class AES
{
    // https://ru.bmstu.wiki/AES_(Advanced_Encryption_Standard)
    // https://www.youtube.com/watch?v=X8whYEWoDSI
    static Matrix4X4 m_matrix;
    static Description::Description m_description;
    static constexpr int rounds{10};
    static std::array<Matrix4X4::Line, rounds> rcon; // 6C, D8, AB, 4D, 9A, 2F, 5E, BC, 63, C6, 97, 35, 6A, D4, B3, 7D, FA, EF and C5

    static void SubBytes();
    static Matrix4X4 KeyExpanded(const QString&, const int&);
    static Matrix4X4 KeyExpanded(const Matrix4X4&, const int&);
    static void ShiftRows();
    static void MixColumns();
    static void AddRoundKey(const Matrix4X4&);
    static void EvenRound(const Matrix4X4&);
    static void OddRound(const Matrix4X4&);

//    static QString KeyGeneration(const QString& )
//    {
//        QString result;

//        for(const auto& letter : key)
//            result += QString::number(letter.cell(), 16);

//        return result;
//    }

    static std::array<uint8_t, 256> initSBox();

public:
    static ReturnType encode(const QString&, const QString&);
};

} // namespace Algorithm
