#pragma once

#include <QString>
#include <QDebug>
#include <vector>
#include <array>

// https://www.geeksforgeeks.org/implementation-of-rc4-algorithm/
namespace Algorithm
{

struct RC4
{
private:

    static const std::array<QChar, 256> init(const QString& key)
    {
        std::array<QChar, 256> S;
        int keyLenght = key.length();

        for(int i{0}; i < 256; ++i)
        {
            qDebug() << QChar(i);
            S[i] = QChar(i);
        }

        return S;
    }

    static QString stringToByte(QString str)
    {
        QByteArray buffer;
        buffer = buffer.append(str);
        QString bytes;
        for(auto c : buffer)
            bytes += (QString("%1").arg(c, 8, 2, QChar('0')));

        return bytes;
    }


public:
    static QString encode(const QString& text, const QString&)
    {
        init(stringToByte(text));

        return QString();
    }

};

} // namespace Algorithm
