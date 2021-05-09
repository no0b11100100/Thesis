#pragma once

#include <QString>
#include <algorithm>
#include <cmath>
#include <QDebug>

namespace Algorithm
{
// https://cpp.mazurok.com/tinyrsa/
// https://www.thecrazyprogrammer.com/2017/03/rsa-algorithm.html
// https://github.com/kaushikthedeveloper/GeeksforGeeks-python/blob/master/Scripts/RSA%20Algorithm%20(%20Encryption%20-%20Decryption%20).py
// https://sites.google.com/site/griffontver/coding/c
class RSA
{
    using InputPrimeNumbers = std::tuple<int, int>;

    static InputPrimeNumbers parseKey(const QString& key)
    {
        auto values = key.split(' ');
        return {values[0].toInt(), values[1].toInt()};
    }

    static int EulerFuntion(int P, int Q)
    {
        return (P-1)*(Q-1);
    }

    static int gcd(int u, int v)
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

    static int findE(int eulerValue)
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

    static size_t fastPow(int number, int pow)
    {

        if(pow == 0) return 1;
        if(pow == 1) return number;

        static auto countBits = [](const size_t& number) -> size_t
        {
            return static_cast<size_t>(log2(number));
        };

        size_t result(1);
        size_t tempResult = number;

        while(pow)
        {
            if(pow == 1)
            {
                result *= number;
                break;
            }
            size_t count = countBits(pow);
            for(size_t i{0}; i < count; ++i)
                tempResult *= tempResult;

            pow -= 1 << count;
            result *= tempResult;
            tempResult = number;
        }

        return result;
    }

public:

    static QString encode(const QString& text, const QString& key)
    {
        auto [P, Q] = parseKey(key);
        auto n = P*Q;
        auto U = EulerFuntion(P, Q);
        auto e = findE(U);

        QString result = "";

        for(const auto& symb : text)
        {
            auto s = symb.cell();
            result += QString::number(fastPow(s, e) % n, 16);
        }
        return result;
    }
};

} // namespace Algorithm
