cmake_minimum_required(VERSION 3.5)

project(CNN_server)

include_directories(${PROJECT_BINARY_DIR}/../include)

link_directories(${PROJECT_BINARY_DIR}/../lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../)
add_executable(Conn_server ./server.cpp)

target_link_libraries(Conn_server wsock32 shared_server)

