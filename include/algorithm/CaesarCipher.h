#pragma once

#include <QString>
#include <algorithm>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "../common/consts.h"
#include "../common/utils.h"

#include "../Description.h"

namespace Algorithm
{

class CaesarCipher
{
    static bool validateKey(const QString& key);

    static Description::Description m_description;

public:
    static ReturnType encode(const QString& text, const QString& offset);

    static ReturnType decode(const QString& text, const QString& offset);

    static QString generateKey();

    static bool validate(const QString&, const QString&);

    static QString theory()
    {
        return "Шифр Цезаря або шифр зсуву — симетричний моноалфавітний алгоритм шифрування, в якому кожна буква відкритого тексту заміняється на ту, що віддалена віднеї в алфавіті на сталу кількість позицій. Як і будь-який моноалфавітний шифр, Цезарів вразливий до частотного криптоаналізу. Навіть легше зламати його простим перебором, бо кількість можливихключів зовсім невелика — для українського алфавіту 32 варіанти. Метод Цезаря не надає майже ніякого криптографічного захисту, але він ліг в основу дещоскладніших алгоритмів. Принцип діїПринцип дії полягає в тому, щоб циклічно зсунути алфавіт, а ключ — це кількість літер, на які робиться зсув.y=(x+k) mod n}ПрикладПрипустимо, що, використовуючи шифр Цезаря, з ключем, який дорівнює 3, необхідно зашифрувати словосполучення «ШИФР ЦЕЗАРЯ».Для цього зрушимо алфавіт так, щоб він починався з четвертої букви (Г). Отже, беручи вихідний алфавіт АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ,і зміщуючи всі літери вліво на 3, отримуємо відповідність:\nА Б В Г Ґ Д Е Є Ж З И І Ї Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ь Ю Я\nГ Ґ Д Е Є Ж З И І Ї Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ь Ю Я А Б В,\nде Г=А, Д=В, Е=Г, і т. д.Використовуючи цю схему, відкритий текст «ШИФР ЦЕЗАРЯ» перетворюється на «ЮЙЧУ ЩЗЇГУВ». Для того, щоб одержувач повідомлення міг відновити вихіднийтекст, необхідно повідомити йому, що ключ — 3.КриптоаналізШифр Цезаря має замало ключів — на одиницю менше, ніж літер в абетці. Тому його легко зламати перебором — пробувати усі можливі ключ, покирозшифрування не дасть впізнаваний відкритий текст.Також зламати шифр Цезаря можна, як і звичайний підстановочний шифр, у зв'язку з тим, що частота появи кожної літери в шифртексті збігається з частотоюпояви у відкритому тексті. Якщо припустити, що частота появи літер у відкритому тексті приблизно відповідає середньостатистичній відносній частотіпояви літер в текстах мови, якою написане повідомлення, тоді ключ знаходиться зіставленням перших декількох літер, що трапляються найчастіше увідкритому та зашифрованому текстах. Тобто за допомогою методу частотного криптоаналізу.";
    }

};

} // namespace Algorithm
