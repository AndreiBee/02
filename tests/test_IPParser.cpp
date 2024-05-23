#define BOOST_TEST_MODULE IPParserTest
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include "IPParser.h"

BOOST_AUTO_TEST_CASE(test_parser)
{
    IPParser ipParser{};
    BOOST_CHECK(ipParser.SortLexicographically() == -1);
    BOOST_CHECK(ipParser.ReverseVector() == -1);
    BOOST_CHECK(ipParser.FilterByFirstByte(28) == -1);
    BOOST_CHECK(ipParser.FilterByFirstAndSecondBytes(28, 256) == -1);
    BOOST_CHECK(ipParser.FilterByAnyByte(28) == -1);

    // IPParser ipParser2{std::string("../ip_filter.tsv")};
    // BOOST_CHECK(ipParser2.SortLexicographically() == 0);
    // BOOST_CHECK(ipParser2.ReverseVector() == 0);
    // BOOST_CHECK(ipParser2.FilterByFirstByte(42) == 0);
    // BOOST_CHECK(ipParser2.FilterByFirstAndSecondBytes(42, 54) == 0);
    // BOOST_CHECK(ipParser2.FilterByAnyByte(28) == 0);
}