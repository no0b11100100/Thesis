#include "../include/algorithm/base64.h"
#include "../include/common/utils.h"
#include "../include/common/consts.h"

using namespace Algorithm;

// https://coderoad.ru/342409/%D0%9A%D0%B0%D0%BA-%D0%BC%D0%BD%D0%B5-base64-%D0%BA%D0%BE%D0%B4%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D1%82%D1%8C-%D0%B4%D0%B5%D0%BA%D0%BE%D0%B4%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D1%82%D1%8C-%D0%B2-C
QString base64::encode(const QString & text)
{
    size_t len = text.size();
    size_t olen = 4*((len + 2) / 3);

    if (olen < len)
        return QString();

    QString result(olen, '=');
    auto charToInt = [](const QChar& c) { return c.cell(); };

    auto resIt = result.begin();
    constexpr unsigned step = 3;
    QString chan;
    for(int i{0}; len >= step; len -= step, i += step)
    {
        chan = text.mid(i, step);
        *resIt++ = BASE_64_TEXT[charToInt(chan[0]) >> 2];
        *resIt++ = BASE_64_TEXT[((charToInt(chan[0]) & 0x03) << 4) | (charToInt(chan[1]) >> 4)];
        *resIt++ = BASE_64_TEXT[((charToInt(chan[1]) & 0x0f) << 2) | (charToInt(chan[2]) >> 6)];
        *resIt++ = BASE_64_TEXT[charToInt(chan[2]) & 0x3f];
    }

    if(len != 0)
    {
        chan = text.mid(text.size()-len, step);
        *resIt++ = BASE_64_TEXT[charToInt(chan[0]) >> 2];
        if(len == 1)
        {
            *resIt++ = BASE_64_TEXT[(charToInt(chan[0]) & 0x03) << 4];
        }
        else
        {
            *resIt++ = BASE_64_TEXT[((charToInt(chan[0]) & 0x03) << 4) | (charToInt(chan[1]) >> 4)];
            *resIt++ = BASE_64_TEXT[(charToInt(chan[1]) & 0x0f) << 2];
        }
    }

    qDebug() << result;

    return result;
}

QString base64::decode(const QString & text)
{
    static const int B64index[256] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62, 63, 62, 62, 63, 52, 53, 54, 55,
    56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,
    7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,
    0,  0,  0, 63,  0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };

    const size_t size = text.size();
    int pad = size > 0 && (size % 4 || text.back() == '=');
    const size_t L = ((size + 3) / 4 - pad) * 4;
    QString result(L / 4 * 3 + pad, '\0');

    auto resIt = result.begin();
    auto charToInt = [](const QChar& c) { return c.cell(); };

    for (size_t i = 0; i < L; i += 4)
    {
        int n = B64index[charToInt(text.at(i))] << 18 | B64index[charToInt(text.at(i+1))] << 12 | B64index[charToInt(text.at(i+2))] << 6 | B64index[charToInt(text.at(i+3))];
        *resIt++ = QChar(n>>16);
        *resIt++ = QChar(n >> 8 & 0xFF);
        *resIt++ = QChar(n & 0xFF);
    }

    if (pad)
    {
        int n = B64index[charToInt(text.at(L))] << 18 | B64index[charToInt(text.at(L+1))] << 12;
        result.back() = n >> 16;

        if (size > L + 2 && text.at(L+2) != '=')
        {
            n |= B64index[charToInt(text.at(L+2))] << 6;
            result.push_back(n >> 8 & 0xFF);
        }
    }

    qDebug() << result;

    return result;
}
