#include "IPParser.h"

int main(int argc, char const *argv[])
{
    if (argc == 1)
        return -1;

    IPParser IPParser{std::string(argv[1])};
    return 0;
};