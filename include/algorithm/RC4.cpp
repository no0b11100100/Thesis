#include "RC4.h"

using namespace Algorithm;

const RC4::SType RC4::makeS()
{
    SType S;
    for(int i{0}; i < 256; ++i)
        S[i] = (Byte)i;
    return S;
}

void RC4::Swap(Byte* a, Byte* b)
{
    *a = a->cell() ^ b->cell();
    *b = b->cell() ^ a->cell();
    *a  = a->cell() ^ b->cell();
}

void RC4::KSA(SType& S, const QString& key)
{
    int j = 0;
    const size_t keyLength = key.size();
    for(int i{0}; i < 256; ++i)
    {
        j = (j + S[i].cell() + key.at(i%keyLength).cell()) % 256;
        Swap(&S[i], &S[j]);
    }
}

RC4::Byte RC4::PRGA(SType& S)
{
    static int i = 0, j = 0;
    i = (i+1)%256;
    j = (j + S[i].cell()) % 256;
    m_description.GetContentDetails() += DOUBLE_TAB + "Розраховуємо i: (i+1)%256 = " + QString::number(i) + " та j: (j + S[i].cell()) % 256 = " + QString::number(j) + ".";
    m_description.GetContentDetails() += " Міняємо місцями S[i] та S[j]: " + QString::number(S[i].cell(), 16) + " " + QString::number(S[j].cell(), 16) + " та вираховуємо індекс нового бита із таблиці ";
    Swap(&S[i], &S[j]);
    int t = (S[i].cell() + S[j].cell()) % 256;
    m_description.GetContentDetails() += " (S[i] + S[j]) % 256: " + QString::number(S[i].cell(), 16) + " + " + QString::number(S[j].cell(), 16) + " % 256 = " + QString::number(t) + ", що дорівнює біту із таблиці " + QString::number(S[t].cell(), 16);
    return S[t];
}

ReturnType RC4::encode(const QString& plainText, const QString& key)
{
//    KeyType plainText = {'H', 'E', 'L', 'L', 'O', 'W', 'O', 'R', 'L', 'D'};
//    KeyType key = {1,2,3,4,5,6,7,8};

//    if(!Utils::validateString(text, ONLY_ENGLISH_LETTERS))
//        return "";

    m_description.Clear();
    m_description.AddHeader(MAKE_S_RC4);

    auto S = makeS();

    {
        int i = 0;
        const int endRow = 16;
        for(const auto& row : S)
        {
            if(i == 0)
                m_description.GetContentDetails() += DOUBLE_TAB + QString::number(row.cell(), 16) + " ";
            else if(i % endRow == 0)
                m_description.GetContentDetails() += "\n" + DOUBLE_TAB + QString::number(row.cell(), 16) + " ";
            else
                m_description.GetContentDetails() += QString::number(row.cell(), 16) + " ";
            ++i;
        }
    }

    m_description.AddContent();

    m_description.AddHeader(MAKE_KSA);
    KSA(S, key);

    {
        int i = 0;
        const int endRow = 16;
        for(const auto& row : S)
        {
            if(i == 0)
                m_description.GetContentDetails() += DOUBLE_TAB + QString::number(row.cell(), 16) + " ";
            else if(i % endRow == 0)
                m_description.GetContentDetails() += "\n" + DOUBLE_TAB + QString::number(row.cell(), 16) + " ";
            else
                m_description.GetContentDetails() += QString::number(row.cell(), 16) + " ";
            ++i;
        }
    }

    m_description.AddContent();

    m_description.AddHeader(ENCODING);
    m_description.GetContentDetails() += "Вхідний текст: " + plainText + "\nКлюч: " + key + "\nЕтапи:\n";

    KeyType result;
    for(int i{0}; i < plainText.size(); ++i)
    {
        auto pt = plainText.at(i);
        m_description.GetContentDetails() += TAB + "Виконуємо PRGA:\n";
        auto prga = PRGA(S);
        qDebug() << pt << QString::number(pt.cell(), 16) << prga <<  QString::number(prga.cell(), 16);
        m_description.GetContentDetails() += "\n" + DOUBLE_TAB + "Останнім етапом шифрування біту є XOR: " + QString::number(pt.cell(), 16) + " ^ " + QString::number(prga.cell(), 16) + " = " + QString::number(QChar(pt.cell()^prga.cell()).cell(), 16) + "\n";
        result.push_back(pt.cell()^prga.cell());
    }

    QString chipherText = "";
    for(auto v : result)
        chipherText += QString::number(v.cell(), 16);

    m_description.GetContentDetails() += "В результаті отримуємо: " + chipherText + "\n";
    m_description.AddContent();

    return {chipherText, m_description};
}

Description::Description RC4::m_description = Description::Description();
