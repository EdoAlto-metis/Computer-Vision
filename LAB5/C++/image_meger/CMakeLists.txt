cmake_minimum_required(VERSION 3.0.0)
project(image_merger)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(image_merger main.cpp)

target_link_libraries(image_merger ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)