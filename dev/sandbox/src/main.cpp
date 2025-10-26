#include <cstdlib>
#include <iostream>

#include "TestVec.h"
#include "TestMat.h"

#include "Numa.h"

#include "Vec.hpp"
#include "Mat.hpp"

#include "Random.h"
#include "Range.hpp"
#include "Intersect.h"

void TestNuma();

void TestVec();
void TestMat();

void NewVecTest();
void NewMatTest();

int main() {
    TestNuma();

    // TestVec();
    // TestMat();

    NewVecTest();
    NewMatTest();

    return EXIT_SUCCESS;
}

void TestNuma() {
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

void TestVec() {
    // Generic 'Vec' class tests (vectors of non-standard sizes)

    /*
    numa::Vec<int, 3> originInt{0};

    float* originData = origin.Data();
    const float* originDataConst = origin.Data();

    numa::Vec<float, 5> positionV5{ 1.0f };
    numa::Vec<float, 3> positionV3{ 0.0f };

    numa::Vec<float, 8> positionV8 = positionV5;
    numa::Vec<float, 8> positionV8_2{};
    numa::Vec<float, 8> positionV8_3;

    float flRes = float{ 1.0f } + double{ 3.0 };
    // numa::Vec<float, 3> flSumRes1 = positionV3 + numa::Vec<double, 3>{ 1.0 };
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

    // numa::Vec3{ 1.0f } + numa::dVec3{ 2 };

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
    */
}
void TestMat() {
    // Generic 'Mat' class tests

    /*
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

    numa::Mat<float, 8, 9> convConstTest1{ m1 };
    numa::Mat<float, 9, 9> convConstTest2{ m2 };
    numa::Mat<float, 9, 9> convConstTest3{ m3 };

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

    numa::Mat3 orient{ 1.0f };
    numa::Mat3 orient2{
        1.0f
    };
    numa::Mat3 orient3{ scale };

    // Mat4 tests

    numa::Mat4 world{
        numa::Vec4{ 1.0f, 0.0f, 0.0f, 0.0f },
        numa::Vec4{ 0.0f, 1.0f, 0.0f, 0.0f },
        numa::Vec4{ 0.0f, 0.0f, 1.0f, 0.0f },
        numa::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f },
    };

    numa::Mat4 world2{
        numa::Vec4{ numa::Vec3{ 1.0f, 0.0f, 0.0f } },
        numa::Vec4{ numa::Vec3{ 0.0f, 1.0f, 0.0f } },
        numa::Vec4{ numa::Vec3{ 0.0f, 0.0f, 1.0f } },
        numa::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f },
    };

    numa::Mat4 world3{
        numa::Vec4{ numa::Vec3{ 1.0f, 0.0f, 0.0f }, 0.0f },
        numa::Vec4{ numa::Vec3{ 0.0f, 1.0f, 0.0f }, 0.0f },
        numa::Vec4{ numa::Vec3{ 0.0f, 0.0f, 1.0f } },
        numa::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f },
    };
    */

    // Won't compile!
    /*
    numa::Mat4 world4{
        numa::Vec3{ 1.0f, 0.0f, 0.0f },
        numa::Vec3{ 0.0f, 1.0f, 0.0f },
        numa::Vec3{ 0.0f, 0.0f, 1.0f },
        numa::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f },
    };
    numa::Mat4 world4_2{
        numa::Vec3{ 1.0f, 0.0f, 0.0f },
        numa::Vec3{ 0.0f, 1.0f, 0.0f },
        numa::Vec3{ 0.0f, 0.0f, 1.0f },
        numa::Vec3{ 0.0f, 0.0f, 0.0f },
    };
    */

    /*
    numa::Mat4 world5{ orient };

    numa::Mat3 orient6{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    numa::Mat4 world6{
        orient6,
        numa::Vec3{ 0.5f, 0.5, 0.5f }
    };

    numa::Mat<float, 5, 5> world_5_5{ world6 };
    numa::Mat<float, 5, 6> world_5_6{ world6 };
    */
}

void NewVecTest() {
    //
    // Generic 'Vec' class tests (vectors of non-standard sizes)
    //

    numa::Vec<double, 11> vecElevenFl{};

    numa::Vec<float, 5> vecFiveFl{0.0f};
    vecFiveFl += 2;
    vecFiveFl += 0.5;

    numa::Vec<int, 5> vecFiveInt(1);
    vecFiveInt += 0.5;
    vecFiveInt = -vecFiveFl; // -numa::Vec<float, 5> is found first, then the converting constructor is called.

    vecFiveFl += vecFiveInt; // ok, since we know the type of the result and can cast the argument to it.
    // auto vecFive = zeroFiveFl + oneFiveInt; // compile-time error! (types don't match!)

    // Not enough components to initialize a vector of the requested size!
    numa::Vec<float, 9> vecNineFl(vecFiveFl); // the last 4 components will be initialized to 0
    numa::Vec<int, 9> vecNineInt(vecFiveInt); // same as above

    // Matrices needed for tests
    // numa::Mat2 oneMat2(1.0f);
    numa::Mat<float, 2, 2> oneMat2(1.0f);
    numa::Mat3 twoMat3(2.0f);
    numa::Mat4 threeMat4(3.0f);

    //
    // Vec2 tests
    //

    // numa::Vec2 firstCol(oneMat2);

    numa::Vec2 v2(2.0f);
    v2 = test::CreateVec2Float(5.0f);

    //
    // Vec3 tests:
    //

    numa::Vec<float, 3> origin{0.0f};
    origin += 5;
}
void NewMatTest() {
    // TODO:

    //
    // Mat2 test
    //

    numa::Mat2 m2(5.0f);
    numa::Mat2 m2_2 = test::CreateMat2Float(2.0f);
}