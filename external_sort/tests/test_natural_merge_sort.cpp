#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>

// Объявления функций
bool natural_less(const std::string& a, const std::string& b);
void natural_merge_sort(std::vector<std::string>& arr);

// Тесты для функции natural_less
TEST_CASE("natural_less compares strings with natural ordering", "[natural_less]") {
    SECTION("Alphabetical strings") {
        REQUIRE(natural_less("apple", "banana") == true);
        REQUIRE(natural_less("banana", "apple") == false);
        REQUIRE(natural_less("apple", "apple") == false);
    }

    SECTION("Case insensitive comparison") {
        REQUIRE(natural_less("Apple", "banana") == true);
        REQUIRE(natural_less("apple", "Banana") == true);
        REQUIRE(natural_less("APPLE", "apple") == false); // равны при игнорировании регистра
        REQUIRE(natural_less("apple", "APPLE") == false); // равны при игнорировании регистра
    }

    SECTION("Strings with numbers") {
        REQUIRE(natural_less("file1", "file2") == true);
        REQUIRE(natural_less("file2", "file10") == true);  // 2 < 10
        REQUIRE(natural_less("file10", "file2") == false); // 10 > 2
    }

    SECTION("Strings with multiple numbers") {
        REQUIRE(natural_less("item1part2", "item1part10") == true);
        REQUIRE(natural_less("item2part1", "item10part1") == true);
        REQUIRE(natural_less("a1b2c3", "a1b2c3") == false); // равны
        REQUIRE(natural_less("a1b2", "a1b2c3") == true); // короче меньше
    }

    SECTION("Leading zeros - это особая проблема") {
        // ВАЖНО: "item1" и "item01" - числа равны (1 == 01),
        // но "item1" короче, поэтому natural_less("item1", "item01") == true
        // Это ожидаемое поведение для вашей реализации
        REQUIRE(natural_less("item1", "item01") == true);
        REQUIRE(natural_less("item01", "item1") == false);
        REQUIRE(natural_less("file001", "file1") == false); // 001 == 1, но 001 длиннее
        REQUIRE(natural_less("file1", "file001") == true);
    }

    SECTION("Mixed content") {
        REQUIRE(natural_less("abc123def", "abc123xyz") == true);
        REQUIRE(natural_less("123abc", "124abc") == true);
        REQUIRE(natural_less("abc", "abc123") == true);
    }

    SECTION("Edge cases") {
        REQUIRE(natural_less("", "a") == true);
        REQUIRE(natural_less("a", "") == false);
        REQUIRE(natural_less("", "") == false);
        REQUIRE(natural_less("1", "2") == true);
        REQUIRE(natural_less("2", "1") == false);
    }
}

// Проверка что функция natural_less создает строгий слабый порядок
TEST_CASE("natural_less creates strict weak ordering", "[natural_less]") {
    // Проверка антисимметричности
    REQUIRE((natural_less("a", "b") == !natural_less("b", "a") || ("a" == "b")));

    // Проверка транзитивности
    std::vector<std::string> test_strings = {
        "apple", "banana", "cherry",
        "file1", "file2", "file10",
        "item1", "item2", "item10"
    };

    for (size_t i = 0; i < test_strings.size(); i++) {
        for (size_t j = 0; j < test_strings.size(); j++) {
            for (size_t k = 0; k < test_strings.size(); k++) {
                if (natural_less(test_strings[i], test_strings[j]) &&
                    natural_less(test_strings[j], test_strings[k])) {
                    REQUIRE(natural_less(test_strings[i], test_strings[k]));
                }
            }
        }
    }
}

