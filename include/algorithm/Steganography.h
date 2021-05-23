#pragma once
#include <QString>
#include <QFile>
#include <QDebug>
#include <QPixmap>

#include "../common/utils.h"

namespace Algorithm {

class Steganography
{
    static QString stringToByte(QString str);
public:
    static void encode(const QString& path, const QString& text);

    static QString decode(const QString& firstPath, const QString& secondPath);
};

} // namespace Algorithm
