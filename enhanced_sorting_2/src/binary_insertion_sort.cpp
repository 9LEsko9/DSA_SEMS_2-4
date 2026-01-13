#include "binary_insertion_sort.h"
template<typename T>

std::vector<T>& binary_insertion_sort(std::vector<T>& data) {
	if (data.empty() || data.size() <= 1) return data;

	for (auto it = std::next(data.begin()), it_e = data.end(); it < it_e; it++) {
	
		T current = *it;

		// ищем место вставки с помощью 
		// бинарного поиска для [left; right]
		auto left = data.begin();
		auto right = it;

		while (left < right) {
			auto mid = left + std::distance(left, right) / 2;

			if (current < *mid) {
				right = mid;
			}
			else {
				left = mid + 1;
			}
		}


		// сдвигаем массив
		auto insert_it = left;
		auto offset_it = it;

		while (offset_it > insert_it) {
			*offset_it = *(offset_it - 1);
			offset_it--;
		}

		*insert_it = current;

	}

	return data;
}

template std::vector<int>& binary_insertion_sort<int>(std::vector<int>&);
template std::vector<double>& binary_insertion_sort<double>(std::vector<double>&);