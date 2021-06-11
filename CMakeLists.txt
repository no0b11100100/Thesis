cmake_minimum_required(VERSION 3.14)

project(Thesis LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

set(PROJECT_SOURCES
        main.cpp
        include/algorithm/CaesarCipher.h
        include/algorithm/Replacement.h
        include/controller.h
        include/algorithm/Vigenere.h
        include/algorithm/Permutation.h
        include/algorithm/RC4.h
        include/algorithm/RSA.h
        include/algorithm/SDES.h
        include/algorithm/AES.h
        include/algorithm/Steganography.h

        src/CaesarCipher.cpp
        src/Replacement.cpp
        src/Vigenere.cpp
        src/Permutation.cpp
        src/RC4.cpp
        src/RSA.cpp
        src/SDES.cpp
        src/AES.cpp
        src/Steganography.cpp
        include/algorithm/Matrix.h

        UI/qml.qrc
        UI/icons/open.png
        UI/icons/close.png
        include/common/consts.h
        include/common/utils.h
        include/Description.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Thesis
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Thesis SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Thesis
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(Thesis
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Thesis
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)


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
