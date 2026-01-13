# Статическая библиотека
add_library(binary_insertion_sort STATIC
    src/binary_insertion_sort.cpp
)
target_include_directories(binary_insertion_sort PUBLIC include)

# Тест с Catch2
add_executable(test_binary_insertion_sort 
    tests/test_binary_insertion_sort.cpp
)
target_link_libraries(test_binary_insertion_sort 
    PRIVATE binary_insertion_sort 
    Catch2::Catch2WithMain
)
include(Catch)
catch_discover_tests(test_binary_insertion_sort)

add_library(shaker_sort STATIC src/shaker_sort.cpp)
target_include_directories(shaker_sort PUBLIC include)

add_executable(test_shaker_sort tests/test_shaker_sort.cpp)
target_link_libraries(test_shaker_sort 
    PRIVATE shaker_sort 
    Catch2::Catch2WithMain
)
catch_discover_tests(test_shaker_sort)
