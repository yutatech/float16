cmake_minimum_required(VERSION 3.10)
project(float16)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    include
)