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
    static Description::Description m_description;
    static constexpr int rounds{10};
    static std::array<Matrix4X4::Line, rounds> rcon; // 6C, D8, AB, 4D, 9A, 2F, 5E, BC, 63, C6, 97, 35, 6A, D4, B3, 7D, FA, EF and C5

    static void SubBytes(Matrix4X4&);
    static Matrix4X4 KeyExpanded(const Matrix4X4&, const int&);
    static void ShiftRows(Matrix4X4&);
    static void MixColumns(Matrix4X4&);
    static void AddRoundKey(Matrix4X4&, const Matrix4X4&);
    static void Round(Matrix4X4&, const Matrix4X4&);
    static void FinalRound(Matrix4X4&, const Matrix4X4&);

    static std::array<uint8_t, 256> initSBox();

public:
    static ReturnType encode(const QString&, const QString&);

    static bool validate(const QString&, const QString&);
};

} // namespace Algorithm
