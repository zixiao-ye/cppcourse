# homework 11 cmake build configuration

# list all the headers of the module
set(MODULE_HEADERS hw11.h)


set(LIBRARY_NAME hw11)
set(EXECUTABLE_NAME runhw11)


add_library(${LIBRARY_NAME} SHARED ${MODULE_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_20)

add_executable(${EXECUTABLE_NAME} run.cpp)
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})

