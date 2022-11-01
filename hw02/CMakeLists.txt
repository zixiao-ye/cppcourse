add_library(hw02 combinatorics.cpp)

target_include_directories(hw02 PUBLIC "./")
add_executable(runhw02 run.cpp)

target_link_libraries(runhw02 PUBLIC hw02)