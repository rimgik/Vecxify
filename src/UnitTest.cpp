#include "UnitTest.hpp"

UnitTest::UnitTest() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
}

void UnitTest::test1() {
    std::array<std::array<int, 7>, 7>  a{
        {{47,23,11,8,38,17,29},{39,43,31,40,5,20,15},{27,18,48,36,33,2,1},{6,37,21,12,42,30,25},{28,26,9,13,22,46,7},{4,3,14,10,34,16,45},{32,44,24,35,19,41,49}}
    };
    Mat<int, 7, 7> m{a};
    std::array<std::array<int, 7>, 7>  b{
        {{15,39,42,47,9,33,37},{31,24,13,19,2,35,46},{43,4,6,14,28,3,8},{12,32,22,41,45,34,40},{10,11,23,25,27,30,17},{20,38,21,16,5,1,26},{29,44,48,7,18,36,49}}
    };
    Mat<int, 7, 7> m2{b};
    std::array<std::array<int,7>,7> tmp{
        {{3548,5025,5138,4553,2770,4862,5714},{4616,5432,4518,5274,3610,4955,6609},{3858,3312,3297,4623,4162,3917,4313},{4029,4292,3919,3476,2990,4154,5291},{3112,4466,3662,3804,2091,3261,4737},{2840,3566,3789,2272,2692,3275,3997},{5727,7443,6480,5585,4223,6233,8590}}
    };
    assert(m*m2 == (Mat<int, 7, 7>{tmp}));
    m *= m2;
    assert(m == (Mat<int,7,7>{tmp}));
}

void UnitTest::test2() {
    Mat<int, 2, 2> m{{1,2}, {3,4}};
    Mat<int, 2, 2> m2{{10,8}, {11, 3}};
    assert(m + m2 == (Mat<int,2,2>{{11,10}, {14, 7}}) );
    
}

void UnitTest::test3() {
    Mat<int, 3, 3> m{{1,23,1}, {123, 23, 80}, {23, 74, 83}};
    Mat<int, 3, 3> id{{1, 0, 0}, {0,1,0}, {0,0,1}};
    m.identity();
    assert(m == id);
}

void UnitTest::test4() {
    Mat<int, 3, 3> m{{1,23,1}, {123, 23, 80}, {23, 74, 83}};
    m *= 2;
    Mat<int, 3, 3> d{{2,46,2}, {123*2, 23*2, 160}, {23*2, 74*2, 83*2}};
    assert(m == d);
}

void UnitTest::test5() {
    BigInt a{"1"};
    BigInt b{a};
    a = "2";
    assert(a == BigInt{"2"} && b == BigInt{"1"});
}

void UnitTest::test6() {
    Vec<int, 3> v{1, 2, 4};
    Vec<int, 3> v2{2, 2, 4};
    Vec<int, 3> v3{3, 4, 8};
    Vec<int, 3> v4{-2, -2, -4};
    assert(v + v2 == v3);
    assert(v - v3 == v4);
}

void UnitTest::test7() {
    Mat<double, 7, 7> mat{{2,46,2,35,80,36,91},{246,46,115,50,95,76,74},{46,148,166,59,21,15,14},{37,102,169,85,15,71,56},{78,17,108,79,147,4,37},{24,7,17,9,120,38,78},{91,47,72,30,77,13,76}};
    
    double ans = -68883024764348;
    assert(std::abs(ans - mat.determinant()) < .1);
    
    Mat<double, 7, 7> zero{{1,2,3,4,5,6,7},{2,4,6,8,10,12,14},{3,6,9,12,15,18,21},{4,8,12,16,20,24,28},{5,10,15,20,25,30,35},{6,12,18,24,30,36,42},{7,14,21,28,35,42,49}};
    
    assert(zero.determinant() == 0.0);
    assert(determinant(zero) == 0.0);
    
    Mat<double, 2, 2> b{{1,2}, {3,4}};
    assert(std::abs(b.determinant() - (-2.0)) < .1);
    assert(std::abs(determinant(b) - (-2.0)) < .1);
    
    Mat<int, 1, 1> a{{10000}};
    assert(a.determinant() == 10000);
}

void UnitTest::test8() {
    BigInt a{"100"};
    a *= BigInt("100");
    a += BigInt("2309");
    assert(a == BigInt("12309"));
//    std::cout << a << std::endl;
    
}
