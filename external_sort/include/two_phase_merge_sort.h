#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>

template<typename T>
void phase1Sort(std::vector<T>& arr, size_t block_size);

template<typename T>
void phase2Merge(std::vector<T>& arr, size_t block_size);

template<typename T>
void twoPhaseMergeSort(std::vector<T>& arr, size_t initial_block_size = 1);

template void phase1Sort(std::vector<int>& arr, size_t block_size);
template void phase1Sort(std::vector<double>& arr, size_t block_size);
template void phase1Sort(std::vector<float>& arr, size_t block_size);

template void phase2Merge(std::vector<int>& arr, size_t block_size);
template void phase2Merge(std::vector<double>& arr, size_t block_size);
template void phase2Merge(std::vector<float>& arr, size_t block_size);

template void twoPhaseMergeSort(std::vector<int>& arr, size_t initial_block_size);
template void twoPhaseMergeSort(std::vector<double>& arr, size_t initial_block_size);
template void twoPhaseMergeSort(std::vector<float>& arr, size_t initial_block_size);