#include <cstdlib>
#include <iostream>

#include "Numa.h"

int main()
{
    std::cout << "Pi: " << numa::Pi<float>() << std::endl;
    return EXIT_SUCCESS;
}