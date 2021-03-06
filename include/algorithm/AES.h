#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>
#include <array>

#include "../common/consts.h"
#include "../common/utils.h"

#include "../Description.h"
#include "Matrix.h"

namespace Algorithm
{

class AES
{
    static Description::Description m_description;
    static constexpr int rounds{10};
    static std::array<Matrix4X4::Line, rounds> rcon; // 6C, D8, AB, 4D, 9A, 2F, 5E, BC, 63, C6, 97, 35, 6A, D4, B3, 7D, FA, EF and C5

    static void SubBytes(Matrix4X4&);
    static Matrix4X4 KeyExpanded(const Matrix4X4&, const int&);
    static void ShiftRows(Matrix4X4&);
    static void MixColumns(Matrix4X4&);
    static void AddRoundKey(Matrix4X4&, const Matrix4X4&);
    static void Round(Matrix4X4&, const Matrix4X4&);
    static void FinalRound(Matrix4X4&, const Matrix4X4&);

    static std::array<uint8_t, 256> initSBox();

public:
    static ReturnType encode(const QString&, const QString&);

    static bool validate(const QString&, const QString&);

    static QString generateKey()
    {
        return "Thats my Kung Fu";
    }

    static QString theory()
    {
        return "Advanced Encryption Standard (AES), також відомий під назвою Rijndael — симетричний алгоритм блочного шифрування (розмір блока 128 біт, ключ 128/192/256 біт), фіналіст конкурсу AES і прийнятий як американський стандарт шифрування урядом США. Вибір припав на AES з розрахуванням на широке використання і активний аналіз алгоритму, як це було із його попередником, DES. Державний інститут стандартів і технологій (англ. National Institute of Standards and Technology, NIST) США опублікував попередню специфікацію AES 26 жовтня 2001 року, після п'ятилітньої підготовки. 26 травня 2002 року AES оголошено стандартом шифрування. Станом на 2009 рік AES є одним із найпоширеніших алгоритмів симетричного шифрування. Опис алгоритму В принципі, алгоритм, запропонований Рейменом і Дейцменом, і AES не одне і те ж. Алгоритм Рейндол підтримує широкий діапазон розміру блоку та ключа. AES має фіксовану довжину у 128 біт, а розмір ключа може приймати значення 128, 192 або 256 біт. В той час як Рейндол підтримує розмірність блоку та ключа із кроком 32 біт у діапазоні від 128 до 256. Через фіксований розмір блоку AES оперує із масивом 4×4 байт, що називається станом (версії алгоритму із більшим розміром блоку мають додаткові колонки). Для ключа 128 біт алгоритм має 10 раундів у яких послідовно виконуються операції     • subBytes()     • shiftRows()     • mixcolumns() (у 10-му раунді пропускається)     • xorRoundKey() SubBytes() У процедурі SubBytes , кожен байт в state замінюється відповідним елементом у фіксованій 8-бітній таблиці пошуку, S; b<sub>ij</sub> = S (a<sub>ij</sub> ). Процедура SubBytes() обробляє кожен байт стану незалежно, проводячи нелінійну заміну байтів використовуючи таблицю замін (S-box). Така операція забезпечує нелінійність алгоритму шифрування.  ShiftRows() У процедурі ShiftRows , байти в кожному рядку state циклічно зсуваються вліво. Розмір зміщення байтів кожного рядка залежить від її номера ShiftRows працює з рядками таблиці State. При цій трансформації рядка стану циклічно зсуваються на r байтів по горизонталі, залежно від номера рядка. Для нульового рядка r = 0, для першого рядка r = 1 і т. д. Таким чином кожна колонка вихідного стану після застосування процедури ShiftRows складається з байтів з кожної колонки початкового стану. Для алгоритму Rijndael патерн зсуву рядків для 128 - і 192-бітних рядків однаковий. Однак для блоку розміром 256 біт відрізняється від попередніх тим, що 2, 3, і 4-і рядки зміщуються на 1, 3, і 4 байти, відповідно. Фактично це проста перестановка байтів таблиці 4х4 State. MixColumns() У процедурі MixColumns , кожна колонка стану перемножується з фіксованим многочленом c (x). У процедурі MixColumns , чотири байти кожної колонки State змішуються, використовуючи для цього зворотну лінійну трансформацію. MixColumns опрацьовує стан по колонках, трактуючи кожну з них як поліном четвертого степеня. Під час цієї операції, кожен стовпчик множиться на матрицю AddRoundKey() У процедурі AddRoundKey , кожен байт стану об'єднується з RoundKey використовуючи операцію XOR. У процедурі AddRoundKey , RoundKey кожного раунду об'єднується зі State. Для кожного раунду Roundkey виходить з CipherKey використовуючи процедуру KeyExpansion ; кожен RoundKey такого ж розміру, що і State. Процедура виробляє побітовий XOR кожного байта State з кожним байтом RoundKey . Фактично це звичайний побайтовий XOR байт ключа з байтами таблиці State.";
    }
};

} // namespace Algorithm
