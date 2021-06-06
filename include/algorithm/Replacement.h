#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>

#include "../common/consts.h"
#include "../common/utils.h"

#include "../Description.h"

namespace Algorithm
{

class Replacement
{
    static bool validateKey(const QString& key);

    static QChar predicate(const QString& alphabet, const QString& permutation, const QChar& c);

    static Description::Description m_description;

public:
    static ReturnType encode(const QString& text, const QString& permutationAlphabet);

    static ReturnType decode( const QString& text, const QString& permutationAlphabet);

    static QString generateKey();
};

} // namespace Algorithm
