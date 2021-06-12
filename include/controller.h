#pragma once
#include <QStringList>
#include <QDebug>
#include <QVariantList>
#include <QPair>
#include <memory>

#include <QQmlComponent>
#include <QtQuick/QQuickView>
#include <QQmlEngine>
#include <QtQuick/QQuickItem>
#include <QQmlProperty>
#include <QQmlApplicationEngine>

#include "include/common/consts.h"

#include "include/algorithm/Replacement.h"
#include "include/algorithm/CaesarCipher.h"
#include "include/algorithm/Permutation.h"
#include "include/algorithm/Replacement.h"
#include "include/algorithm/Vigenere.h"
#include "include/algorithm/SDES.h"
#include "include/algorithm/RC4.h"
#include "include/algorithm/RSA.h"
#include "include/algorithm/AES.h"
#include "include/algorithm/Steganography.h"

using namespace Algorithm;

namespace Controller
{

class Controller : public QObject {
    Q_OBJECT

    Q_PROPERTY(QList<QList<QString>> labelsText READ labelsText NOTIFY textChanged)
    Q_PROPERTY(QStringList buttonsName READ buttonsText NOTIFY viewChanged)
    Q_PROPERTY(QStringList headersName READ headerText NOTIFY descriptionChanged)
    Q_PROPERTY(QStringList contetntsName READ contetntText NOTIFY descriptionChanged)
    Q_PROPERTY(QList<QList<QList<QString>>> tableInfo READ tableInfo NOTIFY tableModelChanged)
    Q_PROPERTY(QStringList algorithmsList READ algorithmsList CONSTANT)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(QString theory READ theory NOTIFY viewChanged)

    QString m_algorithmName = algorithmsList().first();
    TextType m_texts;
    QStringList m_buttonsName;
    TableType m_tableInfo;
    Description::Description m_description;
    QString m_error;

