#pragma once

#include <type_traits>
#include <iterator>
#include <vector>
#include <stack>

class QuickSort final
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
	QuickSort() = delete;
	template <typename RandomAccessIterator, typename Compare = std::greater<>>
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
public:
	template <class iter>
	using it_tag = typename std::iterator_traits<iter>::iterator_category;

	template <typename RandomAccessIterator, typename Compare = std::greater<>,
		std::enable_if_t<std::is_base_of_v<std::random_access_iterator_tag, it_tag<RandomAccessIterator>>, int> = 0>
		static void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp = Compare())
	{
		Qsort(first, static_cast<int>(last - first), comp);
	}
};