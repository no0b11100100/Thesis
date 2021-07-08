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
