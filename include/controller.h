#pragma once
#include <QStringList>
#include <QDebug>

#include "include/common/consts.h"
#include "include/algorithm/Replacement.h"
#include "include/algorithm/CaesarCipher.h"
#include "include/algorithm/Permutation.h"
#include "include/algorithm/Replacement.h"
#include "include/algorithm/Vigenere.h"
#include "include/algorithm/SDES.h"
#include "include/algorithm/RC4.h"
#include "include/algorithm/RSA.h"

using namespace Algorithm;

namespace Controller
{

class Controller : public QObject {
    Q_OBJECT
    QString m_algorithmName = algorithmList().first();

public:
    Q_INVOKABLE QStringList algorithmList()
    {
        return QStringList{AS_CAESAR,
                           AS_VIGENERA,
                           AS_PERMUTATION,
                           AS_REPLACEMENT,
                           "Частотный анализ",
                           AS_RC4,
                           AS_RSA,
                           AS_DES,
                           AS_STEGANOGRAPHY
                        };
    }

    Q_INVOKABLE QStringList headerText()
    {
        return QStringList{
            "Генерация ключа",
            "Шифрование",
            "Расшифровка"
        };
    }

    Q_INVOKABLE QStringList contetntText()
    {
        return QStringList{"", "", ""};
    }

    Q_INVOKABLE QString encode(const QString& text, const QString& key)
    {
        qDebug() << "ENCODING DATA " << text << key << " ALGO " << m_algorithmName;
        if(m_algorithmName == AS_CAESAR)
            return CaesarCipher::encode(text, key.toLongLong());
        else if(m_algorithmName == AS_VIGENERA)
            return Vigenere::encode(text, key);
        else if(m_algorithmName == AS_PERMUTATION)
            return Permutation::encode(text, key);
        else if(m_algorithmName == AS_REPLACEMENT)
            return Replacement::encode(text, key);
        else if(m_algorithmName == AS_DES)
            return SDES::encode(text, key);
        else if(m_algorithmName == AS_RC4)
            return RC4::encode(text, key);
        else if(m_algorithmName == AS_RSA)
            return RSA::encode(text, key);
        else if(m_algorithmName == AS_STEGANOGRAPHY)
            return "AS_STEGANOGRAPHY";

        return "";
    }

    Q_INVOKABLE QString getGenerateKey()
    {
        return "invoke model getGenerateKey function";
    }

    Q_INVOKABLE void setAlgorigthm(const QString& name)
    {
        m_algorithmName = name;
        qDebug() << m_algorithmName;
    }
};

} // namespace Controller
