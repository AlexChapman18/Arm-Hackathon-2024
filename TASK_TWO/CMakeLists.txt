cmake_minimum_required(VERSION 3.22)

project(Task2 LANGUAGES CXX)

add_executable(task src/main.cpp)
target_include_directories(task PUBLIC src)
target_compile_features(task PUBLIC cxx_std_17)


# boost libraries
find_package(Boost 1.74 REQUIRED) 
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(task LINK_PUBLIC ${Boost_LIBRARIES})

