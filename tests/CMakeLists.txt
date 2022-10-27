include(CTest)
include(doctest)


# helper function to registers tests in homework subdirectories
# usage:
#  add_hw_test(execname libraryame sourcefile.cpp othersource.cpp...)
function(add_hw_test name library)
    add_executable(${name} ${ARGN})

    target_link_libraries(${name} PRIVATE doctest::doctest ${library} pthread)
    target_compile_features(${name} PUBLIC cxx_std_20)

    if(MINGW)
        # windows can be special
        set_target_properties(${name} PROPERTIES COMPILE_FLAGS -Wa,-mbig-obj)
    endif()

    doctest_discover_tests(${name} TEST_PREFIX "${library}_")
endfunction()


add_subdirectory("hw02")
