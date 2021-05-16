#pragma once
#include <QString>
#include <QStringList>

/*Algorithm names*/
const QString AS_CAESAR = "Алгоритм Цезаря";
const QString AS_VIGENERA = "Алгоритм Виженера";
const QString AS_PERMUTATION = "Простая перестановка";
const QString AS_REPLACEMENT = "Алгоритм замены";
const QString AS_DES = "DES";
const QString AS_RC4 = "RC4";
const QString AS_RSA = "RSA";
const QString AS_STEGANOGRAPHY = "Стеганография";

/*Alphabets*/
const QString ENGLISH_ALPHABET = "abcdefghijklmnopqrstuvwxyz";
const QString UKRAINIAN_ALPHABET = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
constexpr int UKRAINIAN_ALPHABET_SIZE = 33;
constexpr int ENGLISH_ALPHABET_SIZE = 26;

/*Validate regexps*/
const QString ONLY_UKRAINIAN_LETTERS = "[абвгґдеєжзиіїйклмнопрстуфхцчшщьюяАБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ]";
const QString ONLY_ENGLISH_LETTERS = "[a-zA-Z]";
const QString ONLY_NUMBERS_RE = "[0-9]";
const QString ONLY_BINARY_RE = "[0-1]";

const QStringList PERMUTATION_4 = {"1", "2", "3", "4"};
const QStringList PERMUTATION_8 = {"1", "2", "3", "4", "5", "6", "7", "8"};
const QStringList PERMUTATION_10 = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
