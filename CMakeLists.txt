cmake_minimum_required(VERSION 3.9)
project(File_Managare)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/window.c
        headers/window.h
        src/file.c
        headers/file.h
        src/editor.c
        headers/editor.h src/manager.c headers/manager.h src/vector.c headers/vector.h)

set(EDITOR ${SOURCE_FILES} src/main_editor.c)
set(MANAGER ${SOURCE_FILES} src/main_manager.c)

add_executable(editor ${EDITOR})
add_executable(File_Manager ${MANAGER})
target_link_libraries(editor m panel ncurses)
target_link_libraries(File_Manager m panel ncurses)