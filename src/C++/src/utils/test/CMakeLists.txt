include(GoogleTest)


if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W0)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror -Og)
endif()

file(GLOB_RECURSE MY_HEADERS "*.h")

add_executable(utils_test 
    main.cpp
    coordinate_2d_test.cpp
    daytime_test.cpp
    general_test.cpp

    ${MY_HEADERS}
)

target_include_directories(
utils_test 

PRIVATE 

${CMAKE_CURRENT_SOURCE_DIR}                 
)

target_link_libraries(
  utils_test
  GTest::gtest_main
  utils
  log
)


