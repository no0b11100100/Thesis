#include "RSA.h"

using namespace Algorithm;

RSA::InputPrimeNumbers RSA::parseKey(const QString& key)
{
    auto values = key.split(' ');
    qDebug() << values.size();
    return {values[0].toInt(), values[1].toInt()};
}

int RSA::EulerFuntion(int P, int Q) { return (P-1)*(Q-1); }

int RSA::gcd(int u, int v)
{
    if (u == v) return u;
    if (u == 0) return v;
    if (v == 0) return u;

    if (!(u&1))
    {
        if (v&1) return gcd(u/2, v);
        else return 2 * gcd(u/2, v/2);
    }
    else
    {
        if (!(v&1)) return gcd(u, v/2);
        if (u > v) return gcd((u - v)/2, v);
        else return gcd((v - u)/2, u);
    }
}

int RSA::findE(int eulerValue)
{
    int e = 2;
    while( e < eulerValue)
    {
        if(gcd(e, eulerValue) == 1)
            return e;
        ++e;
    }

    return -1;
}

bool RSA::validateKey(const QString& key)
{
    if(!Utils::validateString(key, ONLY_NUMBERS_RE))
        return false;

    auto values = key.split(' ');
    if(values.size() != 2) return false;

    return true;
}

QString RSA::encode(const QString& text, const QString& key)
{
    if(!validateKey(key) || !!Utils::validateString(text, ONLY_ENGLISH_LETTERS))
        return "";

    auto [P, Q] = parseKey(key);
            auto n = P*Q;
            auto U = EulerFuntion(P, Q);
            auto e = findE(U);

            QString result = "";

            for(const auto& symb : text)
    {
        auto s = symb.cell();
        result += QString::number(Utils::powMod(s,e,n), 16);
    }
    return result;
}
