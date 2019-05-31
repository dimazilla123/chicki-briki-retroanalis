cmake_minimum_required(VERSION 3.1)

project(chiki_briki)
set(CMAKE_CXX_STANDARD 17)

include_directories(src)

set(ANALISATOR_SRC src/analisator.cpp)
set(PLAY_SRC src/play.cpp)
set(LIB_SRC src/state.cpp src/retroanalis.cpp src/dumper.cpp src/print_utils.cpp)

add_library(retroanalis STATIC ${LIB_SRC})
add_executable(analisator ${ANALISATOR_SRC})
add_executable(play ${PLAY_SRC})

target_link_libraries(analisator retroanalis)
target_link_libraries(play retroanalis)
