#pragma once
#include <QString>

namespace Algorithm
{

class XOR
{
public:
    static QString encode(const QString&, const QString&);
    static QString decode(const QString&, const QString&);
    static bool validate(const QString&, const QString&);
};

}
