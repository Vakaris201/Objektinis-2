#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <list>
#include "Vector.h"

//  Konstruktoriai
TEST(VectorTest, DefaultConstructor)
{
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
    EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorTest, CountValueConstructor)
{
    Vector<int> v(5, 42);
    EXPECT_EQ(v.size(), 5u);
    for(std::size_t i = 0; i < v.size(); i++) 
        EXPECT_EQ(v[i], 42);
	
}

TEST(VectorTest, InitializerListConstructor)
{
    Vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, CopyConstructor)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2(v1);
    EXPECT_EQ(v1.size(), v2.size());
    for(std::size_t i = 0; i < v1.size(); i++)
        EXPECT_EQ(v1[i], v2[i]);
}

TEST(VectorTest, MoveConstructor)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[2], 3);
    EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, RangeConstructor)
{
    std::vector<int> v1 = {10, 20, 30};
    Vector<int> v2(v1.begin(), v1.end());
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 10);
    EXPECT_EQ(v2[2], 30);
}

TEST(VectorTest, RangeConstructorList)
{
    std::list<std::string> list = {"a", "b", "c"};
    Vector<std::string> v(list.begin(), list.end());
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], "a");
    EXPECT_EQ(v[2], "c");
}

//  Priskyrimo operatoriai
TEST(VectorTest, CopyAssignment)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, MoveAssignment)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 1);
    EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, InitializerListAssignment)
{
    Vector<int> v;
    v = {1, 2, 3};
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, AssignCountValue)
{
    Vector<int> v = {1, 2, 3};
    v.assign(4, 10);
    EXPECT_EQ(v.size(), 4u);
    for(std::size_t i = 0; i < v.size(); i++)
        EXPECT_EQ(v[i], 10);
}

TEST(VectorTest, AssignInitializerList)
{
    Vector<int> v = {1, 2, 3};
    v.assign({4, 5, 6, 7});
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[0], 4);
    EXPECT_EQ(v[3], 7);
}

TEST(VectorTest, AssignRange)
{
    std::vector<int> v1 = {10, 20, 30};
    Vector<int> v2 = {1, 2};
    v2.assign(v1.begin(), v1.end());
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 10);
    EXPECT_EQ(v2[2], 30);
}

//  Element access
TEST(VectorTest, At)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(2), 3);
	EXPECT_THROW(v.at(100), std::out_of_range);

}

TEST(VectorTest, AtConst)
{
    const Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.at(0), 1);
	EXPECT_EQ(v.at(2), 3);
    EXPECT_THROW(v.at(100), std::out_of_range);
}

TEST(VectorTest, OperatorBracket)
{
    Vector<int> v = {10, 20, 30};
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[2], 30);
    v[1] = 99;
    EXPECT_EQ(v[1], 99);
}

TEST(VectorTest, OperatorBracketConst)
{
    const Vector<int> v = {10, 20, 30};
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[2], 30);
}

TEST(VectorTest, Front)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.front(), 1);
    v.front() = 99;
    EXPECT_EQ(v[0], 99);
}

TEST(VectorTest, FrontConst)
{
    const Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.front(), 1);
}

TEST(VectorTest, Back)
{
    Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.back(), 3);
    v.back() = 99;
    EXPECT_EQ(v[2], 99);
}

TEST(VectorTest, BackConst)
{
    const Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, Data)
{
    Vector<int> v = {1, 2, 3};
    int* p = v.data();
    EXPECT_EQ(p[0], 1);
    p[0] = 99;
    EXPECT_EQ(v[0], 99);
}

TEST(VectorTest, DataConst)
{
    const Vector<int> v = {1, 2, 3};
    const int* p = v.data();
    EXPECT_EQ(p[0], 1);
}

//  Iteratoriai
TEST(VectorTest, BeginEnd)
{
    Vector<int> v = {1, 2, 3};
    int sum = 0;
    for(auto it = v.begin(); it != v.end(); it++)
        sum += *it;
    EXPECT_EQ(sum, 6);
}

TEST(VectorTest, BeginEndConst)
{
    const Vector<int> v = {1, 2, 3};
    int sum = 0;
    for(auto it = v.begin(); it != v.end(); it++)
        sum += *it;
    EXPECT_EQ(sum, 6);
}

