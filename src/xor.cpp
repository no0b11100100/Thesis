#include "../include/algorithm/xor.h"
#include "../include/common/utils.h"

using namespace Algorithm;

QString XOR::encode(const QString & text, const QString& key)
{
    QString result = text;
    std::transform(text.cbegin(), text.cend(), key.cbegin(), result.begin(), [](const QChar& textChar, const QChar& keyChar)
    {
        return QChar(textChar.cell() ^ keyChar.cell());
    });

    return Utils::prettyHex(result);
}

QString XOR::decode(const QString & text, const QString & key)
{
    QString result = "";
    const int textStep = 2;
    for(int i{0}, j{0}; i < text.size() && j < key.size(); ++j, i += textStep)
    {
        auto c = Utils::hexToChar(text.mid(i, textStep));
        result += QChar(c.cell() ^ key.at(j).cell());
    }

    return result;
}
