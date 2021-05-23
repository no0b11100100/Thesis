#pragma once

#include <QString>
#include <QDebug>
#include <vector>
#include <array>

#include "../common/utils.h"

namespace Algorithm
{

struct RC4
{
private:

    using Byte = unsigned char;
    using SType = std::array<Byte, 256>;
    using KeyType = std::vector<Byte>;

    static const SType makeS();

    static void Swap(Byte* a, Byte* b);

    static void KSA(SType& S, const KeyType& key);

    static Byte PRGA(SType& S);

public:
    static QString encode(const QString& text, const QString&);
};

} // namespace Algorithm
