cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

project(ServerClient)

add_executable(client src/client.cpp src/socket.cpp)
add_executable(server src/server_main.cpp src/socket.cpp src/server.cpp src/epoll.cpp)

target_include_directories(client PUBLIC include/)
target_include_directories(server PUBLIC include/)
