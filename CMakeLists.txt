cmake_minimum_required(VERSION 3.10)
project(float16)

find_package(ament_cmake_auto QUIET)

if(ament_cmake_auto_FOUND)
  ament_auto_find_build_dependencies()

  ament_auto_package()
else()
  add_library(${PROJECT_NAME} INTERFACE)

  target_include_directories(${PROJECT_NAME} INTERFACE
      include
  )

  target_link_libraries(${PROJECT_NAME} INTERFACE
      float16
  )
endif()