TEST(VectorTest, CbeginCend)
{
    Vector<int> v = {1, 2, 3};
    int sum = 0;
    for(auto it = v.cbegin(); it != v.cend(); it++)
        sum += *it;
    EXPECT_EQ(sum, 6);
}

TEST(VectorTest, RbeginRend)
{
    Vector<int> v = {1, 2, 3};
    std::vector<int> reversed;
    for(auto it = v.rbegin(); it != v.rend(); it++)
        reversed.push_back(*it);
    EXPECT_EQ(reversed[0], 3);
    EXPECT_EQ(reversed[1], 2);
    EXPECT_EQ(reversed[2], 1);
}

TEST(VectorTest, CrbeginCrend)
{
    Vector<int> v = {1, 2, 3};
    std::vector<int> reversed;
    for(auto it = v.crbegin(); it != v.crend(); it++)
        reversed.push_back(*it);
    EXPECT_EQ(reversed[0], 3);
    EXPECT_EQ(reversed[2], 1);
}

TEST(VectorTest, RangeForLoop)
{
    Vector<int> v = {1, 2, 3, 4, 5};
    int sum = 0;
    for(int x : v) sum += x;
    EXPECT_EQ(sum, 15);
}

//  Capacity
TEST(VectorTest, Empty)
{
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    v.push_back(1);
    EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Size)
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 0u);
    v.push_back(1);
    EXPECT_EQ(v.size(), 1u);
    v.push_back(2);
    EXPECT_EQ(v.size(), 2u);
}

TEST(VectorTest, MaxSize)
{
    Vector<int> v;
    EXPECT_GT(v.max_size(), 0u);
}

TEST(VectorTest, Reserve)
{
    Vector<int> v;
    v.reserve(100);
    EXPECT_GE(v.capacity(), 100u);
    EXPECT_EQ(v.size(), 0u);
}

TEST(VectorTest, ReserveSmallerThanCapacity)
{
    Vector<int> v;
    v.reserve(100);
    std::size_t cap = v.capacity();
    v.reserve(10);           
    EXPECT_EQ(v.capacity(), cap);
}

TEST(VectorTest, Capacity)
{
    Vector<int> v;
    EXPECT_EQ(v.capacity(), 0u);
    v.push_back(1);
    EXPECT_GE(v.capacity(), 1u);
}

TEST(VectorTest, ShrinkToFit)
{
    Vector<int> v;
    v.reserve(100);
    v.push_back(1);
    v.push_back(2);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

//  Modifiers
TEST(VectorTest, Clear)
{
    Vector<int> v = {1, 2, 3};
    std::size_t cap = v.capacity();
    v.clear();
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), cap); 
}

TEST(VectorTest, InsertCopyAtBegin)
{
    Vector<int> v = {2, 3, 4};
    auto it = v.insert(v.begin(), 1);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(*it, 1);
}

TEST(VectorTest, InsertCopyAtMiddle)
{
    Vector<int> v = {1, 3, 4};
    v.insert(v.begin() + 1, 2);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertCopyAtEnd)
{
    Vector<int> v = {1, 2, 3};
    v.insert(v.end(), 4);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v.back(), 4);
}

TEST(VectorTest, InsertMoveValue)
{
    Vector<std::string> v = {"a", "c"};
    std::string s = "b";
    v.insert(v.begin() + 1, std::move(s));
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[1], "b");
}

TEST(VectorTest, InsertCountValue)
{
    Vector<int> v = {1, 5};
    v.insert(v.begin() + 1, 3, 99);
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[1], 99);
    EXPECT_EQ(v[2], 99);
    EXPECT_EQ(v[3], 99);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, InsertRange)
{
    Vector<int> v = {1, 5};
    std::vector<int> src = {2, 3, 4};
    v.insert(v.begin() + 1, src.begin(), src.end());
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, InsertInitializerList)
{
    Vector<int> v = {1, 5};
    v.insert(v.begin() + 1, {2, 3, 4});
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, EmplaceMiddle)
{
    Vector<int> v = {1, 3};
    auto it = v.emplace(v.begin() + 1, 2);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(*it, 2);
}

