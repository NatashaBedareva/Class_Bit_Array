#include <gtest/gtest.h>
#include "BittArray_test.h"

TEST(TestBitsArray,TestSwap) {
    BitArray d{10,5};
    BitArray d2{15,7};

    d.swap(d2);

    EXPECT_EQ(d.size(), 15);
    EXPECT_EQ(d2.size(), 10);
    EXPECT_TRUE(d.to_string()=="111000000000000");

    BitArray d3{100,5};
    d.swap(d3);
    EXPECT_EQ(d.size(), 100);
    EXPECT_EQ(d3.size(), 15);
    EXPECT_TRUE(d.to_string()=="1010000000000000000000000000000010100000000000000000000000000000101000000000000000000000000000001010");

    BitArray d4{16,0};
    d4.swap(d);

    EXPECT_EQ(d.size(), 16);
    EXPECT_EQ(d4.size(), 100);

}


TEST(TestBitsArray,TestResize) {

    BitArray d{10,5};
    d.resize(40,true);

    EXPECT_EQ(d.size(), 40);
    EXPECT_TRUE(d.to_string()=="1010000000111111111111111111111111111111");


    d.resize(5);
    EXPECT_EQ(d.size(), 5);
    //пограничное значение

    EXPECT_TRUE(d.to_string()=="10100");

    d.resize(36);
    EXPECT_EQ(d.size(), 36);
    d.resize(64);
    EXPECT_EQ(d.size(), 64);
    EXPECT_TRUE(d.to_string()=="1010000000000000000000000000000000000000000000000000000000000000");


    BitArray f {20};
    f.set(5);
    f.set(10);
    f.resize(6);
    f.resize(30,true);
    EXPECT_TRUE(f.to_string()=="000001111111111111111111111111");

    f.resize(64,true);
    EXPECT_TRUE(f.to_string()=="0000011111111111111111111111111111111111111111111111111111111111");


}


TEST(TestBitsArray,TestPushBack) {
    BitArray d{10,5};
    d.push_back(true);

    EXPECT_EQ(d.size(), 11);
    EXPECT_TRUE(d.to_string()=="10100000001");

    d.resize(31);
    d.push_back(true);
    EXPECT_EQ(d.size(), 32);
    EXPECT_TRUE(d.to_string()=="10100000001000000000000000000001");

    //уменьшить размер

    d.resize(3);
    d.push_back(true);
    EXPECT_EQ(d.size(), 4);
    EXPECT_TRUE(d.to_string()=="1011");

}

TEST(TestBitsArray,TestSet) {
    BitArray d{33};
    d.set(3);
    EXPECT_TRUE(d.to_string()=="000100000000000000000000000000000");
    d.set();
    EXPECT_TRUE(d.to_string()=="111111111111111111111111111111111");

    // воторное сет

    d.set();
    EXPECT_TRUE(d.to_string()=="111111111111111111111111111111111");
}

TEST(TestBitsArray,TestReset) {
    BitArray d{10};
    d.set();
    d.reset(5);
    EXPECT_TRUE(d.to_string()=="1111101111");
    d.reset();
    EXPECT_TRUE(d.to_string()=="0000000000");

    //повторный ресет

    d.reset();
    EXPECT_TRUE(d.to_string()=="0000000000");
}

TEST(TestBitsArray,TestAnyNone) {
    BitArray d{10};
    d.set(7);
    EXPECT_FALSE(d.none());
    EXPECT_TRUE(d.any());
    d.reset(7);
    EXPECT_FALSE(d.any());
    EXPECT_TRUE(d.none());
    d.set(7);

    d.resize(5);
    EXPECT_FALSE(d.any());
    EXPECT_TRUE(d.none());
}

TEST(TestBitsArray,TestCount) {
    BitArray d{50};
    d.set(2);
    d.set(10);
    d.set(32);
    d.set(40);
    d.set(45);

    //добавить тесты с ресетом
    EXPECT_EQ(d.count(),5);

    d.resize(5);
    EXPECT_EQ(d.count(),1);
    EXPECT_TRUE(d.to_string()=="00100");

    d.resize(50);
    EXPECT_EQ(d.count(),1);

    d.set(10);
    d.set(32);
    d.set(40);
    d.set(45);

    d.reset(10);
    d.reset(40);
    d.reset(45);
    EXPECT_EQ(d.count(),2);



}

