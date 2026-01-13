add_library(two_phase_merge_sort STATIC src/two_phase_merge_sort.cpp)
target_include_directories(two_phase_merge_sort PUBLIC include)

add_executable(test_two_phase_merge_sort tests/test_two_phase_merge_sort.cpp)
target_link_libraries(test_two_phase_merge_sort 
    PRIVATE two_phase_merge_sort
    Catch2::Catch2WithMain
)
include(Catch)
catch_discover_tests(test_two_phase_merge_sort)

add_library(single_phase_merge_sort STATIC src/single_phase_merge_sort.cpp)
target_include_directories(single_phase_merge_sort PUBLIC include)

add_executable(test_single_phase_merge_sort tests/test_single_phase_merge_sort.cpp)
target_link_libraries(test_single_phase_merge_sort 
    PRIVATE single_phase_merge_sort
    Catch2::Catch2WithMain
)
include(Catch)
catch_discover_tests(test_single_phase_merge_sort)

add_library(natural_merge_sort STATIC src/natural_merge_sort.cpp)
target_include_directories(natural_merge_sort PUBLIC include)

add_executable(test_natural_merge_sort tests/test_natural_merge_sort.cpp)
target_link_libraries(test_natural_merge_sort
    PRIVATE natural_merge_sort
    Catch2::Catch2WithMain
)
include(Catch)
catch_discover_tests(test_natural_merge_sort)



