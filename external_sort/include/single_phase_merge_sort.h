#pragma once

#include <vector>

template <typename T>
void singlePhaseMergeSort(std::vector<T>& arr);

template void singlePhaseMergeSort(std::vector<int>& arr);
template void singlePhaseMergeSort(std::vector<double>& arr);
template void singlePhaseMergeSort(std::vector<float>& arr);