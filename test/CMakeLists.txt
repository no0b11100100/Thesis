cmake_minimum_required(VERSION 3.14)

project(Test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

enable_testing()

set(PROJECT_SOURCES
        test_main.cpp
        CaesarTest.cpp
        Vigenere.cpp
        permutation.cpp
        replacement.cpp
)

set( header
    ../include/common/consts.h)

add_definitions(-DGTEST_LANGUAGE_CXX17)
add_executable(Test
  ${PROJECT_SOURCES}
)

target_compile_definitions(Test
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Test
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick gtest)

# add_gtest_test(${PROJECT_NAME} "${sources}" valid_parentheses)


# download test
#include(FetchContent)
#FetchContent_Declare(
#  googletest
#  # Specify the commit you depend on and update it regularly.
#  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
## For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

## Now simply link against gtest or gtest_main as needed. Eg
#add_executable(example example.cpp)
#target_link_libraries(example gtest_main)
#add_test(NAME example_test COMMAND example)
