cmake_minimum_required(VERSION 3.14)
project(PyEditorBr)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES pyEditorBr.hpp pyEditorBr.cpp mainFrame.hpp mainFrame.cpp maps.h)

find_package(wxWidgets REQUIRED COMPONENTS net core base std richtext)

if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

add_executable(PyEditorBr ${SOURCE_FILES})

add_subdirectory(fileEngine)

target_link_libraries(PyEditorBr PUBLIC FileEngine ${wxWidgets_LIBRARIES})

target_include_directories(PyEditorBr PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/fileEngine"
                          )