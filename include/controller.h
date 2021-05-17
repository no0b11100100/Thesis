#pragma once
#include <QStringList>
#include <QDebug>
#include <QVector>
#include <QPair>

#include <functional>

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

    Q_PROPERTY(QStringList labelsName READ labelsText NOTIFY algorithmNameChanged)
    Q_PROPERTY(QStringList buttonsName READ buttonsText NOTIFY algorithmNameChanged)

    QString m_algorithmName = algorithmList().first();
    QStringList m_labelsName;
    QStringList m_buttonsName;

    QString generateKey()
    {
        return "key";
    }

    QString theory()
    {
        return QString();
    }

    void updateControls()
    {
        if(m_algorithmName == AS_CAESAR)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
        else if(m_algorithmName == AS_VIGENERA)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
        }
        else if(m_algorithmName == AS_PERMUTATION)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
        else if(m_algorithmName == AS_REPLACEMENT)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
        else if(m_algorithmName == AS_SDES)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
        else if(m_algorithmName == AS_RC4)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
        else if(m_algorithmName == AS_RSA)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
        else if(m_algorithmName == AS_STEGANOGRAPHY)
        {
            m_labelsName = QStringList{};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
        }
        else
        {
            m_labelsName = QStringList{};
            m_buttonsName = QStringList{};
        }
    }

signals:
    void algorithmNameChanged();
//    void textChanged();

public:

    Controller(QObject* parent = nullptr)
        : QObject{parent}

    {
        updateControls();
    }

    Q_INVOKABLE QStringList algorithmList()
    {
        return QStringList{AS_CAESAR,
                           AS_VIGENERA,
                           AS_PERMUTATION,
                           AS_REPLACEMENT,
                           AS_RC4,
                           AS_RSA,
                           AS_SDES,
                           AS_STEGANOGRAPHY
                        };
    }

    Q_INVOKABLE QStringList headerText()
    {
        return QStringList{"1", "2", "3"};
    }

    // TODO: details
    Q_INVOKABLE QStringList contetntText()
    {
        return QStringList{"", "", ""};
    }

    Q_INVOKABLE QString encode(const QString& text, const QString& key)
    {
        qDebug() << "ENCODING DATA " << text << key << " ALGO " << m_algorithmName;
        if(m_algorithmName == AS_CAESAR)
            return CaesarCipher::encode(text, key);
        else if(m_algorithmName == AS_VIGENERA)
            return Vigenere::encode(text, key);
        else if(m_algorithmName == AS_PERMUTATION)
            return Permutation::encode(text, key);
        else if(m_algorithmName == AS_REPLACEMENT)
            return Replacement::encode(text, key);
        else if(m_algorithmName == AS_SDES)
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

    QStringList labelsText() { return m_labelsName; }
    QStringList buttonsText() { return m_buttonsName; }

    Q_INVOKABLE void setAlgorigthm(const QString& name)
    {
        m_algorithmName = name;
        updateControls();
        emit algorithmNameChanged();
        qDebug() << m_algorithmName << m_labelsName;
    }
};

} // namespace Controller
