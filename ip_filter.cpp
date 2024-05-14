#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
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

// Custom comparator function to compare IP addresses lexicographically
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

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        std::cout << "You haven't entered a valid file name." << "\n";
        std::cout << "Terminating the application." << "\n";
        return 1;
    }

    if (!std::filesystem::exists(std::string(argv[1])))
    {
        std::cout << "Not a valid file name" << "\n";
        return 1;
    }

    std::vector<std::string> ip_pool;

    // Open and read the file
    {
        std::ifstream inputFile(argv[1]);
        // Check if the file opened successfully
        if (!inputFile.is_open())
        {
            std::cerr << "Error: Unable to open file." << std::endl;
            return 1; // Exit with error
        }
        // Read and print each line from the file
        std::string line;
        auto linesCount{0};
        while (std::getline(inputFile, line))
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(v.at(0));
            ++linesCount;
        }
        std::cout << "Read " << linesCount << " lines of addresses." << "\n";

        // Close the file
        inputFile.close();
    }

    // Sort IP addresses lexicographically
    std::sort(ip_pool.begin(), ip_pool.end(), compareIP);

    // Reverse lexicographically sort
    std::reverse(ip_pool.begin(), ip_pool.end());

    {
        // Filter by first byte and output
        auto firstByte = 1;
        auto filteredByFirstByteIP = filter(ip_pool, firstByte);

        // Print the result
        std::cout << "Filtered by the first byte: " << firstByte << "\n";
        for (auto i{0}; i < filteredByFirstByteIP.size(); ++i)
        {
            std::cout << '\t' << filteredByFirstByteIP[i] << "\n";
        }
    }

    {
        // Filter by first and second bytes and output
        auto firstByte = 46;
        auto secondByte = 70;
        auto filteredByFirstAndSecondBytesIP = filter(ip_pool, firstByte, secondByte);

        // Print the result
        std::cout << "Filtered by the first: " << firstByte << " and second byte: " << secondByte << "\n";
        for (auto i{0}; i < filteredByFirstAndSecondBytesIP.size(); ++i)
        {
            std::cout << '\t' << filteredByFirstAndSecondBytesIP[i] << "\n";
        }
    }

    {
        // Filter by any byte and output
        auto anyByte = 46;
        auto filteredByAnyByte = filter_any(ip_pool, anyByte);

        // Print the result
        std::cout << "Filtered by the byte: " << anyByte << "\n";
        for (auto i{0}; i < filteredByAnyByte.size(); ++i)
        {
            std::cout << '\t' << filteredByAnyByte[i] << "\n";
        }
    }
    return 0;

    try
    {
        std::vector<std::vector<std::string>> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
