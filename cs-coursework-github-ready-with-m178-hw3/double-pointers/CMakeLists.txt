cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0135 NEW)  # Set the policy to NEW behavior

function(convert_project_name_to_target_name INPUT OUTPUT)
    # converts EX01-FooBar to "foo_bar".

    # get everything to the right of the last "-".
    string(REGEX REPLACE ".*-(.+)$" "\\1" NO_PREFIX ${INPUT})

    # add underscores
    string(REGEX REPLACE "([a-z])([A-Z])" "\\1_\\2" WITH_UNDERSCORES ${NO_PREFIX})

    # lower case
    string(TOLOWER "${WITH_UNDERSCORES}" TARGET_NAME_LOWER)
    set(${OUTPUT} ${TARGET_NAME_LOWER} PARENT_SCOPE)
endfunction()

project(EX00-DoublePointer)

convert_project_name_to_target_name("${CMAKE_PROJECT_NAME}" EXEC_NAME)
set(TEST_EXEC_NAME "${EXEC_NAME}_unittest")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -Wold-style-cast -Wshadow -Wconversion -Wuninitialized -Wsign-conversion -Wnull-dereference")

add_library(
        ${EXEC_NAME}Lib
        src/${EXEC_NAME}.cc
)
target_include_directories(${EXEC_NAME}Lib PUBLIC include)

add_executable(
        ${EXEC_NAME}
        src/main.cc
)
target_link_libraries(${EXEC_NAME} PRIVATE ${EXEC_NAME}Lib)

# from https://github.com/google/googletest/tree/main/googletest#incorporating-into-an-existing-cmake-project
# and https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        ${EXEC_NAME}_unittest
        src/${TEST_EXEC_NAME}.cc  # sort of a hack to have fewer things to change between projects.
)
target_link_libraries(
        ${TEST_EXEC_NAME}
        GTest::gtest_main
        ${EXEC_NAME}Lib
)

include(GoogleTest)
gtest_discover_tests(${TEST_EXEC_NAME})
