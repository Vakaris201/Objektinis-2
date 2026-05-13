#include <gtest/gtest.h>
#include <sstream>
#include "Studentas.h"

TEST(StudentasTest, DefaultConstructor)
{
	Studentas S;
	EXPECT_EQ(S.test_eilute(), Studentas("Test", "Test", { 0 }, 0).test_eilute());
}
TEST(StudentasTest, ParameterizedConstructor)
{
	Studentas S("Vardenis", "Pavardenis", { 8,9,7 }, 8);
	EXPECT_EQ(S.test_eilute(), Studentas("Vardenis", "Pavardenis", { 8,9,7 }, 8).test_eilute());
}
TEST(StudentasTest, CopyConstructor)
{
	Studentas S1("Vardenis", "Pavardenis", { 8,9,7 }, 8);
	Studentas S2(S1);
	EXPECT_EQ(S1.test_eilute(), S2.test_eilute());
}
TEST(StudentasTest, CopyAssignment)
{
	Studentas S1("Vardenis", "Pavardenis", { 8,9,7 }, 8);
	Studentas S2;
	S2 = S1;
	EXPECT_EQ(S1.test_eilute(), S2.test_eilute());
}
TEST(StudentasTest, MoveConstructor)
{
	Studentas S1("Vardenis", "Pavardenis", { 8,9,7 }, 8);
	Studentas S2(std::move(S1));
	EXPECT_EQ(S2.test_eilute(), Studentas("Vardenis", "Pavardenis", { 8,9,7 }, 8).test_eilute());
	EXPECT_NE(S1.test_eilute(), S2.test_eilute());
}
TEST(StudentasTest, MoveAssignment)
{
	Studentas S1("Vardenis", "Pavardenis", { 8,9,7 }, 8);
	Studentas S2;
	S2 = std::move(S1);
	EXPECT_EQ(S2.test_eilute(), Studentas("Vardenis", "Pavardenis", { 8,9,7 }, 8).test_eilute());
	EXPECT_NE(S1.test_eilute(), S2.test_eilute());
}
TEST(StudentasTest, Getters)
{
	Studentas S("Vardenis", "Pavardenis", { 8,9,7 }, 8);
	EXPECT_STREQ(S.vardas().c_str(), "Vardenis");
	EXPECT_STREQ(S.pavarde().c_str(), "Pavardenis");
	EXPECT_DOUBLE_EQ(S.egzam(), 8.0);
}
TEST(StudentasTest, Destructor)
{
	{
		Studentas S("Vardenis", "Pavardenis", { 8,9,7 }, 8);
	}
	SUCCEED();
}
TEST(StudentasTest, InputOperator)
{
	std::istringstream iss("Vardenis Pavardenis 8 9 7 8");
	Studentas S;
	iss >> S;
	EXPECT_EQ(S.test_eilute(), Studentas("Vardenis", "Pavardenis", { 8,9,7 }, 8).test_eilute());
	EXPECT_DOUBLE_EQ(S.egzam(), 8.0);
}
TEST(StudentasTest, OutputOperator)
{
	Studentas S("Vardenis", "Pavardenis", { 8,9,7 }, 8);
	std::ostringstream oss;
	oss << S;
	std::string expected = "Vardenis       Pavardenis          8.00      ";
	EXPECT_EQ(oss.str(), expected);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
