#pragma once
#include "Replacement.h"
#include "CaesarCipher.h"
#include "Permutation.h"
#include <QStringList>
#include <QDebug>

using namespace Algorithm;

namespace Controller
{

class Controller : public QObject {
    Q_OBJECT
    QString m_algorithmName;

public:
    Q_INVOKABLE QStringList algorithmList()
    {
        return QStringList{"Алгоритм Цезаря",
                           "Алгоритм Виженера",
                           "Простая перестановка",
                           "Алгоритм замены",
                           "Частотный анализ",
                           "RC4",
                           "RSA",
                           "DES",
                           "Стеганография"};
    }

    Q_INVOKABLE QString encode(const QString& text, const QString& key)
    {
        qDebug() << text << key;
        return "";
    }

    Q_INVOKABLE QString getEncodingText() {
        return "invoke model getEncodingText function";
    }

    Q_INVOKABLE QString getDecodingText() {
        return "invoke model getDecodingText function";
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
