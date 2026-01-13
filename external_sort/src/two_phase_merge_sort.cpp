#include "two_phase_merge_sort.h"

// ‘аза 1: ¬нутренн€€ сортировка блоков
template<typename T>
void phase1Sort(std::vector<T>& arr, size_t block_size) {
    auto start = arr.begin();
    while (start != arr.end()) {
        auto end = std::next(start, std::min(block_size,
            static_cast<size_t>(std::distance(start, arr.end()))));
        std::sort(start, end);
        start = end;
    }
}

// ‘аза 2: —ли€ние отсортированных блоков
template<typename T>
void phase2Merge(std::vector<T>& arr, size_t block_size) {
    std::vector<T> temp(arr.size());
    size_t current_block_size = block_size;

    while (current_block_size < arr.size()) {
        auto start = arr.begin();
        auto temp_it = temp.begin();

        while (start != arr.end()) {
            auto middle = std::next(start,
                std::min(current_block_size,
                    static_cast<size_t>(std::distance(start, arr.end()))));

            auto end = std::next(middle,
                std::min(current_block_size,
                    static_cast<size_t>(std::distance(middle, arr.end()))));

            std::merge(start, middle, middle, end, temp_it);

            std::advance(temp_it, std::distance(start, end));
            start = end;
        }

        arr.swap(temp);
        current_block_size *= 2;
    }
}

template<typename T>
void twoPhaseMergeSort(std::vector<T>& arr, size_t initial_block_size) {
    if (arr.size() <= 1) return;

    phase1Sort(arr, initial_block_size);
    phase2Merge(arr, initial_block_size);
}