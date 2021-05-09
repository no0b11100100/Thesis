#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/algorithm/Permutation.h"

using namespace ::testing;

TEST(Permutation, EncodeTest)
{
    QString res = Algorithm::Permutation::encode("зразок маршрутної перестановки", "3,1,4,2,5");
    QString expected = "рмупткзрнрнзкрїсваатеаиошоео";
    EXPECT_EQ(res, expected);
}
