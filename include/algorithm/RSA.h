#pragma once

#include <QString>
#include <algorithm>
#include <cmath>
#include <QDebug>
#include "../common/utils.h"

namespace Algorithm
{
// https://cpp.mazurok.com/tinyrsa/
// https://www.thecrazyprogrammer.com/2017/03/rsa-algorithm.html
// https://github.com/kaushikthedeveloper/GeeksforGeeks-python/blob/master/Scripts/RSA%20Algorithm%20(%20Encryption%20-%20Decryption%20).py
// https://sites.google.com/site/griffontver/coding/c
class RSA
{
    using InputPrimeNumbers = std::tuple<int, int>;

    static InputPrimeNumbers parseKey(const QString& key);

    static int EulerFuntion(int P, int Q);

    static int gcd(int u, int v);

    static int findE(int eulerValue);

    static bool validateKey(const QString& key);

public:

    static QString encode(const QString& text, const QString& key);
};

} // namespace Algorithm