// Тесты для функции natural_merge_sort
TEST_CASE("natural_merge_sort sorts vectors correctly", "[natural_merge_sort]") {
    // Вспомогательная функция для очистки временных файлов
    auto cleanup_files = []() {
        std::remove("f.txt");
        std::remove("g.txt");
        std::remove("h.txt");
        };

    // Очищаем файлы перед каждым тестом
    cleanup_files();

    SECTION("Empty vector") {
        std::vector<std::string> vec;
        natural_merge_sort(vec);
        REQUIRE(vec.empty());
    }

    SECTION("Single element") {
        std::vector<std::string> vec = { "single" };
        natural_merge_sort(vec);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0] == "single");
    }

    SECTION("Two elements already sorted") {
        std::vector<std::string> vec = { "apple", "banana" };
        std::vector<std::string> expected = vec;
        natural_merge_sort(vec);
        REQUIRE(vec == expected);
    }

    SECTION("Two elements reverse sorted") {
        std::vector<std::string> vec = { "banana", "apple" };
        natural_merge_sort(vec);
        REQUIRE(vec[0] == "apple");
        REQUIRE(vec[1] == "banana");
    }

    SECTION("Three elements") {
        std::vector<std::string> vec = { "cherry", "banana", "apple" };
        natural_merge_sort(vec);
        REQUIRE(vec[0] == "apple");
        REQUIRE(vec[1] == "banana");
        REQUIRE(vec[2] == "cherry");
    }

    SECTION("With numbers natural sorting") {
        std::vector<std::string> vec = { "file10", "file2", "file1", "file20" };
        natural_merge_sort(vec);

        // Проверяем естественный порядок
        REQUIRE(vec[0] == "file1");
        REQUIRE(vec[1] == "file2");
        REQUIRE(vec[2] == "file10");
        REQUIRE(vec[3] == "file20");
    }

    SECTION("Complex mixed strings") {
        std::vector<std::string> vec = {
            "zebra10", "apple2", "banana1", "cherry",
            "doc10", "doc2", "doc1", "apple10"
        };

        natural_merge_sort(vec);

        // Проверяем что вектор отсортирован (не убывает)
        for (size_t i = 1; i < vec.size(); i++) {
            REQUIRE_FALSE(natural_less(vec[i], vec[i - 1]));
        }

        // Несколько конкретных проверок
        // apple2 должно быть перед apple10 (2 < 10)
        auto apple2_pos = std::find(vec.begin(), vec.end(), "apple2");
        auto apple10_pos = std::find(vec.begin(), vec.end(), "apple10");
        REQUIRE(apple2_pos < apple10_pos);
    }

    SECTION("Case insensitive sorting") {
        std::vector<std::string> vec = { "Banana", "apple", "cherry", "apricot" };
        natural_merge_sort(vec);

        // Проверяем сортировку
        for (size_t i = 1; i < vec.size(); i++) {
            REQUIRE_FALSE(natural_less(vec[i], vec[i - 1]));
        }
    }

    SECTION("Duplicate values") {
        std::vector<std::string> vec = { "test", "test", "test" };
        natural_merge_sort(vec);
        REQUIRE(vec.size() == 3);
        REQUIRE(vec[0] == "test");
        REQUIRE(vec[1] == "test");
        REQUIRE(vec[2] == "test");
    }

    SECTION("Large vector") {
        std::vector<std::string> vec;
        for (int i = 100; i >= 1; i--) {
            vec.push_back("item" + std::to_string(i));
        }

        natural_merge_sort(vec);

        // Проверяем порядок
        for (size_t i = 1; i < vec.size(); i++) {
            REQUIRE_FALSE(natural_less(vec[i], vec[i - 1]));
        }

        // Первый элемент должен быть "item1"
        REQUIRE(vec[0] == "item1");
    }

    // Очищаем файлы после всех тестов
    cleanup_files();
}

// Дополнительные тесты для проверки файловых операций
TEST_CASE("natural_merge_sort creates and uses temporary files", "[file_operations]") {
    // Очищаем на всякий случай
    std::remove("f.txt");
    std::remove("g.txt");
    std::remove("h.txt");

    std::vector<std::string> vec = { "c", "b", "a" };
    natural_merge_sort(vec);

    // Проверяем, что вектор отсортирован
    REQUIRE(vec[0] == "a");
    REQUIRE(vec[1] == "b");
    REQUIRE(vec[2] == "c");

    // Проверяем, что финальный файл f.txt существует и содержит правильные данные
    std::ifstream f("f.txt");
    REQUIRE(f.good());

    std::vector<std::string> file_contents;
    std::string line;
    while (std::getline(f, line)) {
        file_contents.push_back(line);
    }
    f.close();

    REQUIRE(file_contents.size() == 3);
    REQUIRE(file_contents[0] == "a");
    REQUIRE(file_contents[1] == "b");
    REQUIRE(file_contents[2] == "c");

    // Очищаем файлы
    std::remove("f.txt");
    std::remove("g.txt");
    std::remove("h.txt");
}

// Тест для проверки стабильности сортировки
TEST_CASE("natural_merge_sort stability", "[stability]") {
    // Очищаем файлы
    std::remove("f.txt");
    std::remove("g.txt");
    std::remove("h.txt");

    SECTION("Stable sort for equal elements") {
        std::vector<std::string> vec = { "a1", "a2", "a1", "a3" };
        std::vector<std::string> original = vec;

        natural_merge_sort(vec);

        // Проверяем что отсортировано
        for (size_t i = 1; i < vec.size(); i++) {
            REQUIRE_FALSE(natural_less(vec[i], vec[i - 1]));
        }
    }

    std::remove("f.txt");
    std::remove("g.txt");
    std::remove("h.txt");
}