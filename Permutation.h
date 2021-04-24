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
    static QString makeEncode(const std::vector<QString>& table)
    {
        QString result;

        for(int i{0}, offset{table[0].size()-1}; i < table.size()-1; ++i, --offset)
        {
            for(auto it = table.cbegin(); it != table.cend(); ++it)
            {
                if(it->operator[](offset) != ' ')
                    result += it->operator[](offset);
            }
        }

        return result;
    }

    static std::vector<QString> maketable(const QString& text, const int& size)
    {
        auto tableSize = text.size() % size == 0 ? text.size() / size : (text.size() / size) + 1;
        std::vector<QString> table;
        qDebug() << tableSize;
        for(int i{0}, offset{0}; i < tableSize; ++i)
        {
            if(offset + size > text.size())
            {
                auto rest = std::distance(std::next(text.begin() + offset), text.end());
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
        auto intKey = key.toLongLong();
        auto result = text;
        result.replace(QRegularExpression("\\s+"), QString());

        return makeEncode(maketable(result, intKey));
    }
};

} // namespace Algorithm
