#include "shell_sort.h"

template<typename T>
std::vector<T>& shell_sort(std::vector<T>& data) {
    int n = static_cast<int>(data.size());

    for (int gap = n / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < n; ++i) {
            T temp = std::move(data[i]);
            int j;

            for (j = i; j >= gap && temp < data[j - gap]; j -= gap) {
                data[j] = std::move(data[j - gap]);
            }

            data[j] = std::move(temp);
        }
    }

    return data;
}

template std::vector<int>& shell_sort(std::vector<int>& data);
template std::vector<double>& shell_sort(std::vector<double>& data);
