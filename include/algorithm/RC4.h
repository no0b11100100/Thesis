#pragma once

#include <QString>
#include <QDebug>
#include <vector>
#include <array>

#include "../common/utils.h"
#include "../common/consts.h"

namespace Algorithm
{

struct RC4
{
private:

    using Byte = QChar;
    using SType = std::array<Byte, 256>;
    using KeyType = std::vector<Byte>;

    static const SType makeS();

    static void Swap(Byte* a, Byte* b);

    static void KSA(SType& S, const QString& key);

    static Byte PRGA(SType& S);

    static Description::Description m_description;

public:
    static ReturnType encode(const QString&, const QString&);
};

} // namespace Algorithm
