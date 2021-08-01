#pragma once
#include <QObject>

namespace Algorithms {

class Interface
{
public:
    virtual void encode() = 0;
    virtual void decode() = 0;
    virtual void generateKey() = 0;
//    virtual QString theory() = 0;
    virtual QObject* model() = 0;

    virtual ~Interface() = default;
};

}
