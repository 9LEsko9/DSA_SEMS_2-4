#include <catch2/catch_test_macros.hpp>
#include "two_phase_merge_sort.h"
#include <vector>
#include <algorithm>
#include <random>

TEST_CASE("Empty vector") {
    std::vector<int> arr = {};
    twoPhaseMergeSort(arr, 3);
    REQUIRE(arr.empty());
}

TEST_CASE("Single element") {
    std::vector<int> arr = { 5 };
    twoPhaseMergeSort(arr, 3);
    REQUIRE(arr == std::vector<int>{5});
}

TEST_CASE("Already sorted array") {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    std::vector<int> expected = arr;
    twoPhaseMergeSort(arr, 2);
    REQUIRE(arr == expected);
}

TEST_CASE("Reverse sorted array") {
    std::vector<int> arr = { 5, 4, 3, 2, 1 };
    twoPhaseMergeSort(arr, 2);
    REQUIRE(std::is_sorted(arr.begin(), arr.end()));
}

TEST_CASE("Small random array") {
    std::vector<int> arr = { 3, 1, 4, 1, 5, 9, 2, 6 };
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());

    twoPhaseMergeSort(arr);
    REQUIRE(arr == expected);
}

TEST_CASE("Array with duplicates") {
    std::vector<int> arr = { 2, 2, 2, 1, 1, 1, 3, 3, 3 };
    std::vector<int> expected = { 1, 1, 1, 2, 2, 2, 3, 3, 3 };

    twoPhaseMergeSort(arr, 3);
    REQUIRE(arr == expected);
}

TEST_CASE("Block size larger than array") {
    std::vector<int> arr = { 3, 1, 4, 1, 5 };
    twoPhaseMergeSort(arr, 10);
    REQUIRE(std::is_sorted(arr.begin(), arr.end()));
}

TEST_CASE("Block size 1 (обычная сортировка слиянием)") {
    std::vector<int> arr = { 5, 3, 8, 1, 2, 7, 4, 6 };
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());

    twoPhaseMergeSort(arr, 1);
    REQUIRE(arr == expected);
}

TEST_CASE("Block size equal to array size") {
    std::vector<int> arr = { 5, 3, 8, 1, 2, 7, 4, 6 };
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());

    twoPhaseMergeSort(arr, 8);
    REQUIRE(arr == expected);
}

TEST_CASE("Large random array") {
    const size_t size = 100;
    std::vector<int> arr(size);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(-1000, 1000);

    for (auto& x : arr) {
        x = dist(rng);
    }

    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());

    twoPhaseMergeSort(arr, 16);
    REQUIRE(arr == expected);
}

TEST_CASE("Phase1Sort works correctly") {
    std::vector<int> arr = { 5, 3, 8, 1, 2, 7, 4, 6 };

    // Проверяем, что phase1Sort сортирует каждый блок
    phase1Sort(arr, 3);

    // Блок 1: [5,3,8] -> [3,5,8]
    REQUIRE(arr[0] == 3);
    REQUIRE(arr[1] == 5);
    REQUIRE(arr[2] == 8);

    // Блок 2: [1,2,7] -> [1,2,7]
    REQUIRE(arr[3] == 1);
    REQUIRE(arr[4] == 2);
    REQUIRE(arr[5] == 7);

    // Блок 3: [4,6] -> [4,6]
    REQUIRE(arr[6] == 4);
    REQUIRE(arr[7] == 6);
}

TEST_CASE("Phase2Merge works correctly") {
    // Массив с уже отсортированными блоками по 2 элемента
    std::vector<int> arr = { 1, 5, 2, 6, 3, 7, 4, 8 };

    // После phase2Merge весь массив должен быть отсортирован
    phase2Merge(arr, 2);
    REQUIRE(std::is_sorted(arr.begin(), arr.end()));
}

TEST_CASE("Different block sizes produce same result") {
    std::vector<int> arr1 = { 5, 3, 8, 1, 2, 7, 4, 6 };
    std::vector<int> arr2 = { 5, 3, 8, 1, 2, 7, 4, 6 };
    std::vector<int> arr3 = { 5, 3, 8, 1, 2, 7, 4, 6 };

    twoPhaseMergeSort(arr1, 1);
    twoPhaseMergeSort(arr2, 3);
    twoPhaseMergeSort(arr3, 8);

    REQUIRE(arr1 == arr2);
    REQUIRE(arr2 == arr3);
}