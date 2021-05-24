#pragma once
#include <QStringList>
#include <QDebug>
#include <QVector>

#include <memory>

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
    Q_PROPERTY(QStringList headersName READ headerText NOTIFY descriptionChanged)
    Q_PROPERTY(QStringList contetntsName READ contetntText NOTIFY descriptionChanged)

    QString m_algorithmName = algorithmList().first();
    QStringList m_labelsName;
    QStringList m_buttonsName;
    Description::Description m_description;

    void updateControls()
    {
        if(m_algorithmName == AS_CAESAR)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
        }
        else if(m_algorithmName == AS_VIGENERA)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
        }
        else if(m_algorithmName == AS_PERMUTATION)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
        }
        else if(m_algorithmName == AS_REPLACEMENT)
        {
            m_labelsName = QStringList{TEXT, KEY, RESULT};
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
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

    QString encode(const QString& text, const QString& key)
    {
        qDebug() << "ENCODING DATA " << text << key << " ALGO " << m_algorithmName;
        QString result = "";
        if(m_algorithmName == AS_CAESAR)
            std::tie(result, m_description) = CaesarCipher::encode(text, key);
        else if(m_algorithmName == AS_VIGENERA)
            std::tie(result, m_description) = Vigenere::encode(text, key);
        else if(m_algorithmName == AS_PERMUTATION)
            std::tie(result, m_description) = Permutation::encode(text, key);
        else if(m_algorithmName == AS_REPLACEMENT)
            std::tie(result, m_description) = Replacement::encode(text, key);
        else if(m_algorithmName == AS_SDES)
            result = SDES::encode(text, key);
        else if(m_algorithmName == AS_RC4)
            std::tie(result, m_description) = RC4::encode(text, key);
        else if(m_algorithmName == AS_RSA)
            std::tie(result, m_description) = RSA::encode(text, key);
        else if(m_algorithmName == AS_STEGANOGRAPHY){}
//            "AS_STEGANOGRAPHY";

        emit descriptionChanged();
        return result;
    }

    QString decode(const QString& text, const QString& key)
    {
        qDebug() << "DECODING DATA " << text << key << " ALGO " << m_algorithmName;
        QString result = "";
        if(m_algorithmName == AS_CAESAR)
            std::tie(result, m_description) = CaesarCipher::decode(text, key);
        else if(m_algorithmName == AS_VIGENERA)
            std::tie(result, m_description) = Vigenere::decode(text, key);
        else if(m_algorithmName == AS_PERMUTATION)
            std::tie(result, m_description) = Permutation::decode(text, key);
        else if(m_algorithmName == AS_REPLACEMENT)
            std::tie(result, m_description) = Replacement::decode(text, key);
        else if(m_algorithmName == AS_STEGANOGRAPHY)
        {}

        emit descriptionChanged();
        return result;
    }
signals:
    void algorithmNameChanged();
    void descriptionChanged();

public:

    Controller(QObject* parent = nullptr)
        : QObject{parent},
          m_description{Description::Description()}
    {
        updateControls();
//        std::tie(std::ignore, m_description) = Algorithm::RSA::encode("data", "53 59");
                //Algorithm::RC4::encode("HELLOWORLD", "KEY");
                //Algorithm::Vigenere::encode("Криптографія", "Кібербезпека");
                //Algorithm::Permutation::decode("рмупткзрнрнзкрїсваатеаиошоео", "3,1,4,2,5");
                    //Algorithm::CaesarCipher::encode("Криптографія", "1");
//                    Algorithm::CaesarCipher::decode("лсірупґсбхїа", "1");
    }

    Q_INVOKABLE QStringList algorithmList()
    {
        return QStringList{AS_CAESAR,
                           AS_VIGENERA,
                           AS_PERMUTATION,
                           AS_REPLACEMENT,
//                           AS_RC4,
//                           AS_RSA
//                           AS_SDES,
//                           AS_STEGANOGRAPHY
                        };
    }

    QStringList headerText() const { return m_description.GetHeaders(); }

    QStringList contetntText() const { return m_description.GetContents(); }

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
        m_description = {};
        emit descriptionChanged();
    }

    Q_INVOKABLE QString triggerButton(const QString& action, const QString& text, const QString& key)
    {
        qDebug() << "triggerButton" << action << text << key;
        if(action == ENCODE)
            return encode(text, key);
        else if(action == DECODE)
            return decode(text, key);

        return "";
    }
};

} // namespace Controller
