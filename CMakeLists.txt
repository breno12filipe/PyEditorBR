cmake_minimum_required(VERSION 3.14)
project(PyEditorBr)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES pyEditorBr.hpp pyEditorBr.cpp mainFrame.hpp mainFrame.cpp)

find_package(wxWidgets REQUIRED COMPONENTS net core base std richtext)

if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

add_executable(PyEditorBr ${SOURCE_FILES})
target_link_libraries(PyEditorBr ${wxWidgets_LIBRARIES})