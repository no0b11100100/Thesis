#pragma once

#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include <vector>

#include "../common/utils.h"

namespace Algorithm
{

struct Permutation
{
private:

    static void makePermutation(QString& text, const QStringList& permutation);

    static QString makeEncode(const std::vector<QString>& table, const QStringList& permuationTable);

    static QString makeDecode(const std::vector<QString>& table, const QStringList& permuationTable);

    static std::vector<QString> makeEncodeTable(const QString& text, const int& size, const int& chanSize);

    static std::vector<QString> makeDecodeTable(const QString& text, const int& keyLegth, const QStringList& key);

    static bool validateKey(QStringList key);

public:
    static QString encode(const QString& text, const QString& key);

    static QString decode(const QString& text, const QString& key);
};

} // namespace Algorithm
