cmake_minimum_required(VERSION 3.15)

project(Conn_client)

add_executable(Conn_client ./client.cpp)

target_link_libraries(Conn_client wsock32)