cmake_minimum_required(VERSION 3.9)
project(File_Managare)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.c
        src/window.c
        headers/window.h
        src/file.c
        headers/file.h
        src/editor.c
        headers/editor.h)

add_executable(File_Managare ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} m panel ncurses)