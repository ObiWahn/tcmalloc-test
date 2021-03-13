cmake_minimum_required(VERSION 3.18)
project(test_proj CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

add_subdirectory(tcmalloc)

# normal
add_executable(testapp test.cpp)

## tcmalloc
add_executable(testapp_tc test.cpp)
target_link_libraries(testapp_tc PRIVATE tcmalloc::always)

## tcmalloc - dump stats
add_executable(testapp_tc_stat test.cpp)
target_link_libraries(testapp_tc_stat PRIVATE tcmalloc::always)
target_compile_definitions(testapp_tc_stat PUBLIC TC)


## tcmalloc - gperftools - dump stats
set(CMAKE_PREFIX_PATH /usr/local/gperftools)
find_package(PkgConfig REQUIRED)
pkg_check_modules(TC REQUIRED IMPORTED_TARGET libtcmalloc)

add_executable(testapp_tc_stat2 test.cpp)
target_link_libraries(testapp_tc_stat2 PRIVATE PkgConfig::TC )
target_compile_definitions(testapp_tc_stat2 PUBLIC TC2)
