#pragma once
#include "pch.h"
#include "ParallelAsyncQuickSort.hpp"

namespace
{
	const int NUMBER_OF_ELESMS = 1000;
}
template<typename T>
void my_and_expected_result_compare(const T result, const T expected, const T end) {
	auto i = result;
	for (auto j = expected; j != end; ++j) {
		ASSERT_TRUE(i == j);
		++i;
	}
}
template<typename T, typename type>
T create_rand_and_ParallelQuickSort(T& input)
{
	for (int i = 0; i < NUMBER_OF_ELESMS; ++i) {
		input.push_back(static_cast<type>(static_cast<double>(rand()) / RAND_MAX * 1000));
	}
	T res = input;
	ParallelAsyncQuickSort::sort(res.begin(), res.end());
	return res;
}
template<typename T>
void test_empty_container() {
	T input;
	T result;
	T expected;
	expected = input;
	ParallelAsyncQuickSort::sort(result.begin(), result.end());
	std::sort(expected.begin(), expected.end());
	my_and_expected_result_compare(result.begin(), expected.end(), expected.end());
}
template<typename T>
void test_random_numbers() {
	T input;
	auto result = create_rand_and_ParallelQuickSort<T, T::value_type>(input);
	auto expected = input;
	std::sort(expected.begin(), expected.end());
	my_and_expected_result_compare(result.begin(), expected.end(), expected.end());
}
template<typename T>
void test_all_equal_numbs() {
	T input;
	T result;
	for (int i = NUMBER_OF_ELESMS; i > 0; --i) {
		input.push_back(0);
	}
	result = input;
	auto expected = input;
	ParallelAsyncQuickSort::sort(result.begin(), result.end());
	std::sort(expected.begin(), expected.end());
	my_and_expected_result_compare(result.begin(), expected.end(), expected.end());
}
template<typename T>
void test_reverse_sorted_numbs() {
	T input;
	T result;
	T expected;
	expected = input;
	for (auto i = NUMBER_OF_ELESMS; i > 0; --i) {
		input.push_back(i);
	}
	result = input;
	expected = input;
	ParallelAsyncQuickSort::sort(result.begin(), result.end());
	std::sort(expected.begin(), expected.end());
	my_and_expected_result_compare(result.begin(), expected.end(), expected.end());
}
template<typename T>
void test_already_sorted_numbs() {
	T input;
	for (auto i = 0; i < NUMBER_OF_ELESMS; ++i) {
		input.push_back(i);
	}
	auto result = input;
	auto expected = input;
	ParallelAsyncQuickSort::sort(result.begin(), result.end());
	std::sort(expected.begin(), expected.end());
	my_and_expected_result_compare(result.begin(), expected.end(), expected.end());
}
template<typename T>
void test() {
	using typeS = T::value_type;
	test_random_numbers<T>();
	test_empty_container<T>();
	test_all_equal_numbs<T>();
	test_already_sorted_numbs<T>();
	test_reverse_sorted_numbs<T>();
}

template<typename T>
T* create_rand_and_ParallelQuickSort_for_array(T*& input)
{
	input = new T[NUMBER_OF_ELESMS];
	T* res = new T[NUMBER_OF_ELESMS];
	for (int i = 0; i < NUMBER_OF_ELESMS; ++i) {
		res[i] = input[i] = (static_cast<T>(static_cast<double>(rand()) / RAND_MAX * 1000));
	}
	ParallelAsyncQuickSort::sort(&res[0], &res[NUMBER_OF_ELESMS]);
	return res;
}
template<typename T>
void my_and_expected_result_compare_for_array(const T result, const T expected, size_t size_of_array) {
	for (int i = 0; i < size_of_array; ++i) {
		ASSERT_TRUE(result[i] == expected[i]);
	}
}
template<typename T>
void array_test_rand_numb() {
	T* input = nullptr;
	auto* result = create_rand_and_ParallelQuickSort_for_array(input);
	auto* expected = new T[NUMBER_OF_ELESMS];
	memcpy(expected, input, NUMBER_OF_ELESMS * sizeof(T));
	std::sort(&expected[0], &expected[NUMBER_OF_ELESMS]);
	my_and_expected_result_compare_for_array(result, expected, NUMBER_OF_ELESMS);
	delete input;
	delete[] result;
	delete[] expected;
}
template<typename T>
void array_test_empty_array() {
	T* input = nullptr;
	T* result = nullptr;
	T* expected = nullptr;
	ParallelAsyncQuickSort::sort(&result, &result);
	std::sort(&expected, &expected);
	my_and_expected_result_compare_for_array(result, expected, 0);
}
template<typename T>
void array_test_reverse_sorted_numbs() {
	T* input = new T[NUMBER_OF_ELESMS];
	T* result = new T[NUMBER_OF_ELESMS];
	T* expected = new T[NUMBER_OF_ELESMS];
	for (int i = 99; i >= 0; --i) {
		input[i] = i;
	}
	memcpy(result, input, NUMBER_OF_ELESMS * sizeof(T));
	memcpy(expected, input, NUMBER_OF_ELESMS * sizeof(T));
	ParallelAsyncQuickSort::sort(&result[0], &result[NUMBER_OF_ELESMS]);
	std::sort(&expected[0], &expected[NUMBER_OF_ELESMS]);
	my_and_expected_result_compare_for_array(result, expected, 0);
	delete[] input;
	delete[] result;
	delete[] expected;
}
template<typename T>
void array_test_all_equal_numbs() {
	T* input = new T[NUMBER_OF_ELESMS];
	T* result = new T[NUMBER_OF_ELESMS];
	T* expected = new T[NUMBER_OF_ELESMS];
	for (int i = 0; i < NUMBER_OF_ELESMS; ++i) {
		input[i] = 0;
	}
	memcpy(result, input, NUMBER_OF_ELESMS * sizeof(T));
	memcpy(expected, input, NUMBER_OF_ELESMS * sizeof(T));
	ParallelAsyncQuickSort::sort(&result[0], &result[NUMBER_OF_ELESMS]);
	std::sort(&expected[0], &expected[NUMBER_OF_ELESMS]);
	my_and_expected_result_compare_for_array(result, expected, 0);
	delete[] input;
	delete[] result;
	delete[] expected;
}
template<typename T>
void array_test_already_sorted_numbs() {
	T* input = new T[NUMBER_OF_ELESMS];
	T* result = new T[NUMBER_OF_ELESMS];
	T* expected = new T[NUMBER_OF_ELESMS];
	for (int i = 0; i < NUMBER_OF_ELESMS; ++i) {
		input[i] = i;
	}
	memcpy(result, input, NUMBER_OF_ELESMS * sizeof(T));
	memcpy(expected, input, NUMBER_OF_ELESMS * sizeof(T));
	ParallelAsyncQuickSort::sort(&result[0], &result[NUMBER_OF_ELESMS]);
	std::sort(&expected[0], &expected[NUMBER_OF_ELESMS]);
	my_and_expected_result_compare_for_array(result, expected, 0);
	delete[] expected;
	delete[] result;
	delete[] input;
}
template<typename T>
void array_test() {
	array_test_rand_numb<T>();
	array_test_empty_array<T>();
	array_test_all_equal_numbs<T>();
	array_test_already_sorted_numbs<T>();
	array_test_reverse_sorted_numbs<T>();
}