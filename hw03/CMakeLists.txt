
# homework 3 cmake build configuration

# sources to include in the homework library
set(SOURCES contact_list.cpp)

set(LIBRARY_NAME hw03)
set(EXECUTABLE_NAME runhw03)

add_library(${LIBRARY_NAME} SHARED ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_20)

add_executable(${EXECUTABLE_NAME} run.cpp)
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})

