add_library(hw02 combinatorics.cpp)

target_include_directories(hw02 PUBLIC "/Users/yezixiao/Library/CloudStorage/OneDrive-TUM/TUM/22W/concepts of C++ programming/exercises/00000000014B3116_tasks/hw02")

add_executable(runhw02 run.cpp)

target_link_libraries(runhw02 PUBLIC hw02)