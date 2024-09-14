cmake_minimum_required(VERSION 3.5)

project(Threadpool)

include_directories(${PROJECT_BINARY_DIR}/../include)

aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC_LIST)
aux_source_directory(${PROJECT_BINARY_DIR}/../ MAIN_LIST)
set(FILE_LIST ${SRC_LIST} ${MAIN_LIST})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../lib)
add_library(threadpool_shared SHARED ${SRC_LIST})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../)
add_executable(threadpool_origin ${FILE_LIST})