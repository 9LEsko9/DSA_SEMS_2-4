#include "quick_sort.h"

template<typename T>
T* Partition(T* start, T* end) {
    T pivot = *end;
    T* i = start;

    for (T* j = start; j < end; ++j) {
        if (*j <= pivot) {
            std::swap(*i, *j);
            ++i;
        }
    }
    std::swap(*i, *end);
    return i;
}

template int* Partition(int* start, int* end);
template double* Partition(double* start, double* end);

template<typename T>
void quick_sort(T* start, T* end) {
    if (start >= end) return;

    T* pivot = Partition(start, end);
    quick_sort(start, pivot - 1);
    quick_sort(pivot + 1, end);
}

template void quick_sort(int* start, int* end);
template void quick_sort(double *start, double* end);