TEST(TestBitsArray,TestEmptyClear) {


    BitArray d{50};

    d.set(2);
    d.set(10);

    d.clear();

    EXPECT_TRUE(d.empty());

    //после ресата

    d.resize(10);
    d.set(5);
    EXPECT_FALSE(d.empty());
    d.set(3);
    EXPECT_FALSE(d.empty());

    d.reset(2);
    d.reset(10);
    d.reset(3);
    d.reset(5);

    EXPECT_FALSE(d.empty());
    d.clear();
    EXPECT_TRUE(d.empty());

}

TEST(TestBitsArray,TestIndex) {
    BitArray d{50};
    d.set(2);
    d.set(10);
    d.set(32);
    d.set(40);
    d.set(45);

    EXPECT_EQ(d[2],1);

    EXPECT_NE(d[0],1); // исп неравенство
    EXPECT_EQ(d[32],1);
}

TEST(TestBitsArray,TestLogicOr) {
    BitArray d{10};
    d.set(2);
    d.set(5);
    d.set(4);
    BitArray d2{10};
    d2.set(4);
    d2.set(7);

    EXPECT_TRUE((d | d2).to_string() == "0010110100");
    EXPECT_FALSE((d | d2).to_string() == "0010111100");
}
//Разбить на тесты логические для логик и присваевания

TEST(TestBitsArray,TestLogicAnd) {
    BitArray d{10};
    d.set(2);
    d.set(5);
    d.set(4);
    BitArray d2{10};
    d2.set(4);
    d2.set(7);

    EXPECT_TRUE((d & d2).to_string() == "0000100000");
}
TEST(TestBitsArray,TestLogicOrAssignment) {
    BitArray d{10};
    d.set(2);
    d.set(5);
    d.set(4);
    BitArray d2{10};
    d2.set(4);
    d2.set(7);

    d|=d2;

    EXPECT_TRUE(d.to_string() == "0010110100");
}

TEST(TestBitsArray,TestLogicAndAssignment) {
    BitArray d{10};
    d.set(2);
    d.set(5);
    d.set(4);
    BitArray d2{10};
    d2.set(4);
    d2.set(7);

    d&=d2;

    EXPECT_TRUE(d.to_string() == "0000100000");
}

TEST(TestBitsArray,TestLogicShiftRight) {
    BitArray d3{35};
    d3.set(31);
    d3.set(2);
    d3.set(3);
    d3.set(10);
    d3.set(34);
    EXPECT_TRUE((d3 >> 3).to_string() == "10000001000000000000000000001001000");
}

TEST(TestBitsArray,TestLogicShiftLeft) {
    BitArray d3{35};
    d3.set(31);
    d3.set(2);
    d3.set(3);
    d3.set(10);
    d3.set(34);
    EXPECT_TRUE((d3 << 5).to_string() == "00000001100000010000000000000000000");
}

TEST(TestBitsArray,TestLogicShiftRightAssignment) {
    BitArray d3{35};
    d3.set(31);
    d3.set(2);
    d3.set(3);
    d3.set(10);
    d3.set(34);
    d3>>=3;
    EXPECT_TRUE(d3.to_string() == "10000001000000000000000000001001000");
}

TEST(TestBitsArray,TestLogicShiftLeftAssignment) {
    BitArray d3{35};
    d3.set(31);
    d3.set(2);
    d3.set(3);
    d3.set(10);
    d3.set(34);

    d3<<=5;
    EXPECT_TRUE(d3.to_string() == "00000001100000010000000000000000000");
}

TEST(TestBitsArray,TestConstructor)
{
    BitArray d{35};
    d.set(10);
    EXPECT_EQ(d.size(),35);
    EXPECT_TRUE(d.to_string()=="00000000001000000000000000000000000");


    BitArray d2{10,5};
    EXPECT_EQ(d2.size(),10);
    EXPECT_TRUE(d2.to_string()=="1010000000");

    BitArray d3 {d};

    EXPECT_EQ(d3.size(),35);
    EXPECT_TRUE(d3.to_string()=="00000000001000000000000000000000000");

    BitArray d0;
    EXPECT_EQ(d0.size(),0);

}


//тест на конструктор