    void updateControls()
    {
        static const List defaultTableValue{"0","1","2","3","2","0","1","3","3","0","1","0","2","1","0","3"};
        m_tableInfo = {};
        m_description = {};
        m_texts = {};
        m_tableInfo = {};
        m_buttonsName = QStringList{};
        if(m_algorithmName == AS_CAESAR)
        {
            m_texts = {
                {TEXT, ""},
                {KEY, ""},
                {RESULT, ""}
            };
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
        }
        else if(m_algorithmName == AS_VIGENERA)
        {
            m_texts = {
                {TEXT, ""},
                {KEY, ""},
                {RESULT, ""}
            };
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
        }
        else if(m_algorithmName == AS_PERMUTATION)
        {
            m_texts = {
                {TEXT, ""},
                {KEY, ""},
                {RESULT, ""}
            };
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
        }
        else if(m_algorithmName == AS_REPLACEMENT)
        {
            m_texts = {
                {TEXT, ""},
                {KEY, ""},
                {RESULT, ""}
            };
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, DECODE, THEORY};
        }
        else if(m_algorithmName == AS_SDES)
        {
            m_texts = {
                {TEXT, "10010111"},
                {KEY, "1010000010"},
                {IP, "2,6,3,1,4,8,5,7"},
                {EXPANDED, "4,1,2,3,2,3,4,1"},
                {SBOX_PERMUTATION, "2,4,3,1"},
                {IP_1, "4,1,3,5,7,2,8,6"},
                {P_10, "3,5,2,7,4,10,1,9,8,6"},
                {P_8, "6,3,7,4,8,5,10,9"},
                {RESULT, ""}
            };

            m_tableInfo = {
                {{"S-Box1"}, List{"1","0","3","2","3","2","1","0","0","2","1","3","3","1","3","2"}},
                {{"S-Box2"}, defaultTableValue},
            };

            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
        else if(m_algorithmName == AS_RC4)
        {
            m_texts = {
                {TEXT, ""},
                {KEY, ""},
                {RESULT, ""}
            };
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
        else if(m_algorithmName == AS_RSA)
        {
            m_texts = {
                {TEXT, ""},
                {KEY, ""},
                {RESULT, ""}
            };
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
        else if(m_algorithmName == AS_AES)
        {
            m_texts = {
                {TEXT, ""},
                {KEY, ""},
                {RESULT, ""}
            };
            m_buttonsName = QStringList{GENERATE_KEY, ENCODE, THEORY};
        }
//        else if(m_algorithmName == AS_STEGANOGRAPHY)
//        {
//            m_texts = {
//                {TEXT, ""},
////                {KEY, ""},
////                {RESULT, ""}
//            };
//            m_buttonsName = QStringList{ENCODE, DECODE, THEORY};
//        }
    }

    QString encode(const QVector<QStringList>& tables, const TextType& pack)
    {
        qDebug() << "ENCODING" << pack[0][1] << pack[1][1] << "ALGO" << m_algorithmName;
        QString result = "";
        assert(pack.size() == m_texts.size());
        if(m_algorithmName == AS_CAESAR)
        {
            if(CaesarCipher::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = CaesarCipher::encode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }else if(m_algorithmName == AS_VIGENERA)
        {
            if(Vigenere::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = Vigenere::encode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }else if(m_algorithmName == AS_PERMUTATION)
        {
            if(Permutation::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = Permutation::encode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }else if(m_algorithmName == AS_REPLACEMENT)
        {
            if(Replacement::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = Replacement::encode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }else if(m_algorithmName == AS_SDES)
        {
            if(SDES::validate(tables, pack))
                std::tie(result, m_description) =  SDES::encode(tables, pack);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        } else if(m_algorithmName == AS_RC4)
        {
            if(RC4::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = RC4::encode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }else if(m_algorithmName == AS_RSA)
        {
            if(RSA::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = RSA::encode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }else if(m_algorithmName == AS_AES)
        {
            if(AES::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = AES::encode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
//            std::tie(result, m_description) = AES::encode(pack[0][1], pack[1][1]);
        }

        return result;
    }

    QString decode(const TextType& pack)
    {
        qDebug() << "DECODING DATA " << pack[0][1] << pack[1][1] << " ALGO " << m_algorithmName;
        QString result = "";
        assert(pack.size() == m_texts.size());

        if(m_algorithmName == AS_CAESAR)
        {
            if(CaesarCipher::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = CaesarCipher::decode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }else if(m_algorithmName == AS_VIGENERA)
        {
            if(Vigenere::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = Vigenere::decode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }else if(m_algorithmName == AS_PERMUTATION)
        {
            if(Permutation::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = Permutation::decode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }else if(m_algorithmName == AS_REPLACEMENT)
        {
            if(Replacement::validate(pack[0][1], pack[1][1]))
                std::tie(result, m_description) = Replacement::decode(pack[0][1], pack[1][1]);
            else
            {
                m_error = ERROR_TEXT;
                emit errorChanged();
            }
        }

        return result;
    }

    QString generate()
    {
        if(m_algorithmName == AS_CAESAR)
        {
            return CaesarCipher::generateKey();
        }
        else if(m_algorithmName == AS_VIGENERA)
        {
            return Vigenere::generateKey();
        } else if(m_algorithmName == AS_PERMUTATION)
        {
            return Permutation::generateKey();
        } else if(m_algorithmName == AS_REPLACEMENT)
        {
            return Replacement::generateKey();
        } else if(m_algorithmName == AS_SDES)
        {
            return "";
        } else if(m_algorithmName == AS_RC4)
        {
            return "";
        } else if(m_algorithmName == AS_RSA)
        {
            return "";
        }

        return "";
    }

    QList<std::shared_ptr<QQuickItem>> m_components;

signals:
    void viewChanged();
    void descriptionChanged();
    void textChanged();
    void tableModelChanged();
    void errorChanged();

public:

    Controller(QObject* parent = nullptr)
        : QObject{parent},
          m_description{Description::Description()},
          m_error{""}
    {
        updateControls();
    }

    QStringList algorithmsList() const
    {
        return QStringList{AS_CAESAR,
                           AS_VIGENERA,
                           AS_PERMUTATION,
                           AS_REPLACEMENT,
                           AS_RC4,
                           AS_RSA,
                           AS_SDES,
                           AS_AES,
                           AS_STEGANOGRAPHY
                        };
    }
    QStringList headerText() const { return m_description.GetHeaders(); }
    QStringList contetntText() const { return m_description.GetContents(); }
    TextType labelsText() const { return m_texts; }
    QStringList buttonsText() const { return m_buttonsName; }
    TableType tableInfo() const { return m_tableInfo; }

    QString theory()
    {
        return "Test text";
    }

    Q_INVOKABLE void setAlgorigthm(const QString& name)
    {
        m_algorithmName = name;
        updateControls();
        emit viewChanged();
        emit tableModelChanged();
        emit textChanged();
        qDebug() << m_algorithmName;

    }

    Q_INVOKABLE void trigger(const QString& action, const QVector<QStringList>& tables, const QList<QList<QString>>& pack)
    {
        qDebug() << "trigger" << action;

//        m_error = "something goes wrong\nplease try again";
//        emit errorChanged();
//        m_error = "";
        m_texts = pack;
        auto changeProperty = [&](const QString& field, const QString& data)
        {
            for(auto& label : m_texts)
                if(label.front() == field)
                    label.back() = data;
        };

        if(action == ENCODE)
            changeProperty(RESULT, encode(tables, pack));
        else if(action == DECODE)
            changeProperty(RESULT, decode(pack));
        else if(action == GENERATE_KEY)
        {
            changeProperty(KEY, generate());
            changeProperty(RESULT, "");
            m_description = {};
        }

        emit textChanged();
        emit descriptionChanged();
    }

    Q_INVOKABLE QString specialTrigger(const QString& action, const QString& str1, const QString& str2)
    {
        qDebug() << "trigger overload";

        if(action == ENCODE)
        {
            Algorithm::Steganography::encode(str1, str2);
            return str1;
        }

        return Algorithm::Steganography::decode(str1, str2);
    }

    QString error() const { return m_error; }
};

} // namespace Controller
