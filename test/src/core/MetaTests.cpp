/**
 *  @autor arssivka
 *  @date 11/28/16
 */


#include "gtest/gtest.h"
#include <list>
#include <functional>
#include <rrc/core/MetaFunctions.h>
#include <rrc/core/MetaGenerators.h>

using namespace rrc::meta;


typedef int fuck;

class MetaTestClassFixture : public ::testing::Test {
public:
    MetaTestClassFixture () = default;
    float getSomeTest(int x, bool y, double z) {
        return 70.0;
    }
};


TEST(MetaTest, FunctionTraits) {
    typedef std::function<void(float, char[4], int)> Function;
    typedef FunctionTraits<Function> Traits;
    bool result = std::is_same<Traits::Result, void>::value;
    EXPECT_TRUE(result);
    bool first = std::is_same<Traits::Arg<0>, float>::value;
    EXPECT_TRUE(first);
    bool second = std::is_same<Traits::Arg<1>, char*>::value;
    EXPECT_TRUE(second);
    bool third = std::is_same<Traits::Arg<2>, fuck>::value;
    EXPECT_TRUE(third);
    size_t count = Traits::count;
    EXPECT_EQ(count, 3);
}

bool func(int) {
    return true;
}


TEST(MetaTest, FuntionTraitsPtr) {
    typedef FunctionTraits<decltype(&func)> Traits;
    bool result = std::is_same<Traits::Result, bool>::value;
    EXPECT_TRUE(result);
    bool first = std::is_same<Traits::Arg<0>, fuck>::value;
    EXPECT_TRUE(first);
    size_t count = Traits::count;
    EXPECT_EQ(count, 1);
}


TEST(MetaTest, ArrayGenerator) {
    auto count = ArrayGenerator<int8_t, 1, 2, 3>::size;
    EXPECT_EQ(count, 3);
    auto array = ArrayGenerator<int8_t, 1, 2, 3>::data;
    std::array<int8_t, 3> val = array;
    EXPECT_TRUE(val == array);
}


TEST(MetaTest, Rename) {
    typedef std::vector<int> a;
    typedef std::list<int> b;
    bool eq = std::is_same<Rename<a, std::list>, b>::value;
    EXPECT_TRUE(eq);
}

TEST(MetaTest, Length) {
    auto len = rrc::meta::Length<fuck, float, double>::value;
    EXPECT_EQ(len, 3);
}


TEST(MetaTest, Size) {
    auto size = Size<std::pair<fuck, float>>::value;
    EXPECT_EQ(size, 2);
}


TEST(MetaTest, PushFront) {
    typedef PushFront<List<float>, fuck> push;
    bool pushed = std::is_same<List<fuck, float>, push>::value;
    EXPECT_TRUE(pushed);
}


TEST(MetaTest, Front) {
    typedef Front<List<float, fuck>> push;
    bool front = std::is_same<float, push>::value;
    EXPECT_TRUE(front);
}


TEST(MetaTest, PopFront) {
    typedef PopFront<List<float, fuck>> push;
    bool front = std::is_same<List<fuck>, push>::value;
    EXPECT_TRUE(front);
}

TEST(MetaTest, TrueFalse) {
    EXPECT_NE(True::value, False::value);
}

TEST(MetaTest, Empty) {
    typedef List<fuck, fuck, fuck, fuck> FUCK;
    typedef List<> EMPTY;
    bool nempty = Empty<FUCK>::value;
    EXPECT_FALSE(nempty);
    bool empty = Empty<EMPTY>::value;
    EXPECT_TRUE(empty);
}

TEST(MetaTest, Clear) {
    typedef Clear<List<fuck,fuck,fuck,fuck>> FUCK;
    bool eq = std::is_same<FUCK, List<>>::value;
    EXPECT_TRUE(eq);
}

template <class A>
using AddPointer = typename std::add_pointer<A>::type;

TEST(MetaTest, Transform) {
    typedef Transform<AddPointer , List<fuck, fuck, fuck>> DIRECTIONAL_FUCK;
    bool same = std::is_same<DIRECTIONAL_FUCK, List<fuck*, fuck*, fuck*>>::value;
    EXPECT_TRUE(same);
}

TEST(MetaTest, Append) {
    typedef Append<List<float>, List<fuck, fuck>, List<fuck, fuck, fuck>> append;
    bool back =std::is_same<List<float, fuck, fuck, fuck, fuck, fuck>, append>::value;
    EXPECT_TRUE(back);
}

TEST(MetaTest, AppendSequence) {
    typedef AppendSequence <IntegralSequence<fuck, 1, 2, 3>, IntegralSequence<fuck, 4, 5, 6>, IntegralSequence<fuck, 7, 8, 9>> append;
    bool back =std::is_same<IntegralSequence<fuck, 1, 2, 3, 4, 5, 6, 7, 8, 9>, append>::value;
    EXPECT_TRUE(back);
}

TEST_F(MetaTestClassFixture, MethodTraits) {
    typedef MethodTraits<decltype(&MetaTestClassFixture::getSomeTest)> Traits;
    bool result = std::is_same<Traits::Result, float>::value;
    EXPECT_TRUE(result);
    bool first = std::is_same<Traits::Arg<0>, fuck>::value;
    EXPECT_TRUE(first);
    bool second = std::is_same<Traits::Arg<1>, bool>::value;
    EXPECT_TRUE(second);
    bool third = std::is_same<Traits::Arg<2>, double>::value;
    EXPECT_TRUE(third);
    size_t count  = Traits::count;
    EXPECT_EQ(3, count);
}

TEST(MetaTest, GetSequence) {
    typedef GetSequence<IntegralSequence<fuck, 1, 2, 3>> list;
    bool eq = std::is_same<list, List<std::integral_constant<fuck>(1), 2, 3>>::value;
}