// tests/test_quick_sort.cpp
#include <catch2/catch_test_macros.hpp>
#include "quick_sort.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

TEST_CASE("Quick Sort - empty array", "[quick_sort]") {
    std::vector<int> empty_vec;
    if (!empty_vec.empty()) {
        quick_sort(empty_vec.data(), empty_vec.data() + empty_vec.size() - 1);
    }
    REQUIRE(empty_vec.empty());

}

TEST_CASE("Quick Sort - single element", "[quick_sort]") {
    int arr[] = { 42 };
    quick_sort(arr, arr);
    REQUIRE(arr[0] == 42);
}

TEST_CASE("Quick Sort - two elements", "[quick_sort]") {
    SECTION("already sorted") {
        int arr[] = { 1, 2 };
        quick_sort(arr, arr + 1);
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
    }

    SECTION("reverse order") {
        int arr[] = { 2, 1 };
        quick_sort(arr, arr + 1);
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
    }
}

TEST_CASE("Quick Sort - multiple elements", "[quick_sort]") {
    SECTION("already sorted") {
        int arr[] = { 1, 2, 3, 4, 5 };
        quick_sort(arr, arr + 4);
        REQUIRE(std::is_sorted(arr, arr + 5));
    }

    SECTION("reverse sorted") {
        int arr[] = { 5, 4, 3, 2, 1 };
        quick_sort(arr, arr + 4);
        REQUIRE(std::is_sorted(arr, arr + 5));
    }

    SECTION("random order") {
        int arr[] = { 3, 1, 4, 1, 5, 9, 2, 6 };
        const int size = sizeof(arr) / sizeof(arr[0]);
        quick_sort(arr, arr + size - 1);
        REQUIRE(std::is_sorted(arr, arr + size));
    }
}

TEST_CASE("Quick Sort - with duplicates", "[quick_sort]") {
    int arr[] = { 5, 2, 8, 5, 1, 2, 8 };
    const int size = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, arr + size - 1);
    REQUIRE(std::is_sorted(arr, arr + size));
}

TEST_CASE("Quick Sort - with negative numbers", "[quick_sort]") {
    int arr[] = { -5, 3, -2, 0, 7, -1 };
    const int size = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, arr + size - 1);
    REQUIRE(std::is_sorted(arr, arr + size));
}

TEST_CASE("Quick Sort - all equal elements", "[quick_sort]") {
    int arr[] = { 7, 7, 7, 7, 7, 7 };
    const int size = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, arr + size - 1);
    REQUIRE(std::all_of(arr, arr + size, [](int x) { return x == 7; }));
}

TEST_CASE("Quick Sort - large array", "[quick_sort]") {
    const int size = 1000;
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    for (int i = 0; i < size; ++i) {
        vec[i] = dis(gen);
    }

    quick_sort(vec.data(), vec.data() + size - 1);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Quick Sort - worst case (sorted)", "[quick_sort]") {
    const int size = 100;
    std::vector<int> vec(size);
    std::iota(vec.begin(), vec.end(), 0);  // 0, 1, 2, ..., 99

    quick_sort(vec.data(), vec.data() + size - 1);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Quick Sort - different data types", "[quick_sort]") {
    SECTION("double") {
        double arr[] = { 3.14, 2.71, 1.41, 1.73, 0.57 };
        const int size = sizeof(arr) / sizeof(arr[0]);
        quick_sort(arr, arr + size - 1);
        REQUIRE(std::is_sorted(arr, arr + size));
    }

    SECTION("int") {
        int arr[] = { 'z', 'a', 'm', 'k', 'd' };
        const int size = sizeof(arr) / sizeof(arr[0]);
        quick_sort(arr, arr + size - 1);
        REQUIRE(std::is_sorted(arr, arr + size));
    }
}

TEST_CASE("Quick Sort - edge cases", "[quick_sort]") {
    SECTION("INT_MIN and INT_MAX") {
        int arr[] = { INT_MAX, 0, INT_MIN, 1, -1 };
        const int size = sizeof(arr) / sizeof(arr[0]);
        quick_sort(arr, arr + size - 1);
        REQUIRE(std::is_sorted(arr, arr + size));
    }

    SECTION("two elements already sorted") {
        int arr[] = { 1, 2 };
        quick_sort(arr, arr + 1);
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
    }

    SECTION("two elements reversed") {
        int arr[] = { 2, 1 };
        quick_sort(arr, arr + 1);
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
    }
}