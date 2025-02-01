#include <cstdlib>
#include <iostream>

#include "Numa.h"
#include "Vec.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat.hpp"
#include "Mat2.hpp"

void TestNuma();
void TestVec();
void TestMat();

int main()
{
    TestNuma();
    TestVec();
    TestMat();
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

    float* originData = origin.Data();
    const float* originDataConst = origin.Data();

    numa::Vec<float, 5> positionV5{ 1.0f };
    numa::Vec<float, 3> positionV3{ 0.0f };

    numa::Vec<float, 8> positionV8 = positionV5;
    numa::Vec<float, 8> positionV8_2{};
    numa::Vec<float, 8> positionV8_3;

    float flRes = float{ 1.0f } + double{ 3.0 };
    numa::Vec<float, 3> flSumRes1 = positionV3 + numa::Vec<double, 3>{ 1.0 };
    // numa::Vec<float, 3> flSumRes1 = positionV3 + numa::Vec<double, 4>{ 1.0 }; // won't compile

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
    numa::Vec<float, 15> sumRes2 = positionV5 + numa::Vec<float, 5>{ numa::Vec2{ positionV3 } };

    // Vec2 tests

    numa::Vec2 uv4{ origin };
    numa::Vec2 uv5 = numa::Vec2{ positionV3 };
    numa::Vec2 uv6 = positionV5;
    numa::Vec2 uv7;

    // Vec3 tests

    numa::Vec3 pos1{ positionV5 };
    numa::Vec3 pos2{ numa::Vec<int, 8>{ 2 } };
    numa::Vec3 pos3 = uv4;

    numa::Vec3 nextPos1 = positionV5 + numa::Vec<float, 5>{ uv4 };
    numa::Vec3 nextPos2 = numa::Vec2{ positionV5 } + uv4;

    nextPos2 *= 1;

    // Vec4 tests

    // numa::Vec4 positionV4{ 1.0f, 2.0f, 0.5f };
    // numa::Vec4 positionV4 = numa::Vec<float, 4>{ 1.0f, 2.0f, 0.5f, 1.0f };

    numa::Vec4 posV41{ sumRes2 };
    numa::Vec4 posV42{ numa::Vec<int, 11>{ 5.0 } };
    numa::Vec4 posV43 = triagUv1;

    numa::Vec4 posMul1 = nextPos1 * nextPos2;
    posMul1 *= posV42;

    numa::Vec4 nextPosV41 = positionV5 + numa::Vec<float, 5>{ uv4 };
    numa::Vec4 nextPosV42 = numa::Vec2{ positionV5 } + uv4;

    // Additional tests

    // numa::Vec3 sumRes = numa::Vec3{ 1.0f } + numa::Vec2{ 2.5f }; // won't compile!
    numa::Vec3 sumRes = numa::Vec3{ 1.0f } + numa::Vec3{ numa::Vec2{ 2.5f } };

    numa::Vec3{ 1.0f } + numa::dVec3{ 2 };

    numa::Vec2 imgUv{ 0.25, 0.15 };

    numa::Vec3 pos = imgUv;
    pos.z = -2;

    // numa::Vec4 posH = numa::Vec4{ pos };
    // or
    numa::Vec4 posH = pos;
    posH.w = 1.0f;

    // Should add this feature!
    numa::Vec4 posH2 = numa::Vec4{ pos, 1.0f };
    numa::Vec4 posH3{ imgUv, 0.0f, 1 };
}
void TestMat()
{
    // Generic 'Mat' class tests

    numa::Mat<float, 3, 5> m1{ 1 };
    numa::Mat<int, 3, 5> m2{ 1.0f };
    numa::Mat<int, 3, 3> m3{ 1.0f };
    numa::Mat<int, 3, 5> m2_2;
    numa::Mat<int, 3, 3> m3_2;

    numa::Mat<float, 3, 5> m1m2addRes = m1 + m2;
    numa::Mat<double, 3, 5> m1m2addRes2 = m1 + m2;

    numa::Mat<float, 3, 5> m1m2subRes1 = numa::Mat<float, 3, 5>{ m1 - m2 };
    numa::Mat<double, 3, 5> m1m2subRes2 = m1 - m2;

    m1m2addRes2 += m1m2addRes;
    m1m2addRes2 -= m1m2addRes;

    numa::Mat<float, 2, 3> matMult{ 2 };
    numa::Mat<float, 3, 4> matMultRes1 = matMult * 2;
    numa::Mat<float, 5, 6> matMultRes2 = 4 * matMult;
    numa::Mat<float, 7, 8> matMultRes3 = (matMult * 4) / 2;

    // Mat2 tests

    numa::Mat2 m2I{ 1.0f };

    numa::Mat2 scale = 2.0f * m2I;
    scale = m2I * 4.0f;
    scale = scale / 2;

    // Implicit conversion check

    double dv{ 2.0 };
    int iv{ 1 };
    auto av = iv + dv;

    // Mat3 tests

    // TODO

    // Mat4 tests

    // TODO
}