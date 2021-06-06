#include "../include/algorithm/Steganography.h"

using namespace Algorithm;

QString Steganography::stringToByte(QString str)
{
    QByteArray buffer;
    buffer = buffer.append(str);
    QString bytes;
    for(auto c : buffer)
        bytes += (QString("%1").arg(c, 8, 2, QChar('0'))) + " ";

    return bytes;
}
void Steganography::encode(const QString& path, const QString& text)
{
    //        if(!Utils::validateString(text, ONLY_UKRAINIAN_LETTERS))
    //            return;

    QPixmap pixmap(path);
    QImage image = pixmap.toImage();
    QColor c = image.pixel(5,5);
    QString bitStr = "1";//stringToByte(text);
    qDebug() << c << c.red() << c.green() << c.blue() << c.alpha() << bitStr;

    int i = 0, j = 0;
    auto column = pixmap.size().rwidth();
    for(const auto& bit : bitStr)
    {
        int newByte;
        QColor color = image.pixel(i,j);
        if(bit == '1')
        {
            if(color.blue()&1)
                newByte = color.blue();
            else
                newByte = color.blue()+1;

            qDebug() << "newByte" << newByte;
        }
        else
        {
            if(color.blue()&1)
                newByte = color.blue();
            else
                newByte = color.blue()+1;
        }

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
    QString encode = "/home/drago/Desktop/C++/Thesis/Thesis/encode.png";
    QString normal = "/home/drago/Desktop/C++/Thesis/Thesis/close1.png";

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
        QColor colorEncode = imageEncode.pixel(i,j);
        QColor colorNormal = imageNormal.pixel(i,j);
        qDebug() << "value " << colorEncode.blue() << colorNormal.blue();
        if(colorEncode.blue() != colorNormal.blue())
        {
            qDebug() << QString::number(colorEncode.blue(), 2);
            result += QString::number(colorEncode.blue(), 2).back();
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
        break;
    }

    qDebug() << "result" << result;
    return result;
}
