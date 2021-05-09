#pragma once

#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include <vector>

namespace Algorithm
{

struct Permutation
{
private:
    static QString makeEncode(const std::vector<QString>& table, const QStringList& permuationTable)
    {
        QStringList resultTable = permuationTable;
        qDebug() << resultTable;
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

    static std::vector<QString> maketable(const QString& text, const int& size)
    {
        auto tableSize = text.size() % size == 0 ? text.size() / size : (text.size() / size) + 1;
        std::vector<QString> table;
        qDebug() << tableSize << text;
        for(int i{0}, offset{0}; i < tableSize; ++i)
        {
            if(offset + size > text.size())
            {
                auto rest = std::distance(std::next(text.begin() + offset), text.end())+1;
                QString tmp = text.mid(offset, rest);
                for(int j{0}; j < (size-rest); ++j)
                    tmp += " ";
                table.push_back(tmp);
            }
            else
            {
                table.push_back(text.mid(offset, size));
                offset += size;
            }
        }

        return table;
    }

public:
    static QString encode(const QString& text, const QString& key)
    {
        auto keyTable = key.split(QString(","));
        int columnCount = keyTable.size();
        auto result = text;
        result.replace(QRegularExpression("\\s+"), QString());

        return makeEncode(maketable(result, columnCount), keyTable);
    }
};

} // namespace Algorithm