TEST(VectorTest, EmplaceString)
{
    Vector<std::string> v = {"hello", "world"};
    v.emplace(v.begin() + 1, 3, 'x');
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[1], "xxx");
}

TEST(VectorTest, EraseAtPos)
{
    Vector<int> v = {1, 2, 3, 4};
    auto it = v.erase(v.begin() + 1);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(*it, 3);
}

TEST(VectorTest, EraseAtBegin)
{
    Vector<int> v = {1, 2, 3};
    v.erase(v.begin());
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, EraseAtEnd)
{
    Vector<int> v = {1, 2, 3};
    v.erase(v.end() - 1);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, EraseRange)
{
    Vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.erase(v.begin() + 1, v.begin() + 4);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 5);
    EXPECT_EQ(*it, 5);
}

TEST(VectorTest, EraseAll)
{
    Vector<int> v = {1, 2, 3};
    v.erase(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, PushBackCopy)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PushBackMove)
{
    Vector<std::string> v;
    std::string s = "hello";
    v.push_back(std::move(s));
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0], "hello");
    EXPECT_TRUE(s.empty());
}

TEST(VectorTest, EmplaceBack)
{
    Vector<int> v;
    auto& ref = v.emplace_back(42);
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(ref, 42); 
}

TEST(VectorTest, EmplaceBackString)
{
    Vector<std::string> v;
    v.emplace_back(5, 'z'); 
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0], "zzzzz");
}

TEST(VectorTest, PopBack)
{
    Vector<int> v = {1, 2, 3};
    v.pop_back();
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, ResizeSmaller)
{
    Vector<int> v = {1, 2, 3, 4, 5};
    v.resize(3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, ResizeLarger)
{
    Vector<int> v = {1, 2};
    v.resize(5);
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 0);
}

TEST(VectorTest, ResizeLargerWithValue)
{
    Vector<int> v = {1, 2};
    v.resize(5, 99);
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[2], 99);
    EXPECT_EQ(v[4], 99);
}

TEST(VectorTest, ResizeSameSize)
{
    Vector<int> v = {1, 2, 3};
    v.resize(3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, MemberSwap)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {4, 5};
    v1.swap(v2);
    EXPECT_EQ(v1.size(), 2u);
    EXPECT_EQ(v1[0], 4);
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 1);
}

//  Non-member funkcijos
TEST(VectorTest, EqualityOperator)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {1, 2, 3};
    Vector<int> v3 = {1, 2, 4};
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(VectorTest, InequalityOperator)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {1, 2, 4};
    EXPECT_TRUE(v1 != v2);
    EXPECT_FALSE(v1 != v1);
}

TEST(VectorTest, LessThanOperator)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {1, 2, 4};
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(VectorTest, LessThanDifferentSize)
{
    Vector<int> v1 = {1, 2};
    Vector<int> v2 = {1, 2, 3};
    EXPECT_TRUE(v1 < v2);
}

TEST(VectorTest, LessEqualOperator)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {1, 2, 3};
    Vector<int> v3 = {1, 2, 4};
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 <= v3);
    EXPECT_FALSE(v3 <= v1);
}

TEST(VectorTest, GreaterThanOperator)
{
    Vector<int> v1 = {1, 2, 4};
    Vector<int> v2 = {1, 2, 3};
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST(VectorTest, GreaterEqualOperator)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {1, 2, 3};
    Vector<int> v3 = {1, 2, 2};
    EXPECT_TRUE(v1 >= v2);
    EXPECT_TRUE(v1 >= v3);
    EXPECT_FALSE(v3 >= v1);
}

TEST(VectorTest, NonMemberSwap)
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {4, 5};
    swap(v1, v2);
    EXPECT_EQ(v1.size(), 2u);
    EXPECT_EQ(v1[0], 4);
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, GetAllocator)
{
    Vector<int> v;
    auto alloc = v.get_allocator();
    int* p = alloc.allocate(1);
    EXPECT_NE(p, nullptr);
    alloc.deallocate(p, 1);
}

TEST(VectorTest, ConstVectorAccess)
{
    const Vector<int> v = {1, 2, 3};
    EXPECT_EQ(v.front(), 1);
    EXPECT_EQ(v.back(), 3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_FALSE(v.empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}