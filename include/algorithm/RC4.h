#pragma once

#include <QString>
#include <QDebug>
#include <vector>
#include <array>

#include "../common/utils.h"
#include "../common/consts.h"

namespace Algorithm
{

struct RC4
{
private:

    using Byte = QChar;
    using SType = std::array<Byte, 256>;
    using KeyType = std::vector<Byte>;

    static const SType makeS();

    static void Swap(Byte* a, Byte* b);

    static void KSA(SType& S, const QString& key);

    static Byte PRGA(SType& S);

    static Description::Description m_description;

public:
    static ReturnType encode(const QString&, const QString&);

    static bool validate(const QString&, const QString&);

    static QString generateKey()
    {
        return "encode";
    }

    static QString theory()
    {
        return "RC4 - потоковий шифр, розроблення Роном Рівестом (анг. Ron Rivest) у 1987 году, коли ВІН працював у амеріканській компании RSA Security.З часом було знайдено методи успішної атаки на цею алгоритм и тому зараз ВІН НЕ рекомендується до использование. Підтримка RC4 поступово прібірається зрізніх криптосистем.ОписЯдро алгоритму поточних шифрів складається з функції - генератора псевдовипадкових бітів (гами), який видає потік бітів ключа (ключовий потік, гаму,послідовність псевдовипадкових бітів).Режим гамування для поточних шифрівАлгоритм шифрування.1. Функція генерує послідовність бітів.2. Потім послідовність бітів за допомогою операції «підсумовування по модулю два» (xor) об'єднується з відкритим текстом. Алгоритм розшифровки.1. Повторно створюється (регенерується) потік бітів ключа (Ключовий потік)2. Потік бітів ключа складається з шіфрограмою операцією «xor». В силу властівостей операции «xor» на виході. Вихід вихідний (незашіфрованій) текстRC4 - фактично клас алгоритмів, що визначаються розміром блоку (надалі S-блоку). Параметр n є розміром слова для алгоритму і визначає довжину S-блоку.Зазвичай, n = 8, але в цілях аналізу можна зменшити його. Однак для підвищення безпеки необхідно збільшити цю величину. В алгоритмі немає протиріч назбільшення розміру S-блоку. При збільшенні n, припустимо, до 16 біт, елементів в S-блоці стає 65 536 і відповідно час початкової ітерації будезбільшено. Однак, швидкість шифрування зросте.Внутрішній стан RC4 представляється у вигляді масиву розміром 2n і двох лічильників. Масив відомий як S-блок, і далі буде позначатися як S. Він завждимістить перестановку 2n можливих значень слова. Два лічильника позначені через i і j.Ініціалізація RC4 складається з двох частин:1. ініціалізація S-блоку;2. генерація псевдовипадкового слова K.Ініціалізація S-блокуАлгоритм також відомий як «key-scheduling algorithm» або «KSA». Цей алгоритм використовує ключ, що подається на вхід користувачем, збережений в Key, і маєдовжину L байт. Ініціалізація починається з заповнення масиву S, далі цей масив перемішується шляхом перестановок, які визначаються ключем. Так яктільки одна дія виконується над S, то повинно виконуватися твердження, що S завжди містить один набір значень, який був даний при початковіїініціалізації (S [i]: = i). Генерація псевдовипадкового слова KГенератор ключового потоку RC4Ця частина алгоритму називається генератором псевдовипадковій послідовності (англ. Pseudo-random generation algorithm, PRGA). Генератор ключового потокуRC4 переставляє значення, що зберігаються в S. В одному циклі RC4 визначається одне n-бітове слово K з ключового потоку. Надалі ключове слово буде складено по модулю два з вихідним текстом, яке користувач хоче зашифрувати, і отриманий зашифрований текс";
    }
};

} // namespace Algorithm
