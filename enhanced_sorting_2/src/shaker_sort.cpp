#include "shaker_sort.h"

template<typename T>
std::vector<T>& shaker_sort(std::vector<T>& data) {
    if (data.empty() || data.size() == 1) return data;

    auto left = data.begin();
    auto right = std::prev(data.end());
    bool swapped = true;

    while (left < right && swapped) {
        swapped = false;

        // Проход слева направо
        for (auto it = left; it != right; ++it) {
            auto next_it = std::next(it);
            if (*it > *next_it) {
                std::swap(*it, *next_it);
                swapped = true;
            }
        }

        if (!swapped) break;

        --right;  // Последний элемент теперь на своем месте
        swapped = false;

        // Проход справа налево
        for (auto it = right; it != left; --it) {
            auto prev_it = std::prev(it);
            if (*prev_it > *it) {
                std::swap(*prev_it, *it);
                swapped = true;
            }
        }

        ++left;  // Первый элемент теперь на своем месте
    }

    return data;
}

template std::vector<int>& shaker_sort(std::vector<int>& data);
template std::vector<double>& shaker_sort(std::vector<double>& data);