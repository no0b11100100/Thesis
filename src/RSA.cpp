#include "../include/algorithm/RSA.h"

using namespace Algorithm;

RSA::InputPrimeNumbers RSA::parseKey(const QString& key)
{
    auto values = key.split(' ');
    qDebug() << values.size();
    return {values[0].toInt(), values[1].toInt()};
}

int RSA::EulerFuntion(int P, int Q) { return (P-1)*(Q-1); }

int RSA::gcd(int u, int v)
{
    if (u == v) return u;
    if (u == 0) return v;
    if (v == 0) return u;

    if (!(u&1))
    {
        if (v&1) return gcd(u/2, v);
        else return 2 * gcd(u/2, v/2);
    }
    else
    {
        if (!(v&1)) return gcd(u, v/2);
        if (u > v) return gcd((u - v)/2, v);
        else return gcd((v - u)/2, u);
    }
}

int RSA::findE(int eulerValue)
{
    int e = 2;
    while( e < eulerValue)
    {
        if(gcd(e, eulerValue) == 1)
            return e;
        ++e;
    }

    return -1;
}

//bool RSA::validateKey(const QString& key)
//{
//    if(!Utils::validateString(key, ONLY_NUMBERS_RE))
//        return false;

//    auto values = key.split(' ');
//    if(values.size() != 2) return false;

//    return true;
//}

ReturnType RSA::encode(const QString& text, const QString& key)
{
//    if(!validateKey(key) || !!Utils::validateString(text, ONLY_ENGLISH_LETTERS))
//        return "";

    m_description.Clear();
    m_description.AddHeader(KEY_GENERATION);
    auto [P, Q] = parseKey(key);
    auto n = P*Q;
    auto U = EulerFuntion(P, Q);
    auto e = findE(U);

    m_description.GetContentDetails() += TAB + "Із двох простих чисел " + QString::number(P) + " " + QString::number(Q) +  " вираховуємо іїх добуток " + QString::number(n) + ".";
    m_description.GetContentDetails() += "Після цього необхідно отримати значення функції Ейлера: " + QString::number(U) + " та знайти експоненту: " + QString::number(e);

    m_description.AddContent();

    m_description.AddHeader(ENCODING);
    m_description.GetContentDetails() += "Вхідний текст: " + text + "\nКлюч: " + key + "\nЕтапи:\n";

    QString result = "";

    for(const auto& symb : text)
    {
        auto s = symb.cell();
        auto powMod = QString::number(Utils::powMod(s,e,n), 16);
        result += powMod;
        m_description.GetContentDetails() += DOUBLE_TAB + "Для шифрування необхідно вирахувати наступний вираз: (Літера тексту * еспонента) % значення функції Ейлера: " + powMod + "\n";
    }

    m_description.AddContent();
    return {result, m_description};
}

bool RSA::validate(const QString &text, const QString &key)
{
    auto validateKey = [](const QString &key)
    {
        auto data = key.simplified();
        auto values = key.split(' ');
        if(values.size() != 2) return false;

        auto [P, Q] = parseKey(data);
        auto n = P*Q;
        auto U = EulerFuntion(P, Q);
        auto e = findE(U);

        return e != -1;
    };
    return Utils::validateString(text, ENGLISH_ALPHABET) && validateKey(key);
}

Description::Description RSA::m_description = Description::Description();
