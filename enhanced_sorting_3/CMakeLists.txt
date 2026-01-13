add_library(quick_sort STATIC src/quick_sort.cpp)
target_include_directories(quick_sort PUBLIC include)

add_executable(test_quick_sort tests/test_quick_sort.cpp)
target_link_libraries(test_quick_sort 
    PRIVATE quick_sort 
    Catch2::Catch2WithMain
)
include(Catch)
catch_discover_tests(test_quick_sort)

add_library(shell_sort STATIC src/shell_sort.cpp)
target_include_directories(shell_sort PUBLIC include)

add_executable(test_shell_sort tests/test_shell_sort.cpp)
target_link_libraries(test_shell_sort 
    PRIVATE shell_sort 
    Catch2::Catch2WithMain
)
catch_discover_tests(test_shell_sort)
