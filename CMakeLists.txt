
cmake_minimum_required(VERSION 3.10)
project(log_test CXX)

set(spdlog_PATH "${CMAKE_SOURCE_DIR}/vendor/spdlog")
set(glfw3_PATH "${CMAKE_SOURCE_DIR}/vendor/glfw")

if(NOT TARGET spdlog)
    add_subdirectory("${spdlog_PATH}")
endif()

if(NOT TARGET glfw)
    option(GLFW_BUILD_DOCS OFF)
    option(GLFW_BUILD_TESTS OFF)
    option(GLFW_BUILD_EXAMPLES OFF)
    option(GLFW_BUILD_TESTS OFF)
    option(GLFW_INSTALL OFF)
    
    add_subdirectory("${glfw3_PATH}")
    include_directories("${glfw3_PATH}/include")
endif()

file(GLOB main "src/*.cpp")

add_executable(log_test "${main}")

target_link_libraries(log_test PRIVATE spdlog::spdlog)
target_link_libraries(log_test PRIVATE glfw)
