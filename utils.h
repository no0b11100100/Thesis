#pragma once
#include <QString>
#include <QDebug>
#include <unordered_map>

class Utils
{
    template<class Iterator>
    static QChar castHexOrOctalToBinary(Iterator& it, Iterator end)
    {
        static const std::unordered_map<QString, QChar> fromBinaryTo
        {
            {"0000", '0'},
            {"0001", '1'},
            {"0010", '2'},
            {"0011", '3'},
            {"0100", '4'},
            {"0101", '5'},
            {"0110", '6'},
            {"0111", '7'},
            {"1000", '8'},
            {"1001", '9'},
            {"1010", 'A'},
            {"1011", 'B'},
            {"1100", 'C'},
            {"1101", 'D'},
            {"1110", 'E'},
            {"1111", 'F'},
        };
        QString chan(4, '0');

        for(auto chanIt = chan.rbegin(); chanIt != chan.rend() && it != end; ++chanIt, ++it)
            *chanIt = *it;

        return fromBinaryTo.at(chan);
    }
public:
    static QString stringToBin(QString str)
    {
        QByteArray buffer;
        buffer = buffer.append(str);
        QString bytes;
        for(auto c : buffer)
            bytes += (QString("%1").arg(c, 8, 2, QChar('0'))) + " ";

        return bytes;
    }

    static QString binToHex(const QString& binStr)
    {
        QString result = "";
        for(auto it = binStr.crbegin(); it != binStr.crend();)
        {
            QChar symbol = castHexOrOctalToBinary(it, binStr.crend());
            result.push_front(symbol);
        }

        qDebug() << result;
        return result;
    }
};
