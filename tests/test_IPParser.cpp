// #define BOOST_TEST_MODULE IPParserTest

#include <gtest/gtest.h>
// #include <boost/test/unit_test.hpp>
#include "IPParser.h"

// BOOST_AUTO_TEST_CASE(test_parser)
// {
//     IPParser ipParser{};
//     BOOST_CHECK(ipParser.SortLexicographically() == -1);
//     BOOST_CHECK(ipParser.ReverseVector() == -1);
//     BOOST_CHECK(ipParser.FilterByFirstByte(28) == -1);
//     BOOST_CHECK(ipParser.FilterByFirstAndSecondBytes(28, 256) == -1);
//     BOOST_CHECK(ipParser.FilterByAnyByte(28) == -1);

//     IPParser ipParser2{std::string("../ip_filter.tsv")};
//     BOOST_CHECK(ipParser2.SortLexicographically() == 0);
//     BOOST_CHECK(ipParser2.ReverseVector() == 0);
//     BOOST_CHECK(ipParser2.FilterByFirstByte(42) == 0);
//     BOOST_CHECK(ipParser2.FilterByFirstAndSecondBytes(42, 54) == 0);
//     BOOST_CHECK(ipParser2.FilterByAnyByte(28) == 0);
// }

// Your test cases here
TEST(IPParserTest, TestCase1)
{
    // Test code here
    IPParser ipParser{};
    GTEST_CHECK_(ipParser.SortLexicographically() == -1);
    GTEST_CHECK_(ipParser.ReverseVector() == -1);
    GTEST_CHECK_(ipParser.FilterByFirstByte(28) == -1);
    GTEST_CHECK_(ipParser.FilterByFirstAndSecondBytes(28, 256) == -1);
    GTEST_CHECK_(ipParser.FilterByAnyByte(28) == -1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}