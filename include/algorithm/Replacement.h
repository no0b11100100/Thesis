#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>

#include "../common/consts.h"
#include "../common/utils.h"

#include "../Description.h"

namespace Algorithm
{

class Replacement
{
    static bool validateKey(const QString& key);

    static QChar predicate(const QString& alphabet, const QString& permutation, const QChar& c);

    static Description::Description m_description;

public:
    static ReturnType encode(const QString& text, const QString& permutationAlphabet);

    static ReturnType decode( const QString& text, const QString& permutationAlphabet);

    static QString generateKey();

    static bool validate(const QString&, const QString&);

    static QString theory()
    {
        return "Шифр простої заміни, простий шифр підстановки, моноалфавітний шифр — клас методів шифрування, які зводяться до створення за певним алгоритмом таблицішифрування, в якій для кожної букви відкритого тексту існує єдина зіставлена їй буква шифр-тексту. Саме шифрування полягає в заміні букв. Длярозшифрування досить мати ту ж таблицю, або знати алгоритм, за якою вона генерується.Для розкриття таких шифрів використовується частотний криптоаналіз.Цей вид шифру є окремим випадком шифру підстановки.Шифр простої заміни не завжди передбачає заміну літери на якусь іншу літеру. Допускається використовувати заміну літери на число. До прикладу уявімоякийсь шифр-алфавіт (подається за приклад російський алфавіт): А - 33; Б - 17; В - 8; Г - 16; Д - 2; Е - 15; Ё - 14; Ж - 13; З - 12; И - 98; Й- 10; К - 97; Л- 96; М - 24; Н - 0; О - 11; П - 5; Р - 25; С - 7; Т - 3; У - 64; Ф - 26; Х - 66; Ц - 69; Ч - 4; Ш - 6; Щ - 36; Ь - 21; Ъ - 22; Ы - 23; Э - 37; Ю - 39; Я - 18.У цьому шифрі застосовуються числа, які замінюють літери. Ніякої логіки в цих числах немає, тому отримувач зашифрованого повідомлення також повиненмати копію таблиці шифрування";
    }
};

} // namespace Algorithm
