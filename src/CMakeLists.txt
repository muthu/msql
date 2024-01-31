set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cc)

set(SOURCES ${SOURCES})

# create a executable using all the files stored in the ${SOURCES} variable
add_executable(${BINARY}_run ${SOURCES})

# add the src itself as a library so it can be used by the gtest library for testing
add_library(${BINARY}_lib STATIC ${SOURCES})
