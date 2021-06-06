#pragma once
#include <QStringList>
#include <QDebug>
#include <QVariantList>
#include <QPair>

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
#include "include/algorithm/AES.h"

using namespace Algorithm;

namespace Controller
{

class Controller : public QObject {
    Q_OBJECT

    using List = QList<QString>;
    using TextType = QList<List>;
    using TableType = QList<QList<List>>;

    Q_PROPERTY(QList<QList<QString>> labelsText READ labelsText NOTIFY textChanged)
    Q_PROPERTY(QStringList buttonsName READ buttonsText NOTIFY viewChanged)
    Q_PROPERTY(QStringList headersName READ headerText NOTIFY descriptionChanged)
    Q_PROPERTY(QStringList contetntsName READ contetntText NOTIFY descriptionChanged)
    Q_PROPERTY(QList<QList<QList<QString>>> tableInfo READ tableInfo NOTIFY tableModelChanged)
    Q_PROPERTY(QStringList algorithmsList READ algorithmsList CONSTANT)

    QString m_algorithmName = algorithmsList().first();
    TextType m_texts;
    QStringList m_buttonsName;
    TableType m_tableInfo;
    Description::Description m_description;

    void updateControls()
    {
        static const List defaultTableValue{"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"};
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
                {TEXT, ""},
                {KEY, ""},
                {IP, ""},
                {EXPANDED, ""},
                {SBOX_PERMUTATION, ""},
                {IP_1, ""},
                {P_10, ""},
                {P_8, ""},
                {RESULT, ""}
            };

            m_tableInfo = {
                {{"S-Box1"}, defaultTableValue},
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
        else if(m_algorithmName == AS_STEGANOGRAPHY)
        {
            m_texts = {
                {TEXT, ""},
//                {KEY, ""},
//                {RESULT, ""}
            };
            m_buttonsName = QStringList{ENCODE, DECODE, THEORY};
        }
    }

    QString encode(const QVector<QStringList>& tables, const TextType& pack)
    {
        qDebug() << "ENCODING" << pack[0][1] << pack[1][1] << "ALGO" << m_algorithmName;
        QString result = "";
        assert(pack.size() == m_texts.size());
        if(m_algorithmName == AS_CAESAR)
            std::tie(result, m_description) = CaesarCipher::encode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_VIGENERA)
            std::tie(result, m_description) = Vigenere::encode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_PERMUTATION)
            std::tie(result, m_description) = Permutation::encode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_REPLACEMENT)
            std::tie(result, m_description) = Replacement::encode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_SDES)
            assert(!tables[0].isEmpty() && !tables[1].isEmpty());
//            result = SDES::encode(text, key);
        else if(m_algorithmName == AS_RC4)
            std::tie(result, m_description) = RC4::encode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_RSA)
            std::tie(result, m_description) = RSA::encode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_STEGANOGRAPHY) {}

        return result;
    }

    QString decode(const TextType& pack)
    {
        qDebug() << "DECODING DATA " << pack[0][1] << pack[1][1] << " ALGO " << m_algorithmName;
        QString result = "";
        assert(pack.size() == m_texts.size());
        if(m_algorithmName == AS_CAESAR)
            std::tie(result, m_description) = CaesarCipher::decode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_VIGENERA)
            std::tie(result, m_description) = Vigenere::decode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_PERMUTATION)
            std::tie(result, m_description) = Permutation::decode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_REPLACEMENT)
            std::tie(result, m_description) = Replacement::decode(pack[0][1], pack[1][1]);
        else if(m_algorithmName == AS_STEGANOGRAPHY) {}

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

signals:
    void viewChanged();
    void descriptionChanged();
    void textChanged();
    void tableModelChanged();

public:

    Controller(QObject* parent = nullptr)
        : QObject{parent},
          m_description{Description::Description()}
    {
        updateControls();

//        auto GMul = [](int a, int b)
//        {
//            int el = 0;
//            constexpr static int size{8};

////            auto h = (a >> 7) & 1;
////            el = a << 1;
////            el ^= h * 0x1B;

//            for(int i{0}; i < size; ++i)
//            {
//                if((b&1) != 0)
//                    el ^= a;

//                bool isHiBitSet = (a&0x80) != 0;
//                a <<= 1;
//                if(isHiBitSet)
//                    a ^= 0x1B;

//                b >>= 1;
//            }

//            return el;
//        };

//        qDebug() << "GMul" << GMul(9, 16);

//        QString t = "abcdefghijklmnop";
//        Matrix4X4 m(t);
        Algorithm::AES::encode("AESUSESAMATRIX", "");
//        std::tie(std::ignore, m_description) = Algorithm::RSA::encode("data", "53 59");
                //Algorithm::RC4::encode("HELLOWORLD", "KEY");
                //Algorithm::Vigenere::encode("Криптографія", "Кібербезпека");
                //Algorithm::Permutation::decode("рмупткзрнрнзкрїсваатеаиошоео", "3,1,4,2,5");
                    //Algorithm::CaesarCipher::encode("Криптографія", "1");
//                    Algorithm::CaesarCipher::decode("лсірупґсбхїа", "1");
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
        qDebug() << "trigger" << pack;

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
};

} // namespace Controller
