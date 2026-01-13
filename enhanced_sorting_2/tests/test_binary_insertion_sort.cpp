#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "binary_insertion_sort.h"
#include <vector>
#include <algorithm>

TEST_CASE("Binary Insertion Sort - empty vector") {
    std::vector<int> vec;
    binary_insertion_sort(vec);
    REQUIRE(vec.empty());
}

TEST_CASE("Binary Insertion Sort - single element") {
    std::vector<int> vec = { 42 };
    binary_insertion_sort(vec);
    REQUIRE(vec.size() == 1);
    REQUIRE(vec[0] == 42);
}

TEST_CASE("Binary Insertion Sort - two elements") {
    std::vector<int> vec1 = { 2, 1 };
    binary_insertion_sort(vec1);
    REQUIRE((vec1[0] == 1 && vec1[1] == 2));

    std::vector<int> vec2 = { 1, 2 };
    binary_insertion_sort(vec2);
    REQUIRE((vec2[0] == 1 && vec2[1] == 2));
}

TEST_CASE("Binary Insertion Sort - already sorted") {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    binary_insertion_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Binary Insertion Sort - reverse sorted") {
    std::vector<int> vec = { 5, 4, 3, 2, 1 };
    binary_insertion_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Binary Insertion Sort - random elements") {
    std::vector<int> vec = { 3, 1, 4, 1, 5, 9, 2, 6 };
    binary_insertion_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Binary Insertion Sort - all equal") {
    std::vector<int> vec(10, 7);
    binary_insertion_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Binary Insertion Sort - with negative numbers") {
    std::vector<int> vec = { -5, 3, -2, 0, 7, -1 };
    binary_insertion_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}