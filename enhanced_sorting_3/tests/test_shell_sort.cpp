#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "shell_sort.h"
#include <vector>
#include <algorithm>

TEST_CASE("Shell Sort - empty vector") {
    std::vector<int> vec;
    shell_sort(vec);
    REQUIRE(vec.empty());
}

TEST_CASE("Shell Sort - single element") {
    std::vector<int> vec = { 42 };
    shell_sort(vec);
    REQUIRE(vec.size() == 1);
    REQUIRE(vec[0] == 42);
}

TEST_CASE("Shell Sort - two elements") {
    std::vector<int> vec1 = { 2, 1 };
    shell_sort(vec1);
    REQUIRE((vec1[0] == 1 && vec1[1] == 2));

    std::vector<int> vec2 = { 1, 2 };
    shell_sort(vec2);
    REQUIRE((vec2[0] == 1 && vec2[1] == 2));
}

TEST_CASE("Shell Sort - already sorted") {
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7 };
    shell_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Shell Sort - reverse sorted") {
    std::vector<int> vec = { 7, 6, 5, 4, 3, 2, 1 };
    shell_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Shell Sort - random elements") {
    std::vector<int> vec = { 12, 34, 54, 2, 3 };
    shell_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Shell Sort - with duplicates") {
    std::vector<int> vec = { 5, 2, 8, 5, 1, 2, 8 };
    shell_sort(vec);
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));
}

TEST_CASE("Shell Sort - different data types") {
    SECTION("Double") {
        std::vector<double> vec = { 3.14, 2.71, 1.41, 1.73, 0.57 };
        shell_sort(vec);
        REQUIRE(std::is_sorted(vec.begin(), vec.end()));
    }

    SECTION("int") {
        std::vector<int> vec = { 234, 123, 55, 7567 };
        shell_sort(vec);
        REQUIRE(std::is_sorted(vec.begin(), vec.end()));
    }
}