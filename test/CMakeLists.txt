set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cc *.txt)


set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

enable_testing()

add_test(NAME ${BINARY} COMMAND ${BINARY})

# copy .txt files required for cin testing
configure_file(${CMAKE_SOURCE_DIR}/test/insertOneRecord.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

# add to add this to include the .h files from src directory into test code
include_directories(${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest_main)

