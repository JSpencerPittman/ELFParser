cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)

project(ELFParser VERSION 1.0)
set(ELFParser_VERSION 1.0)

add_subdirectory(src)
add_subdirectory(include)

add_executable(${PROJECT_NAME} ${CXX_SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)