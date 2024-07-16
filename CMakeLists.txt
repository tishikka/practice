cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0 LANGUAGES C CXX)

add_executable(game main.cpp)

include(CTest)
enable_testing()

set(SFML_DIR "С:\\SFML-2.6.1\\lib\\cmake\\SFML") 
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED) 
target_link_libraries(game sfml-graphics sfml-audio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
