#include "pch.h"
#include <vector>
#include <deque>
#include "functions_for_tests.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

namespace VectorContainerTests
{
	TEST(VectorContanerTest, Random_int_numbers_test)
	{
		test_random_numbers<std::vector<int>>();
	}
	TEST(VectorContainerTest, Empty_int_container) {
		test_empty_container<std::vector<int>>();
	}
	TEST(VectorContainerTest, All_equal_int_numbers) {
		test_all_equal_numbs<std::vector<int>>();
	}
	TEST(VectorContainerTest, Already_sorted_int_numbs) {
		test_already_sorted_numbs<std::vector<int>>();
	}
	TEST(VectorContainerTest, Reverse_sorted_int_numbs) {
		test_reverse_sorted_numbs<std::vector<int>>();
	}
	TEST(VectorContanerTest, Random_double_numbers_test)
	{
		test_random_numbers<std::vector<double>>();
	}
	TEST(VectorContainerTest, Empty_double_container) {
		test_empty_container<std::vector<double>>();
	}
	TEST(VectorContainerTest, All_equal_double_numbers) {
		test_all_equal_numbs<std::vector<double>>();
	}
	TEST(VectorContainerTest, Already_sorted_double_numbs) {
		test_already_sorted_numbs<std::vector<double>>();
	}
	TEST(VectorContainerTest, Reverse_sorted_double_numbs) {
		test_reverse_sorted_numbs<std::vector<double>>();
	}
}
namespace DequeContainerTests
{
	TEST(DequeContanerTest, Random_int_numbers_test)
	{
		test_random_numbers<std::deque<int>>();
	}
	TEST(DequeContainerTest, Empty_int_container) {
		test_empty_container<std::deque<int>>();
	}
	TEST(DequeContainerTest, All_equal_int_numbers) {
		test_all_equal_numbs<std::deque<int>>();
	}
	TEST(DequeContainerTest, Already_sorted_int_numbs) {
		test_already_sorted_numbs<std::deque<int>>();
	}
	TEST(DequeContainerTest, Reverse_sorted_int_numbs) {
		test_reverse_sorted_numbs<std::deque<int>>();
	}
	TEST(DequeContanerTest, Random_double_numbers_test)
	{
		test_random_numbers<std::deque<double>>();
	}
	TEST(DequeContainerTest, Empty_double_container) {
		test_empty_container<std::deque<double>>();
	}
	TEST(DequeContainerTest, All_equal_double_numbers) {
		test_all_equal_numbs<std::deque<double>>();
	}
	TEST(DequeContainerTest, Already_sorted_double_numbs) {
		test_already_sorted_numbs<std::deque<double>>();
	}
	TEST(DequeContainerTest, Reverse_sorted_double_numbs) {
		test_reverse_sorted_numbs<std::deque<double>>();
	}
}
namespace StringConatainerTests
{
	TEST(StringContainerTest, CharType) {
		_CrtMemState startPoint, endPoint, diff;
		_CrtMemCheckpoint(&startPoint); {
			test<std::string>();
		}_CrtMemCheckpoint(&endPoint);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startPoint, &endPoint)) << "Memory leaks detected";
	}
}
namespace ArrayContainerTests {

	TEST(ArrayContainerTest, IntType) {
		_CrtMemState startPoint, endPoint, diff;
		_CrtMemCheckpoint(&startPoint); {
			array_test<int>();
		}_CrtMemCheckpoint(&endPoint);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startPoint, &endPoint)) << "Memory leaks detected";
	}
	TEST(ArrayContainerTest, UIntType) {
		_CrtMemState startPoint, endPoint, diff;
		_CrtMemCheckpoint(&startPoint); {
			array_test<unsigned int>();
		}_CrtMemCheckpoint(&endPoint);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startPoint, &endPoint)) << "Memory leaks detected";
	}
	TEST(ArrayContainerTest, FloatType) {
		_CrtMemState startPoint, endPoint, diff;
		_CrtMemCheckpoint(&startPoint); {
			array_test<float>();
		}_CrtMemCheckpoint(&endPoint);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startPoint, &endPoint)) << "Memory leaks detected";
	}
	TEST(ArrayContainerTest, DoubleType) {
		_CrtMemState startPoint, endPoint, diff;
		_CrtMemCheckpoint(&startPoint); {
			array_test<double>();
		}_CrtMemCheckpoint(&endPoint);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startPoint, &endPoint)) << "Memory leaks detected";
	}
	TEST(ArrayContainerTest, LongType) {
		_CrtMemState startPoint, endPoint, diff;
		_CrtMemCheckpoint(&startPoint); {
			array_test<long>();
		}_CrtMemCheckpoint(&endPoint);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startPoint, &endPoint)) << "Memory leaks detected";
	}
	TEST(ArrayContainerTest, ULongType) {
		_CrtMemState startPoint, endPoint, diff;
		_CrtMemCheckpoint(&startPoint); {
			array_test<unsigned long>();
		}_CrtMemCheckpoint(&endPoint);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startPoint, &endPoint)) << "Memory leaks detected";
	}
	TEST(ArrayContainerTest, CharType) {
		_CrtMemState startPoint, endPoint, diff;
		_CrtMemCheckpoint(&startPoint); {
			array_test<char>();
		}_CrtMemCheckpoint(&endPoint);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startPoint, &endPoint)) << "Memory leaks detected";
	}
	TEST(ArrayContainerTest, UCharType) {
		_CrtMemState startPoint, endPoint, diff;
		_CrtMemCheckpoint(&startPoint); {
			array_test<unsigned char>();
		}_CrtMemCheckpoint(&endPoint);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startPoint, &endPoint)) << "Memory leaks detected";
	}
}
namespace NonStandartComparatorTests {
	TEST(MainComparator, CompareVectorsSizes) {
		class comparator {
		public:
			bool operator() (int i, int j) { return (i > j); }
		};
		std::vector<int> array;
		for (int i = 0; i < 20; i++)
			array.push_back(rand());
		ParallelAsyncQuickSort::sort(array.begin(), array.end(), comparator());
		for (int i = 0; i < array.size() - 1; i++)
		{
			EXPECT_GT(array[i + 1], array[i]);
		}
	}
}