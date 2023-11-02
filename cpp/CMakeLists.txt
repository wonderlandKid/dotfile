cmake_minimum_required(VERSION 3.0)
  
#set(CMAKE_TOOLCHAIN_FILE "/home/liu/code/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")
#set(CMAKE_PREFIX_PATH "/home/liu/code/cpp/vcpkg/installed/x64-linux/share")

project(test)

# find_package(fmt CONFIG REQUIRED)
include_directories(include)

#set(CMAKE_CXX_STANDARD 20)

add_compile_options(-std=c++2b -O2)

add_executable(test test.cpp)

target_link_libraries(test fmt)

