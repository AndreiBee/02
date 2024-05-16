#include "IPParser.h"

namespace IPParserNameSpace
{
    std::vector<std::string> split(const std::string &str, char d)
    {
        std::vector<std::string> r;

        if (str.empty())
            return r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while (stop != std::string::npos)
        {
            r.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }

        r.push_back(str.substr(start));

        return r;
    }

    bool compareIP(const std::string &ip1, const std::string &ip2)
    {
        std::vector<std::string> parts1 = split(ip1, '.');
        std::vector<std::string> parts2 = split(ip2, '.');

        // Compare each part of the IP address lexicographically
        for (size_t i = 0; i < 4; ++i)
        {
            if (std::stoi(parts1[i]) != std::stoi(parts2[i]))
            {
                return std::stoi(parts1[i]) < std::stoi(parts2[i]);
            }
        }
        return false; // If all parts are equal
    }

    std::vector<std::string> filter(const std::vector<std::string> &ip_pool, const int firstByte)
    {
        std::vector<std::string> r;

        if (ip_pool.size() == 0)
            return r;

        for (auto i{0}; i < ip_pool.size(); ++i)
        {
            std::vector<std::string> parts1 = split(ip_pool[i], '.');
            if (std::stoi(parts1[0]) == firstByte)
                r.emplace_back(ip_pool[i]);
        }

        return r;
    }

    std::vector<std::string> filter(const std::vector<std::string> &ip_pool, const int firstByte, const int secondByte)
    {
        auto filteredByFirstByte = filter(ip_pool, firstByte);

        std::vector<std::string> r;
        for (auto i{0}; i < filteredByFirstByte.size(); ++i)
        {
            std::vector<std::string> parts1 = split(filteredByFirstByte[i], '.');
            if (std::stoi(parts1[1]) == secondByte)
                r.emplace_back(filteredByFirstByte[i]);
        }

        return r;
    }

    std::vector<std::string> filter_any(const std::vector<std::string> &ip_pool, const int byte)
    {
        std::vector<std::string> r;

        if (ip_pool.size() == 0)
            return r;

        for (auto i{0}; i < ip_pool.size(); ++i)
        {
            std::vector<std::string> parts1 = split(ip_pool[i], '.');
            for (auto k{0}; k < parts1.size(); ++k)
            {
                if (std::stoi(parts1[k]) == byte)
                    r.emplace_back(ip_pool[i]);
            }
        }

        return r;
    }
}

IPParser::IPParser(const std::string filePath) : m_FilePath(filePath), m_IsVectorSorted(false)
{
    if (!std::filesystem::exists(m_FilePath))
    {
        std::cout << "Not a valid file name" << "\n";
        return;
    }

    ParseFile(m_FilePath);
};

int IPParser::SortLexicographically()
{
    if (!m_IPPool.size())
        return -1;
    // Sort IP addresses lexicographically
    std::sort(m_IPPool.begin(), m_IPPool.end(), IPParserNameSpace::compareIP);
    m_IsVectorSorted = true;
    return 0;
};

int IPParser::ReverseVector()
{
    if (!m_IPPool.size())
        return -1;

    if (!m_IsVectorSorted)
        return -2;

    // Reverse lexicographically sort
    std::reverse(m_IPPool.begin(), m_IPPool.end());
    m_IsVectorSorted = false;
    return 0;
};

int IPParser::FilterByFirstByte(const int byte)
{
    if (!m_IPPool.size())
        return -1;

    auto filteredByFirstByteIP = IPParserNameSpace::filter(m_IPPool, byte);

    if (!filteredByFirstByteIP.size())
        return -1;

    // Print the result
    std::cout << "Filtered by the first byte: " << byte << "\n";
    for (auto i{0}; i < filteredByFirstByteIP.size(); ++i)
    {
        std::cout << '\t' << filteredByFirstByteIP[i] << "\n";
    }
    return 0;
};

int IPParser::FilterByFirstAndSecondBytes(const int firstByte, const int secondByte)
{
    if (!m_IPPool.size())
        return -1;

    auto filteredByFirstAndSecondBytesIP = IPParserNameSpace::filter(m_IPPool, firstByte, secondByte);

    if (!filteredByFirstAndSecondBytesIP.size())
        return -1;

    // Print the result
    std::cout << "Filtered by the first: " << firstByte << " and second byte: " << secondByte << "\n";
    for (auto i{0}; i < filteredByFirstAndSecondBytesIP.size(); ++i)
    {
        std::cout << '\t' << filteredByFirstAndSecondBytesIP[i] << "\n";
    }
    return 0;
};

int IPParser::FilterByAnyByte(const int byte)
{
    if (!m_IPPool.size())
        return -1;

    auto filteredByAnyByte = IPParserNameSpace::filter_any(m_IPPool, byte);

    if (!filteredByAnyByte.size())
        return -1;

    // Print the result
    std::cout << "Filtered by the byte: " << byte << "\n";
    for (auto i{0}; i < filteredByAnyByte.size(); ++i)
    {
        std::cout << '\t' << filteredByAnyByte[i] << "\n";
    }
    return 0;
};

int IPParser::ParseFile(const std::string filePath)
{
    m_IPPool.clear();

    std::ifstream inputFile(filePath);
    // Check if the file opened successfully
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open file." << std::endl;
        return -1; // Exit with error
    }
    // Read and print each line from the file
    std::string line;
    auto linesCount{0};
    while (std::getline(inputFile, line))
    {
        std::vector<std::string> v = IPParserNameSpace::split(line, '\t');
        m_IPPool.push_back(v.at(0));
        ++linesCount;
    }
    std::cout << "Read " << linesCount << " lines of addresses." << "\n";

    // Close the file
    inputFile.close();

    return 0;
};