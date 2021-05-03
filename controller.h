#pragma once
#include "Replacement.h"
#include "CaesarCipher.h"
#include "Permutation.h"
#include "consts.h"
#include <QStringList>
#include <QDebug>

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
                           "Стеганография"
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
            return "AS_VIGENERA";
        else if(m_algorithmName == AS_PERMUTATION)
            return "AS_PERMUTATION";
        else if(m_algorithmName == AS_REPLACEMENT)
            return "AS_REPLACEMENT";
        else if(m_algorithmName == AS_DES)
            return "AS_DES";
        else if(m_algorithmName == AS_RC4)
            return "AS_RC4";
        else if(m_algorithmName == AS_RSA)
            return "AS_RSA";

        return "";
    }

    Q_INVOKABLE QString getGenerateKey() {
        return "invoke model getGenerateKey function";
    }

    Q_INVOKABLE void setAlgorigthm(const QString& name)
    {
        m_algorithmName = name;
        qDebug() << m_algorithmName;
    }
};

} // namespace Controller
