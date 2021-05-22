#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/algorithm/Vigenere.h"

using namespace ::testing;

TEST(Vigenere, EncodeTest)
{
    QString res = Algorithm::Vigenere::encode("Криптографія", "Кібербезпека");
    QString expected = "шюіхзпзщпьхя";
    EXPECT_EQ(res, expected);
}

TEST(Vigenere, DecodeTest)
{
    QString res = Algorithm::Vigenere::decode("шюіхзпзщпьхя", "Кібербезпека");
    QString expected = "криптографія";
    EXPECT_EQ(res, expected);
}
