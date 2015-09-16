# project

project(MML)

cmake_minimum_required(VERSION 2.8.12)



# compil

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -O0 -pg -g3 -ggdb3 -DDEBUG -DMML_STATIC_CHECKING -coverage")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror -O3 -DNDEBUG")

include_directories(include src)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)



# library

file(GLOB_RECURSE CXXFILES src/*.cc)
#add_library(mml STATIC ${CXXFILES})



# tools

file(GLOB_RECURSE INTERSECT_TEST_FILES tools/intersect_test/*.cc tools/common/*.cc)
file(GLOB_RECURSE TILING_DEBUG_FILES   tools/tiling_debug/*.cc   tools/common/*.cc)
file(GLOB_RECURSE TILING_TEST_FILES    tools/tiling_test/*.cc    tools/common/*.cc)
file(GLOB_RECURSE TGA_TEST_FILES       tools/tga_test/*.cc       tools/common/*.cc)

add_executable(intersect_test EXCLUDE_FROM_ALL ${INTERSECT_TEST_FILES})
add_executable(tiling_debug   EXCLUDE_FROM_ALL ${TILING_DEBUG_FILES})
add_executable(tiling_test    EXCLUDE_FROM_ALL ${TILING_TEST_FILES})
add_executable(tga_test       EXCLUDE_FROM_ALL ${TGA_TEST_FILES})

target_include_directories(intersect_test PRIVATE tools/common)
target_include_directories(tiling_debug   PRIVATE tools/common)
target_include_directories(tiling_test    PRIVATE tools/common)
target_include_directories(tga_test       PRIVATE tools/common)

add_custom_target(tools DEPENDS intersect_test tiling_debug tiling_test tga_test)



# tests

file(GLOB_RECURSE TESTFILES check/*.cc)
file(GLOB_RECURSE ANAFILES  src/* include/*)
add_executable(tests ${TESTFILES})
target_link_libraries(tests --coverage)

add_custom_target(run_tests
    COMMAND ./tests
    DEPENDS tests
    COMMENT "running tests")

add_custom_target(run_analysis
    COMMAND ${PROJECT_SOURCE_DIR}/scripts/analysis
            -I ${PROJECT_SOURCE_DIR}/include
            -I ${PROJECT_SOURCE_DIR}/src
            ${ANAFILES}
    COMMENT "running code analysis")

add_custom_target(run_coverage
    COMMAND ${PROJECT_SOURCE_DIR}/scripts/coverage .
            ${PROJECT_SOURCE_DIR}/doc/coverage
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/src
    DEPENDS run_tests
    COMMENT "generating coverage report")

if(CMAKE_BUILD_TYPE MATCHES debug)
  add_custom_target(check DEPENDS run_tests run_analysis run_coverage)
else()
  add_custom_target(check DEPENDS run_tests)
endif()



# install

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/nauths DESTINATION include)
#install(TARGETS mml DESTINATION lib)



# misc

add_custom_target(flower COMMAND cat ${PROJECT_SOURCE_DIR}/scripts/flower)
