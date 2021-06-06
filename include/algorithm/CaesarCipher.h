#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "../common/consts.h"
#include "../common/utils.h"

#include "../Description.h"

namespace Algorithm
{

class CaesarCipher
{
    static bool validateKey(const QString& key);

    static Description::Description m_description;

public:
    static ReturnType encode(const QString& text, const QString& offset);

    static ReturnType decode(const QString& text, const QString& offset);

    static QString generateKey();

};

} // namespace Algorithm
