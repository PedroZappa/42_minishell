#include <gtest/gtest.h>

TEST(Tests, TestTest)
{
	EXPECT_TRUE(true);
}

int	main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return (RUN_ALL_TESTS());
}
