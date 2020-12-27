

#pragma once
#include <type_traits>
#include <iterator>
#include <vector>
#include <stack>
#include <functional>
#include <thread>
#include <future>

class ParallelAsyncQuickSort final
{
	template <typename RandomAccessIterator, typename Compare = std::greater<>>
	static int partition(RandomAccessIterator& arr, const int start_indx, const int end_indx, Compare comp)
	{
		auto end_indx_elem = arr[end_indx];
		int i = (start_indx - 1);

		for (int j = start_indx; j <= end_indx - 1; ++j)
		{
			if (!comp(arr[j], end_indx_elem))
			{
				++i;
				std::swap(arr[i], arr[j]);
			}
		}
		std::swap(arr[i + 1], arr[end_indx]);
		return (i + 1);
	}
	ParallelAsyncQuickSort() = delete;
	template <typename RandomAccessIterator, typename Compare>
	static void Qsort(RandomAccessIterator begin, size_t elements, Compare comp = Compare())
	{
		std::stack<int> stack;
		int start_indx = 0;
		int end_indx = elements - 1;
		if (start_indx > end_indx)
		{
			return;
		}
		stack.push(start_indx);
		stack.push(end_indx);
		while (!stack.empty())
		{
			end_indx = stack.top();
			stack.pop();
			start_indx = stack.top();
			stack.pop();
			int pivot = partition(begin, start_indx, end_indx, comp);
			if (pivot - 1 > start_indx)
			{
				stack.push(start_indx);
				stack.push(pivot - 1);
			}
			if (pivot + 1 < end_indx)
			{
				stack.push(pivot + 1);
				stack.push(end_indx);
			}
		}
	}
	template <typename RandomAccessIterator, typename Compare>
	static void greedySort(RandomAccessIterator first, RandomAccessIterator last, size_t number_of_threads, Compare comp = Compare())
	{
		__int64 input_size = std::distance(first, last);

		size_t part_size = input_size / number_of_threads;
		size_t remainder = input_size % number_of_threads;

		std::vector<size_t> pos_in_array;
		pos_in_array.assign(number_of_threads, 0);
		std::vector<std::iterator_traits<RandomAccessIterator>::value_type> result;
		for (size_t i = 0; i < number_of_threads; ++i) {
			size_t max_size_i = (i != number_of_threads - 1) ? part_size : part_size + remainder;
			while (pos_in_array[i] != max_size_i) {
				bool founded = false;
				size_t pos;
				RandomAccessIterator it;
				for (size_t j = 0; j < number_of_threads; ++j) {
					if (i == j) { continue; }
					size_t max_size_j = (j != number_of_threads - 1) ? part_size : part_size + remainder;
					if (pos_in_array[j] != max_size_j && pos_in_array[i] != max_size_i) {
						if (!founded) {
							it = (first + pos_in_array[i] + i * part_size);
							pos = i;
						}
						if (comp(*it, *(first + pos_in_array[j] + j * part_size))) {
							it = (first + pos_in_array[j] + j * part_size);
							pos = j;
						}
						founded = true;
					}
				}
				if (founded) {
					result.push_back(*it);
					++pos_in_array[pos];
				}
				size_t empty_cont = 0;
				size_t not_empty_pos = 0;
				for (size_t k = 0; k < number_of_threads; ++k) {
					if (pos_in_array[k] == part_size && k != number_of_threads - 1 || pos_in_array[k] == part_size + remainder) ++empty_cont;
					else not_empty_pos = k;
				}
				if (empty_cont == number_of_threads - 1) {
					size_t max_pos = (not_empty_pos != number_of_threads - 1) ? part_size : part_size + remainder;
					while (pos_in_array[not_empty_pos] != max_pos) {
						result.push_back(*(first + pos_in_array[not_empty_pos] + (not_empty_pos)*part_size));
						++pos_in_array[not_empty_pos];
					}
					break;
				}
			}
		}

		auto result_iter = result.begin();
		for (auto it = first; it != last; ++it) {
			*it = *result_iter++;
		}
	}
public:
	template <class iter>
	using it_tag = typename std::iterator_traits<iter>::iterator_category;


	template <typename RandomAccessIterator, typename Compare = std::greater<>,
		std::enable_if_t<std::is_base_of_v<std::random_access_iterator_tag, it_tag<RandomAccessIterator>>, int> = 0>
		static std::future<void> asyncSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp = Compare())
	{
		return std::async(std::launch::async, [&first, &last, &comp]() {ParallelAsyncQuickSort::sort(first, last, comp); });
	}

	template <typename RandomAccessIterator, typename Compare = std::greater<>,
		std::enable_if_t<std::is_base_of_v<std::random_access_iterator_tag, it_tag<RandomAccessIterator>>, int> = 0>
		static void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp = Compare())
	{
		__int64 input_size = std::distance(first, last);
		if (input_size >= 1000000) {
			std::vector<std::future<void>> container;
			size_t number_of_threads = std::thread::hardware_concurrency();
			if (number_of_threads == 0) number_of_threads = 2;

			size_t part_size = input_size / number_of_threads;
			size_t remainder = input_size % number_of_threads;
			for (int i = 0; i < number_of_threads - 1; i++) {
				auto func = [first, &part_size, i, comp]() { Qsort(first + i * part_size, part_size, comp); };
				container.push_back(std::async(std::launch::async, func));
			}
			auto func = [first, number_of_threads, &part_size, &remainder, comp]() { Qsort(first + (number_of_threads - 1) * part_size, part_size + remainder, comp); };
			container.push_back(std::async(std::launch::async, func));

			for (auto& thr : container) {
				thr.wait();
			}
			greedySort(first, last, number_of_threads, comp);
		}
		else
		{
			Qsort(first, input_size, comp);
		}
	}
};
