#pragma once
#include <QString>
#include <array>
#include <unordered_map>

#include "../common/utils.h"
#include "../common/consts.h"

namespace Algorithm
{

class SDES
{
    template <size_t N>
    using permutationType = std::array<short, N>;

    template<size_t N>
    static void makePermautation(QString& key, const permutationType<N>& permutation);

    static std::tuple<QString, QString> divideIntoTwoParts(const QString& str);

    static std::tuple<QString, QString> generateKey(const QString& key, const permutationType<10>& permutation);

    static void P_blockCompression(QString& key, const permutationType<8>& P_block);

    static QString keyRound1(const QString& leftPart, const QString& rightPart,
                             const permutationType<8>& P_block);

    static QString keyRound2(const QString& leftPart, const QString& rightPart,
                             const permutationType<8>& P_block);

    static QString textPermutation(const QString& text, const permutationType<8>& permutation);

    static void ExpandText(QString& text, const permutationType<8>& expandTable);

    static QString XOR(const QString& lhs, const QString& rhs);

    static QString prepareDataForSBox(const QString& text);

    static void SPermutation(QString& text, const permutationType<4>& permutation);

    static QString Round(const QString& text, const QString& key, const int& round,
                         const permutationType<8>& expanded, const permutationType<4>& sbox,
                          const std::unordered_map<QString, QString>&, const std::unordered_map<QString, QString>&);

    static Description::Description m_description;

    static constexpr int ROUNDS = 2;

    static constexpr permutationType<8> IP = {2,6,3,1,4,8,5,7};
    static constexpr permutationType<8> EXPANDED = {4,1,2,3,2,3,4,1};
    static constexpr permutationType<4> SBOX_PERMUTATION = {2,4,3,1};
    static constexpr permutationType<8> IP_1 = {4,1,3,5,7,2,8,6};


    /*key permutations*/
    static constexpr permutationType<10> P_10 = {3,5,2,7,4,10,1,9,8,6};
    static constexpr permutationType<8> P_8 = {6,3,7,4,8,5,10,9};

    template<size_t N>
    static std::array<short int, N> toArray(const QString& data)
    {
        auto list = data.split(QString(","));
        std::array<short, N> result;
        int i = 0;
        for(const auto& value : list)
        {
            result[i] = value.toInt();
            ++i;
        }
        return result;
    }

    static std::unordered_map<QString, QString> toMap(const QStringList& list)
    {
        std::unordered_map<QString, QString> result;

        std::unordered_map<int, QString> bin {
            {0, "00"},
            {1, "01"},
            {2, "10"},
            {3, "11"},
            {4, "error"}
        };

        auto toHex = [&](const QString& item)
        {
            return bin.at(item.toInt());
        };

        auto indexToHex = [&](const int& item)
        {
            return bin.at(item);
        };

        int i = 0, j = 0;
        const int limit = 4;
        for(const auto& item : list)
        {
//            qDebug() << "item" << item;
            if(j != 0 && j % limit == 0)
            {
                j = 0;
                ++i;
            }

//            assert(i < 4 && j < 4);
            result.emplace(indexToHex(i)+indexToHex(j),toHex(item));
            ++j;
        }

//        qDebug() << "toMap";
//        for(auto v : result)
//            qDebug() << v;
//        qDebug() << "end toMap";
        return result;
    }

public:
    static ReturnType encode(const QVector<QStringList>&, const TextType&);

    static bool validate(const QVector<QStringList>&, const TextType&);

    static QString theory()
    {
        return " Спрощений DES (S-DES) розроблений професором Едуардом Шаефером (Edward Schaefer) Університету Санта-Клари і є освітнім інструментом для допомоги студентам при вивченні структури DES – для шифрування і дешифрування з використанням блокових шифрів і ключів з невеликою кількістю бітів.  На стороні шифрування S-DES приймає початковий текст по 8 бітів і створює зашифрований текст по 8 бітів; на стороні дешифрування S-DES приймає зашифрований текст на 8 бітів і створює 8-бітовий відкритий текст. Один і той же ключ шифру на 10 бітів використовується і для шифрування, і для дешифрування. Зупинимося на шифруванні, а потім обговоримо дешифрування. Процес шифрування складається з двох перестановок (P-блоки), які ми називаємо початковими і кінцевими перестановками (їх також називають IP і IP - 1), і двох раундів Файстеля. Кожен раунд використовує різні ключі раунду по 8 бітів, згенерованих від ключа шифру згідно заздалегідь заданому алгоритму. S-DES використовує два раунди. Кожен раунд S-DES – це шифр Файстеля, Функція S-DES Основа S-DES – функція S-DES. Функція S-DES застосовує ключ на 8 бітів до правих 4 біт (R I-1), щоб формує вихід на 4 біта. Ця функція складена з чотирьох секцій:       P-блоку розширення, вибілювача, групи S-блоків і прямого P-блоку P-блок розширення – R I-1 вхід на 4 біта, і K I – ключ на 8 бітів, так що ми спочатку повинні розширити R I-1 до 8 бітів.  Хоча стосунки між входом і виходом можуть бути визначені математично, S-DES використовує таблицю, щоб визначити P- блок, як це показано на мал. 5. Зверніть увагу, що число портів виходу – 8, але діапазон значення – тільки 1-4. Деякі з входів йдуть більше ніж в один вихід. Вибілювач (що виключає или). Після перестановки розширення S-DES використовують операцію що виключає или для складання розширеної правої секції і ключа раунду. Зверніть увагу, що ключі раунду використовуються тільки в цій операції. S-блоки. S-блоки роблять реальне змішування (перемішування). S-DES використовують два S-блоку, кожен з входом на 4 біта і виведенням на 2 біта Дані по 8 бітів від другої операції розділені на дві частини по 4 біта, і кожен шматок подається у свій блок. Результат кожного блоку – відрізок на 2 біта; коли вони об'єднуються, в результаті виходить текст на 4 біта. Підстановка в кожному блоці відповідає заздалегідь визначеним правилам, грунтованим на записах в таблицях 4x4. Комбінація вхідних бітів 1 і 4 визначає один з чотирьох рядків; комбінація бітів 2 і 3 визначає один з чотирьох стовпців Оскільки кожен S- блок має свою власну таблицю, потрібні дві таблиці, щоб визначити вихід цих блоків. Значення входів (номер рядка і номер стовпця) і значення виходів на малюнку даються у вигляді десяткових чисел, щоб зберегти простір. Вони мають бути змінені на двійкові значення.";
    }
};

} // namespace Algorithm

