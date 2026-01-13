#include "single_phase_merge_sort.h"

template <typename T>
void singlePhaseMergeSort(std::vector<T>& arr) {
    if (arr.size() <= 1) return;

    // Создаем временный буфер
    std::vector<T> temp(arr.size());

    // Длина текущих серий
    size_t runSize = 1;

    while (runSize < arr.size()) {
        // Проходим по массиву и сливаем пары серий
        for (size_t left = 0; left < arr.size(); left += 2 * runSize) {
            // Границы двух серий для слияния
            size_t mid = std::min(left + runSize, arr.size());
            size_t right = std::min(left + 2 * runSize, arr.size());

            size_t i = left;     // Индекс в первой серии
            size_t j = mid;      // Индекс во второй серии
            size_t k = left;     // Индекс во временном массиве

            // Слияние двух отсортированных серий
            while (i < mid && j < right) {
                if (arr[i] <= arr[j]) {
                    temp[k++] = arr[i++];
                }
                else {
                    temp[k++] = arr[j++];
                }
            }

            // Копируем остатки из первой серии
            while (i < mid) {
                temp[k++] = arr[i++];
            }

            // Копируем остатки из второй серии
            while (j < right) {
                temp[k++] = arr[j++];
            }

            // Копируем объединенную серию обратно в исходный массив
            for (size_t idx = left; idx < right; idx++) {
                arr[idx] = temp[idx];
            }
        }

        // Увеличиваем размер серии в 2 раза
        runSize *= 2;
    }
}