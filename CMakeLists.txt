cmake_minimum_required(VERSION 3.10)
project(float16)

if(DEFINED ENV{COLCON} AND "$ENV{COLCON}" STREQUAL "1")
  find_package(ament_cmake_auto REQUIRED)

  ament_auto_find_build_dependencies()

  ament_auto_package()
else()
  add_library(${PROJECT_NAME} INTERFACE)

  target_include_directories(${PROJECT_NAME} INTERFACE
      include
  )
endif()