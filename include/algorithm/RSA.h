#pragma once

#include <QString>
#include <algorithm>
#include <cmath>
#include <QDebug>

#include "../common/utils.h"
#include "../common/consts.h"

namespace Algorithm
{
// https://cpp.mazurok.com/tinyrsa/
// https://www.thecrazyprogrammer.com/2017/03/rsa-algorithm.html
// https://github.com/kaushikthedeveloper/GeeksforGeeks-python/blob/master/Scripts/RSA%20Algorithm%20(%20Encryption%20-%20Decryption%20).py
// https://sites.google.com/site/griffontver/coding/c
class RSA
{
    using InputPrimeNumbers = std::tuple<int, int>;

    static InputPrimeNumbers parseKey(const QString& key);

    static int EulerFuntion(int P, int Q);

    static int gcd(int u, int v);

    static int findE(int eulerValue);

//    static bool validateKey(const QString& key);

    static Description::Description m_description;

public:

    static ReturnType encode(const QString& text, const QString& key);

    static bool validate(const QString&, const QString&);

    static QString theory()
    {
        return " RSA (абревіатура від прізвищ Rivest, Shamir та Adleman) — криптографічний алгоритм з відкритим ключем, що базується на обчислювальній складності задачі факторизації великих цілих чисел. RSA став першим алгоритмом такого типу, придатним і для шифрування, і для цифрового підпису. Алгоритм застосовується до великої кількості криптографічних застосунків. Опис алгоритму Алгоритм RSA складається з 4 етапів: генерації ключів, шифрування, розшифрування та розповсюдження ключів. Безпека алгоритму RSA побудована на принципі складності факторизації цілих чисел. Алгоритм використовує два ключі — відкритий (public) і секретний  private), разом відкритий і відповідний йому секретний ключі утворюють пари ключів (keypair). Відкритий ключ не потрібно зберігати в таємниці, він використовується для шифрування даних. Якщо повідомлення було зашифровано відкритим ключем, то розшифрувати його можна тільки відповідним секретним ключем.Генерація ключів Для того, щоб згенерувати пари ключів виконуються такі дії:\n1. Вибираються два великі прості числа p і q приблизно 512 біт завдовжки кожне\n2. Обчислюється їх добуток n=pq\n3. Обчислюється функція Ейлера φ(n)=(p-1)(q-1)\n4. Вибирається ціле число e таке, що 1< e < φ(n) та e взаємно просте з φ(n)\n5. За допомогою розширеного алгоритму Евкліда знаходиться число d таке, що ed ≡1 (mod φ n))\nЧисло n називається модулем, а числа e і d — відкритою й секретною експонентами (англ. encryption and decryption exponents), відповідно.  Пари чисел (n,e) є відкритою частиною ключа, а (n,d) — секретною.  Числа p,q після генерації пари ключів можуть бути знищені, але в жодному разі не повинні бути розкриті. Шифрування Припустимо, що Боб хотів би відправити повідомлення M Алісі. Спочатку він перетворює M в ціле число m так, щоб 0 ≤ m < n за допомогою узгодженого оборотного протоколу, відомого як схеми доповнення. Потім він обчислює зашифрований текст c, використовуючи відкритий ключ Аліси e, за допомогою рівняння: \nc=m<sup>e</sup> mod n\nЦе може бути зроблено досить швидко, навіть для 500-бітних чисел, з використанням модульного зведення в ступінь. Потім Боб передає c Алісі. Розшифрування Для розшифрування повідомлення Боба m Алісі потрібно обчислити таку рівність: m=c<sup>d</sup> mod n\nНеважко переконатися, що при розшифруванні відновиться вихідне повідомлення:\n c<sup>d</sup> ≡ (m<sup>e</sup>)<sup>d</sup> ≡ m<sup>ed</sup> (mod n)\nЗ умови ed ≡1 (mod φ(n)) випливає, що ed=k φ(n)+1 для деякого цілого k, отже m<sup>ed</sup> ≡m <sup>k φ(n)+1</sup> (mod n)\nЗгідно з теоремою Ейлера: m <sup>φ(n)</sup> ≡1 (mod n), тому  m <sup>k φ(n)+</sup> ≡m (mod n) c<sup>d</sup> ≡ m (mod n )";
    }
};

} // namespace Algorithm
