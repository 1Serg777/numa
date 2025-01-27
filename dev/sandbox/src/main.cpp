#include <cstdlib>
#include <iostream>

#include "Numa.h"
#include "Vec.hpp"
#include "Vec2.hpp"

void TestNuma();
void TestVec();

int main()
{
    TestNuma();
    TestVec();
    return EXIT_SUCCESS;
}

void TestNuma()
{
    std::cout << "Numa constants\n";

    std::cout << "Pi: " << numa::Pi<float>() << "\n";
    std::cout << "Pi/2: " << numa::PiOverTwo<float>() << "\n";
    std::cout << "2*Pi: " << numa::TwoPi<float>() << "\n";

    std::cout << std::endl;

    std::cout << "Degrees and Radians conversions\n";

    std::cout << "Rad: " << numa::Rad(180.0f) << ", Deg: " << numa::Deg(numa::Pi<float>()) << "\n";
    std::cout << "Rad: " << numa::Rad(90.0f) << ", Deg: " << numa::Deg(numa::PiOverTwo<float>()) << "\n";
    std::cout << "Rad: " << numa::Rad(360.0f) << ", Deg: " << numa::Deg(numa::TwoPi<float>()) << "\n";

    std::cout << std::endl;
}
void TestVec()
{
    // Generic 'Vec' class tests

    numa::Vec<float, 3> origin{ 0.0f };

    numa::Vec<float, 5> positionV5{ 1.0f };
    numa::Vec<float, 3> positionV3{ 0.0f };

    positionV3 = positionV5;
    positionV5 = positionV3;

    numa::Vec<float, 2> uv1 = numa::Vec<float, 3>{ 0.5 };
    numa::Vec<double, 2> uv2 = uv1;
    numa::Vec<int, 2> uv3{ uv2 };

    numa::Vec2 triagUv1{ 0.25f, 1 };
    numa::Vec2 triagUv2{ 0.25f, 0.5 };
    numa::Vec2 triagUv3{ 0.11f, 0.51f };
    
    // numa::Vec<float, 5> sumRes1 = positionV5 + triagUv3; // won't compile!
    // however, the one below will
    numa::Vec<float, 5> sumRes1 = positionV5 + numa::Vec<float, 5>{ triagUv3 };

    // numa::Vec4 positionV4{ 1.0f, 2.0f, 0.5f };
    // numa::Vec4 positionV4 = numa::Vec<float, 4>{ 1.0f, 2.0f, 0.5f, 1.0f };
}