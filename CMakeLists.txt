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

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/UI)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Algorithms)

set(PROJECT_SOURCES
        main.cpp

        Models/MainModel.hpp
        Models/DefaultModel.hpp
        Models/ModelWithTables.hpp

        Models/Components/Button.hpp
        Models/Components/Label.hpp
        Models/Components/Table.hpp
        Models/Components/Group.hpp

        Models/TreeView/TreeItem.h
        Models/TreeView/TreeItem.cpp
        Models/TreeView/TreeModel.h
        Models/TreeView/TreeModel.cpp

        common/const.hpp

        Models/NavigationList/List.hpp

        Algorithms/Interface.hpp
        Algorithms/Matrix/matrix.hpp


        Algorithms/XOR/xor.cpp
        Algorithms/XOR/xor.h
        Algorithms/XOR/const.h
        Algorithms/XOR/Impl/xorImpl.cpp
        Algorithms/XOR/Impl/xorImpl.h

        Algorithms/DESes/SDES/SDES.h
        Algorithms/DESes/SDES/SDES.cpp

        UI/qml.qrc
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
