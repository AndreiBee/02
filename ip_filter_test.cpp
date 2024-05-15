#define BOOST_TEST_MODULE ipFilterTest

#include "ip_filter.cpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ipFilterTest)

BOOST_AUTO_TEST_CASE(test_parser)
{
    IPParser ipParser{};
    BOOST_CHECK(ipParser.SortLexicographically() == -1);
    BOOST_CHECK(ipParser.ReverseVector() == -1);
    BOOST_CHECK(ipParser.FilterByFirstByte(28) == -1);
    BOOST_CHECK(ipParser.FilterByFirstAndSecondBytes(28, 256) == -1);
    BOOST_CHECK(ipParser.FilterByAnyByte(28) == -1);
}

BOOST_AUTO_TEST_SUITE_END()