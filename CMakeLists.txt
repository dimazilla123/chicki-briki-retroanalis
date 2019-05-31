cmake_minimum_required(VERSION 3.1)

project(chiki_briki)
set(CMAKE_CXX_STANDARD 17)

include_directories(src)

set(ANALISATOR_SRC src/retroanalis.cpp src/analisator.cpp)
set(LIB_SRC src/state.cpp src/retroanalis.cpp src/dumper.cpp)

add_library(retroanalis STATIC ${LIB_SRC})
add_executable(analisator ${ANALISATOR_SRC})

target_link_libraries(analisator retroanalis)
