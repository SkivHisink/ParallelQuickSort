#include <iostream>
#include <mutex>
#include <vector>
#include <chrono>
#include "ParallelQuickSort.hpp"
#include "ParallelAsyncQuickSort.hpp"
#include "ParallelAsyncRecursiveQuickSort.hpp"
#include "QuickSort.hpp"

int main() {
	for (int i = 1; i < 9; ++i) {
		std::vector<double> input;
		for (int j = 0; j < pow(10, i); ++j) {
			input.push_back(static_cast<double>(static_cast<double>(rand()) / RAND_MAX * 1000));
		}
		auto input_copy = input;
		auto input_async = input;
		auto input_async_recursive = input;
		auto begin = std::chrono::steady_clock::now();
		ParallelQuickSort::sort(input.begin(), input.end());
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << "The time of Parallel Quick Sort: " << elapsed_ms.count() << " ms for "<< pow(10, i)<<" elements"<<std::endl;
		begin = std::chrono::steady_clock::now();
		QuickSort::sort(input_copy.begin(), input_copy.end());
		end = std::chrono::steady_clock::now();
		elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << "The time of Quick Sort: " << elapsed_ms.count() << " ms for " << pow(10, i) << " elements" << std::endl;
		begin = std::chrono::steady_clock::now();
		ParallelAsyncQuickSort::sort(input_async.begin(), input_async.end());
		end = std::chrono::steady_clock::now();
		elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << "The time of Parallel Async Quick Sort: " << elapsed_ms.count() << " ms for " << pow(10, i) << " elements" << std::endl;begin = std::chrono::steady_clock::now();
		ParallelAsyncRecursiveQuickSort::sort(input_async_recursive.begin(), input_async_recursive.end());
		end = std::chrono::steady_clock::now();
		elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << "The time of Parallel Async Recursive Quick Sort: " << elapsed_ms.count() << " ms for " << pow(10, i) << " elements" << std::endl;
		std::cout << "Done!" << std::endl;
	}
	return 0;
}
