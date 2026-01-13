#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <vector>
#include <algorithm>
#include "single_phase_merge_sort.h"

TEMPLATE_TEST_CASE("Single Phase Merge Sort - Basic Tests",
    "[single_phase_merge_sort]",
    int, double, float) {

    SECTION("Empty vector") {
        std::vector<TestType> arr;
        singlePhaseMergeSort(arr);
        REQUIRE(arr.empty());
    }

    SECTION("Single element") {
        std::vector<TestType> arr = { 42 };
        singlePhaseMergeSort(arr);
        REQUIRE(arr.size() == 1);
        REQUIRE(arr[0] == 42);
    }

    SECTION("Already sorted array") {
        std::vector<TestType> arr = { 1, 2, 3, 4, 5 };
        std::vector<TestType> expected = arr;

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Reverse sorted array") {
        std::vector<TestType> arr = { 5, 4, 3, 2, 1 };
        std::vector<TestType> expected = { 1, 2, 3, 4, 5 };

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Array with duplicates") {
        std::vector<TestType> arr = { 3, 1, 4, 1, 5, 9, 2, 6 };
        std::vector<TestType> expected = arr;
        std::sort(expected.begin(), expected.end());

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }
}

TEMPLATE_TEST_CASE("Single Phase Merge Sort - Edge Cases",
    "[single_phase_merge_sort]",
    int, double, float) {

    SECTION("All elements equal") {
        std::vector<TestType> arr(10, 7);
        std::vector<TestType> expected = arr;

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Negative numbers") {
        std::vector<TestType> arr = { -5, -1, -3, -2, -4 };
        std::vector<TestType> expected = arr;
        std::sort(expected.begin(), expected.end());

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Mixed positive and negative numbers") {
        std::vector<TestType> arr = { -3, 5, 0, -1, 2, -4 };
        std::vector<TestType> expected = arr;
        std::sort(expected.begin(), expected.end());

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }
}

TEMPLATE_TEST_CASE("Single Phase Merge Sort - Performance Scenarios",
    "[single_phase_merge_sort]",
    int, double, float) {

    SECTION("Large array (100 elements)") {
        std::vector<TestType> arr(100);

        // Заполняем обратным порядком
        for (size_t i = 0; i < arr.size(); ++i) {
            arr[i] = static_cast<TestType>(arr.size() - i);
        }

        std::vector<TestType> expected = arr;
        std::sort(expected.begin(), expected.end());

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Power of two size") {
        std::vector<TestType> arr(16);

        for (size_t i = 0; i < arr.size(); ++i) {
            arr[i] = static_cast<TestType>((i * 7) % 13);
        }

        std::vector<TestType> expected = arr;
        std::sort(expected.begin(), expected.end());

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Non-power of two size") {
        std::vector<TestType> arr(17);

        for (size_t i = 0; i < arr.size(); ++i) {
            arr[i] = static_cast<TestType>((i * 5) % 11);
        }

        std::vector<TestType> expected = arr;
        std::sort(expected.begin(), expected.end());

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }
}

TEMPLATE_TEST_CASE("Single Phase Merge Sort - Floating Point Tests",
    "[single_phase_merge_sort]",
    double, float) {

    SECTION("Fractional values") {
        std::vector<TestType> arr = { 3.14, 1.41, 2.71, 0.57 };
        std::vector<TestType> expected = arr;
        std::sort(expected.begin(), expected.end());

        singlePhaseMergeSort(arr);

        // Проверяем, что массив отсортирован
        for (size_t i = 0; i < arr.size() - 1; ++i) {
            REQUIRE(arr[i] <= arr[i + 1]);
        }

        // Проверяем, что все элементы из исходного массива присутствуют
        for (const auto& val : expected) {
            REQUIRE(std::find(arr.begin(), arr.end(), val) != arr.end());
        }
    }

    SECTION("Very small values") {
        std::vector<TestType> arr = { 1e-10, 1e-15, 1e-12, 1e-8 };
        std::vector<TestType> expected = arr;
        std::sort(expected.begin(), expected.end());

        singlePhaseMergeSort(arr);

        for (size_t i = 0; i < arr.size() - 1; ++i) {
            REQUIRE(arr[i] <= arr[i + 1]);
        }
    }

    SECTION("Large and small values mixed") {
        std::vector<TestType> arr = { 1000.5, 0.001, 500.25, 0.0001, 1000.4 };
        std::vector<TestType> expected = arr;
        std::sort(expected.begin(), expected.end());

        singlePhaseMergeSort(arr);

        for (size_t i = 0; i < arr.size() - 1; ++i) {
            REQUIRE(arr[i] <= arr[i + 1]);
        }
    }

    SECTION("Exact equality test for simple values") {
        std::vector<TestType> arr = { 1.0, 2.0, 3.0, 4.0 };
        std::vector<TestType> expected = arr;

        singlePhaseMergeSort(arr);

        REQUIRE(arr == expected);
    }
}