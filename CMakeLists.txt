cmake_minimum_required(VERSION 3.10)
project(SafeThreadQueue)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp 
					${PROJECT_SOURCE_DIR}/*.h 
					${PROJECT_SOURCE_DIR}/*.hpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})