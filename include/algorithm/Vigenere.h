#pragma once
#include <QString>
#include <array>
#include <map>
#include <algorithm>
#include <QDebug>

#include "../common/consts.h"
#include "../common/utils.h"

namespace Algorithm
{

class Vigenere
{
    using TableType = std::array<QString, UKRAINIAN_ALPHABET_SIZE>;

    static TableType fillTable();

    static std::pair<int, int> getIndexs(const QChar& textChar, const QChar& keyChar);

    static Description::Description m_description;

    static void createTableDescription(const TableType& table);

public:
    static ReturnType encode(const QString& text, const QString& key);

    static ReturnType decode(const QString& text, const QString& key);

};

} // namespace Algorithm

