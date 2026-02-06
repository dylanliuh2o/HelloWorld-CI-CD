cmake_minimum_required(VERSION 3.10)
project(HelloWorld-CI-CD VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(hello_world src/main.cpp)

# 安装规则（便于打包）
install(TARGETS hello_world DESTINATION bin)