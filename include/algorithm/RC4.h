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

    static const SType makeS()
    {
        SType S;
        for(int i{0}; i < 256; ++i)
            S[i] = (Byte)i;
        return S;
    }

    static void Swap(Byte* a, Byte* b)
    {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }

    static void KSA(SType& S, const KeyType& key)
    {
        int j = 0;
        const size_t keyLength = key.size();
        for(int i{0}; i < 256; ++i)
        {
            j = (j + S[i] + key.at(i%keyLength)) % 256;
            Swap(&S[i], &S[j]);
        }
    }

    static Byte PRGA(SType& S)
    {
        static int i = 0, j = 0;
        i = (i+1)%256;
        j = (j + S[i]) % 256;
        Swap(&S[i], &S[j]);
        int t = (S[i] + S[j]) % 256;
        return S[t];
    }

public:
    static QString encode(const QString& text, const QString&)
    {
        KeyType plainText = {'H', 'E', 'L', 'L', 'O', 'W', 'O', 'R', 'L', 'D'};
        KeyType key = {1,2,3,4,5,6,7,8};

        auto S = makeS();
        KSA(S, key);
        KeyType result;
        for(int i{0}; i < plainText.size(); ++i)
        {
            auto pt = plainText.at(i);
            auto prga = PRGA(S);
            qDebug() << pt << QString::number(pt, 16) << prga <<  QString::number(prga, 16);
            result.push_back(pt^prga);
        }

        for(auto v : result)
            qDebug() << v << QString::number(v, 16);

        return QString();
    }

};

} // namespace Algorithm
