cmake_minimum_required(VERSION 3.30)
set(CONAN_HOST_PROFILE riscv64)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

project(riscv64_hello_world)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
add_definitions(-DBOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED -DBOOST_STACKTRACE_USE_ADDR2LINE)

include_directories(
        ${Boost_INCLUDE_DIRS}
)

add_executable(riscv64_hello_world main.cpp)
target_link_libraries(riscv64_hello_world Boost::boost)
