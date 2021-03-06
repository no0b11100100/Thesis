#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/algorithm/Replacement.h"

using namespace ::testing;

TEST(Replacement, EncodeTest)
{
    QString res = Algorithm::Replacement::encode("Криптографія", "чжбвкюзгґсєйиуфлітрхцденаїяшмщьоп");
    QString expected = "фцєхервцчайп";
    EXPECT_EQ(res, expected);
}


TEST(Replacement, DecodeTest)
{
    QString res = Algorithm::Replacement::decode("фцєхервцчайп", "чжбвкюзгґсєйиуфлітрхцденаїяшмщьоп");
    QString expected = "криптографія";
    EXPECT_EQ(res, expected);
}
