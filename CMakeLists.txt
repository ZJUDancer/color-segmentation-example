cmake_minimum_required(VERSION 3.5.1)
project(color_segmentation)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-Wall -O2)

# OpenCV
find_package(OpenCV REQUIRED)
message("Using OpenCV: ${OpenCV_INCLUDE_DIRS}")

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

IF(APPLE)
    # Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
    link_directories(/usr/local/lib)
    include_directories(/usr/local/include)
ENDIF()

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    ${OpenCV_LIBS}
)
