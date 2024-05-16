#ifndef IPPARSER_H
#define IPPARSER_H

#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace IPParserNameSpace
{
    // ("",  '.') -> [""]
    // ("11", '.') -> ["11"]
    // ("..", '.') -> ["", "", ""]
    // ("11.", '.') -> ["11", ""]
    // (".11", '.') -> ["", "11"]
    // ("11.22", '.') -> ["11", "22"]
    std::vector<std::string> split(const std::string &str, char d);

    // Custom comparator function to compare IP addresses lexicographically
    bool compareIP(const std::string &ip1, const std::string &ip2);

    std::vector<std::string> filter(const std::vector<std::string> &ip_pool, const int firstByte);

    std::vector<std::string> filter(const std::vector<std::string> &ip_pool, const int firstByte, const int secondByte);

    std::vector<std::string> filter_any(const std::vector<std::string> &ip_pool, const int byte);
}

class IPParser
{
public:
    IPParser() = default;
    IPParser(const std::string filePath);

    int SortLexicographically();

    int ReverseVector();

    int FilterByFirstByte(const int byte);

    int FilterByFirstAndSecondBytes(const int firstByte, const int secondByte);

    int FilterByAnyByte(const int byte);

private:
    int ParseFile(const std::string filePath);

private:
    std::string m_FilePath{};
    std::vector<std::string> m_IPPool{};
    bool m_IsVectorSorted{};
};

#endif // IPPARSER_H