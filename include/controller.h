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

    void encode(const QString& text, const QString& key)
    {
        qDebug() << "ENCODING DATA " << text << key << " ALGO " << m_algorithmName;
        QString result = "";
        if(m_algorithmName == AS_CAESAR)
            std::tie(result, m_description) = CaesarCipher::encode(text, key);
        else if(m_algorithmName == AS_VIGENERA)
            result = Vigenere::encode(text, key);
        else if(m_algorithmName == AS_PERMUTATION)
            result = Permutation::encode(text, key);
        else if(m_algorithmName == AS_REPLACEMENT)
            std::tie(result, m_description) = Replacement::encode(text, key);
        else if(m_algorithmName == AS_SDES)
            result = SDES::encode(text, key);
        else if(m_algorithmName == AS_RC4)
            result = RC4::encode(text, key);
        else if(m_algorithmName == AS_RSA)
            result = RSA::encode(text, key);
        else if(m_algorithmName == AS_STEGANOGRAPHY){}
//            "AS_STEGANOGRAPHY";

        for(auto& label : m_labelsName)
            if(label == RESULT)
                label = result;
    }

    void decode(const QString& text, const QString& key)
    {
        qDebug() << "DECODING DATA " << text << key << " ALGO " << m_algorithmName;
        if(m_algorithmName == AS_CAESAR)
            CaesarCipher::decode(text, key);
        else if(m_algorithmName == AS_VIGENERA)
            Vigenere::decode(text, key);
        else if(m_algorithmName == AS_PERMUTATION)
            Permutation::decode(text, key);
        else if(m_algorithmName == AS_REPLACEMENT)
            Replacement::decode(text, key);
        else if(m_algorithmName == AS_STEGANOGRAPHY)
        {}
    }
signals:
    void algorithmNameChanged();
//    void textChanged();

public:

    Controller(QObject* parent = nullptr)
        : QObject{parent},
          m_description{Description::Description()}
    {
        updateControls();
        std::tie(std::ignore, m_description) = //Algorithm::CaesarCipher::encode("Криптографія", "1");
                    Algorithm::CaesarCipher::decode("лсірупґсбхїа", "1");
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
        return m_description.GetHeaders();
    }

    Q_INVOKABLE QStringList contetntText()
    {
        return m_description.GetContents();
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
//        m_description.Clear();
        qDebug() << m_algorithmName << m_labelsName;
    }

    Q_INVOKABLE void triggerButton(const QString& action, const QString& text, const QString& key)
    {
        if(action == ENCODE)
            encode(text, key);
        else if(action == DECODE)
            decode(text, key);

//        emit algorithmNameChanged();
    }
};

} // namespace Controller
