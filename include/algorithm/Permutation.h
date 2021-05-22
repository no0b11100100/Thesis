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

    static void makePermutation(QString& text, const QStringList& permutation)
    {
        QString temp; // рмпие
//        qDebug() << text;
        for(const auto& index : permutation)
        {
            temp += text[index.toInt()-1];
        }

        text = std::move(temp);
    }

    static QString makeEncode(const std::vector<QString>& table, const QStringList& permuationTable)
    {
        QStringList resultTable = permuationTable;
        int i = 0;
        for(const auto& column : permuationTable)
        {
            int _column = column.toLongLong()-1;
            QString resStr = "";

            for(const auto& c : table)
                if(auto symbol = c.at(i); symbol != ' ')
                    resStr += symbol;

            ++i;
            resultTable[_column] = resStr;
        }

        return resultTable.join(QString());
    }

    static QString makeDecode(const std::vector<QString>& table, const QStringList& permuationTable)
    {
        qDebug() << "table";
        for(auto v : table)
            qDebug() << v;

        qDebug() << "end table";

        QString result = "";

        for(int i{0}; i < table.at(0).size(); ++i)
        {
            QString tmp;
            for(const auto& row : table)
            {
                tmp += row[i];
            }
            makePermutation(tmp, permuationTable);
            qDebug() << tmp;
            result += tmp;
        }

        qDebug() << result;
        return result;
    }

    static std::vector<QString> makeEncodeTable(const QString& text, const int& size, const int& chanSize)
    {
        QString default_value(chanSize, QChar(' '));
        std::vector<QString> table(size, default_value);

        for(int i{0}, offset{0}; i < size; ++i)
        {
            if(offset + chanSize > text.size())
            {
                int rest = (offset + chanSize) - text.size();
                table.at(i) = text.mid(offset, chanSize) + QString(rest, QChar(' '));
            } else {
                table.at(i) = (text.mid(offset, chanSize));
                offset += chanSize;
            }
        }

        for(auto v : table)
            qDebug() << v;

        return table;
    }

    static std::vector<QString> makeDecodeTable(const QString& text, const int& keyLegth, const QStringList& key)
    {
        int stringSize = 0;
        int startSpaceColumns = -1;

        if(int ratio = (text.size() / keyLegth); text.size() % keyLegth == 0)
        {
            stringSize = ratio;
        } else
        {
            stringSize = ratio + 1;
            startSpaceColumns = text.size() - (keyLegth * ratio);
        }

        QString default_value(stringSize, QChar(' '));
        std::vector<QString> table(keyLegth, default_value);

//        qDebug() << key;

        for(int i{0}, offset{0}; i < keyLegth; ++i)
        {
//            qDebug() << "i" << i+1;
            if(startSpaceColumns != -1)
            {
                auto it = std::find(key.cbegin(), key.cend(), QString::number(i+1));
//                qDebug() << "startSpaceColumns != -1" << (it == key.cend()) << "distance" << std::distance(key.cbegin(), it);
                if(startSpaceColumns <= std::distance(key.cbegin(), it))
                {
                    table.at(i) = (text.mid(offset, stringSize-1)) + ' ';
                    offset += stringSize-1;
//                    qDebug() << "if" << table.at(i);
                } else
                {
                    table.at(i) = (text.mid(offset, stringSize));
                    offset += stringSize;
                }
            } else
            {
                table.at(i) = (text.mid(offset, stringSize));
                offset += stringSize;
            }
//            qDebug() << table.at(i);
        }

        return table;
    }

    static bool validateKey(QStringList key)
    {
        std::sort(key.begin(), key.end());
        if(key.isEmpty() || key.back().toInt() != key.size()) return false;
        for(auto it = key.cbegin(); it != std::prev(key.cend()); ++it)
            if(it->toInt()+1 != std::next(it)->toInt())
                return false;

        return true;
    }

public:
    static QString encode(const QString& text, const QString& key)
    {
        auto keyTable = key.split(QString(","));
//        if(!validateKey(keyTable) || !Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
//            return "";
        auto result = text;
        result.replace(QRegularExpression("\\s+"), QString());
        int size = text.size() %  keyTable.size() == 0 ? text.size() /  keyTable.size() : (text.size() /  keyTable.size()) + 1;

        return makeEncode(makeEncodeTable(result, size, keyTable.size()), keyTable);
    }

    static QString decode(const QString& text, const QString& key)
    {
        auto keyTable = key.split(QString(","));
        // TODO: add validation
        auto result = text;
        qDebug() << "text" << result;
        result.replace(QRegularExpression("\\s+"), QString());

        return makeDecode(makeDecodeTable(result, keyTable.size(), keyTable), keyTable);
    }
};

} // namespace Algorithm
