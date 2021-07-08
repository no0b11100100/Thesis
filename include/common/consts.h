#pragma once
#include <QString>
#include <QStringList>
#include "../Description.h"

/*Alias*/
using ReturnType = std::tuple<QString, Description::Description>;
using List = QList<QString>;
using TextType = QList<List>;
using TableType = QList<QList<List>>;

/*Algorithm names*/
const QString AS_CAESAR = "Алгоритм Цезаря";
const QString AS_VIGENERA = "Алгоритм Віженера";
const QString AS_PERMUTATION = "Проста перестановка";
const QString AS_REPLACEMENT = "Алгоритм заміни";
const QString AS_SDES = "SDES";
const QString AS_RC4 = "RC4";
const QString AS_RSA = "RSA";
const QString AS_AES = "AES";
const QString AS_STEGANOGRAPHY = "Стеганографія";

/*SDES constants*/
const QString IP = "ІР перестановку";
const QString EXPANDED = "Розширення ключа";
const QString SBOX_PERMUTATION = "SBOX перестановка";
const QString IP_1 = "ІР-1 перестановка";
const QString P_10 = "Р_10";
const QString P_8 = "Р_8";

/*Alphabets*/
const QString ENGLISH_ALPHABET = "abcdefghijklmnopqrstuvwxyz";
const QString UKRAINIAN_ALPHABET = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
constexpr int UKRAINIAN_ALPHABET_SIZE = 33;
constexpr int ENGLISH_ALPHABET_SIZE = 26;
const QString BASE_64_TEXT = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 /";

/*Validate text regexps*/
const QString ONLY_UKRAINIAN_LETTERS = "[абвгґдеєжзиіїйклмнопрстуфхцчшщьюяАБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ]";
const QString ONLY_ENGLISH_LETTERS = "[a-zA-Z]";
const QString ONLY_NUMBERS_RE = "[0-9]";
const QString ONLY_BINARY_RE = "[0-1]";
//const QString ONLY_HEX = "0123456789abcdef";

/*Validate permutation regexps*/
const QStringList PERMUTATION_4 = {"1", "2", "3", "4"};
const QStringList PERMUTATION_8 = {"1", "2", "3", "4", "5", "6", "7", "8"};
const QStringList PERMUTATION_10 = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

/*Buttons text*/
const QString GENERATE_KEY = "Згенерувати ключ";
const QString ENCODE = "Зашифрувати";
const QString DECODE = "Розшифрувати";
const QString THEORY = "Теорія";

/*Labels text*/
const QString TEXT = "Введіть текст";
const QString KEY = "Введіть ключ";
const QString RESULT = "Результат";

/*Description headers names*/
const QString ENCODING = "Шифрування";
const QString DECODING = "Розшифрування";
const QString VIGENERE_TABLE = "Формування таблиці Віженера";
const QString MAKE_S_RC4 = "Формування таблиці S";
const QString MAKE_KSA = "KSA";
const QString KEY_GENERATION = "Формування ключа";

/*Text formating*/
const QString TAB = "    ";
const QString DOUBLE_TAB = TAB + TAB;

const QString ERROR_TEXT = "Неправильні дані";
