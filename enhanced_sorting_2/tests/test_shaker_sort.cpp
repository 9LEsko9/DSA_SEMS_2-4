#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "shaker_sort.h"
#include <vector>
#include <algorithm>

TEST_CASE("Shaker Sort - empty vector") {
    std::vector<int> vec;
    shaker_sort(vec);
    REQUIRE(vec.empty());
}

TEST_CASE("Shaker Sort - single element") {
    std::vector<int> vec = { 99 };
    shaker_sort(vec);
    REQUIRE(vec.size() == 1);
    REQUIRE(vec[0] == 99);
}

TEST_CASE("Shaker Sort - two elements") {
    std::vector<int> vec1 = { 2, 1 };
    shaker_sort(vec1);
    REQUIRE((vec1[0] == 1 && vec1[1] == 2));

    std::vector<int> vec2 = { 1, 2 };
    shaker_sort(vec2);
    REQUIRE((vec2[0] == 1 && vec2[1] == 2));
}

TEST_CASE("Shaker Sort - already sorted") {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    shaker_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Shaker Sort - reverse sorted") {
    std::vector<int> vec = { 5, 4, 3, 2, 1 };
    shaker_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Shaker Sort - random elements") {
    std::vector<int> vec = { 64, 34, 25, 12, 22, 11, 90 };
    shaker_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Shaker Sort - with duplicates") {
    std::vector<int> vec = { 5, 2, 8, 2, 5, 1, 8 };
    shaker_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}