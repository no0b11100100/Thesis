#include "../include/algorithm/Steganography.h"

using namespace Algorithm;

void Steganography::encode(const QString& path, const QString& text)
{
    //        if(!Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
    //            return;

    qDebug() << "encode" << path.mid(7, path.size()) << text;
    QPixmap pixmap(path.mid(7, path.size()));
    QImage image = pixmap.toImage();
    QColor c = image.pixel(5,5);
    QString bitStr = Utils::stringToBin(text);
    qDebug() << c << c.red() << c.green() << c.blue() << c.alpha() << bitStr;

    int i = 0, j = 0;

    auto column = pixmap.size().rwidth();
    for(const auto& bit : bitStr)
    {
        QColor color = image.pixel(i,j);
        int newByte = (color.blue() + (1 + Steganography::L * QString(bit).toInt()) % 255) ;

        qDebug() << "old" << color.blue();

        QColor newColor = QColor(color.red(), color.green(), newByte);
        image.setPixelColor(i, j, newColor);
        if(j+1 == column)
        {
            j = 0;
            ++i;
        } else
            ++j;
        qDebug() << "new" << newColor.blue();
    }

    if(!image.save("/home/drago/Desktop/C++/Thesis/Thesis/encode.png"))
    {
        qDebug() << "cannot save image";
    }
}

QString Steganography::decode(const QString& firstPath, const QString& secondPath)
{
    qDebug() << "decode" << firstPath.mid(7, firstPath.size()) << secondPath.mid(7, secondPath.size());
    QString encode = firstPath.mid(7, firstPath.size());
    QString normal = secondPath.mid(7, secondPath.size());

    QPixmap pixmapEncode(encode);
    QImage imageEncode = pixmapEncode.toImage();

    QPixmap pixmapNormal(normal);
    QImage imageNormal = pixmapNormal.toImage();

    int i = 0, j = 0;
    auto row = pixmapEncode.size().rheight();
    auto column = pixmapEncode.size().rwidth();
    QString result = "";
    while(true)
    {
        qDebug() << "index" << i << j << "all size" << row << column;
        QColor colorEncode = imageEncode.pixel(i,j);
        QColor colorNormal = imageNormal.pixel(i,j);
        qDebug() << "value " << colorEncode.blue() << colorNormal.blue();
        if(colorEncode.blue() != colorNormal.blue())
        {
            qDebug() << "find bit" << QString::number(colorEncode.blue(), 2);
            int info = abs(colorEncode.blue() - colorNormal.blue()) / Steganography::L;
            result += QString::number(info);
        } else {
            break;
        }

        if(j+1 == column)
        {
            j = 0;
            ++i;
        } else
        {
            if(i+1 == row) break;
            ++j;
        }
    }

    qDebug() << "result" << Utils::binToString(result);
    return Utils::binToString(result);
}
