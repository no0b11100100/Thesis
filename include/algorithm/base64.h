#pragma once

#include <QString>

namespace Algorithm
{

class base64
{
public:
    static QString encode(const QString&);
    static QString decode(const QString&);
    static bool validate(const QString&);
};

}
