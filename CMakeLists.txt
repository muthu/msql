# A minimum cmake version has to be specified. The installed version can be checked 
# using cmake --version on the command line
cmake_minimum_required(VERSION 3.28.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(msql)

# add_subdirectory() function adds the given directory to the build. This given directory should also contain a CMakeLists.txt file
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)
