#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/algorithm/CaesarCipher.h"

using namespace ::testing;

TEST(CaesarCipher, EncodeTest)
{
    QString res = Algorithm::CaesarCipher::encode("а", "1");
    QString expected = "б";
    EXPECT_EQ(res, expected);

    res = Algorithm::CaesarCipher::encode("я", "1");
    expected = "а";
    EXPECT_EQ(res, expected);

    res = Algorithm::CaesarCipher::encode("Криптографія", "1");
    expected = "лсірупґсбхїа";
    EXPECT_EQ(res, expected);
}

