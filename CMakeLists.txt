# A minimum cmake version has to be specified. The installed version can be checked 
# using cmake --version on the command line
cmake_minimum_required(VERSION 3.28.1)

project(msql)

# build something
add_executable(${PROJECT_NAME} src.cc)


