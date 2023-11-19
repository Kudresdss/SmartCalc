cmake_minimum_required(VERSION 3.5)

project(SmartCalculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COVERAGE_COMPILE_FLAGS "--coverage")
set(COVERAGE_LINKER_FLAGS "--coverage")

set(CMAKE_PREFIX_PATH "$ENV{QTDIR}/cmake")
set(CMAKE_PREFIX_PATH "/Users/Ivan/Qt/6.4.2/Src/qtbase/lib/cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROJECT_DIRS
        .
        model
        view
        controller
        qcustomplot
        )

set(TEST_DIRS
        test
        )

set(TEST_EXECUTABLE tests)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)
find_package(GTest REQUIRED)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
        DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_MakeAvailable(googletest)


foreach(dir ${PROJECT_DIRS})
    file(GLOB CC_SOURCES "${dir}/*.cc")
    file(GLOB CPP_SOURCES "${dir}/*.cpp")
    file(GLOB HEADER_SOURCES "${dir}/*.h")
    file(GLOB UI_SOURCES "${dir}/*.ui")
    list(APPEND PROJECT_SOURCES ${CC_SOURCES} ${CPP_SOURCES} ${HEADER_SOURCES} ${UI_SOURCES})
endforeach()

foreach(dir ${TEST_DIRS})
    file(GLOB CC_SOURCES "${dir}/*.cc")
    file(GLOB CPP_SOURCES "${dir}/*.cpp")
    file(GLOB HEADER_SOURCES "${dir}/*.h")
    list(APPEND TEST_SOURCES ${CC_SOURCES} ${CPP_SOURCES} ${HEADER_SOURCES})
endforeach()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
            resources/fonts.qrc
    )
    qt_add_executable(${TEST_EXECUTABLE}
        MANUAL_FINALIZATION
            model/model.cc
        model/model.h
        ${TEST_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES})
    endif()
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/model)
target_include_directories(${TEST_EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/model)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/view)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/controller)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/qcustomplot)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(${TEST_EXECUTABLE} PRIVATE ${GTEST_LIBRARIES} pthread)

target_compile_options(${TEST_EXECUTABLE} PRIVATE ${COVERAGE_COMPILE_FLAGS})
target_link_options(${TEST_EXECUTABLE} PRIVATE ${COVERAGE_LINKER_FLAGS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION ..
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
    qt_finalize_executable(${TEST_EXECUTABLE})
endif()
