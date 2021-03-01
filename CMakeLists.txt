
cmake_minimum_required(VERSION 3.10)
project(log_test CXX)

set(spdlog_PATH "${CMAKE_SOURCE_DIR}/vendor/spdlog")
set(glfw3_PATH "${CMAKE_SOURCE_DIR}/vendor/glfw")
set(glew_PATH "${CMAKE_SOURCE_DIR}/vendor/glew-cmake")
set(imgui_PATH "${CMAKE_SOURCE_DIR}/vendor/imgui")

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
endif()

if(NOT TARGET glew)
    add_definitions(-DGLEW_STATIC)
    add_subdirectory("${glew_PATH}")
endif()

if(NOT TARGET imgui)
    add_subdirectory("${imgui_PATH}")
    file(GLOB imgui-backends "${imgui_PATH}/backends/imgui_impl_glfw.cpp" "${imgui_PATH}/backends/imgui_impl_opengl3.cpp")
endif()

file(GLOB main "src/*.cpp")

add_executable(log_test "${main}" "${imgui-backends}")

target_include_directories(log_test PRIVATE "${glfw3_PATH}/include")
target_include_directories(log_test PUBLIC "${imgui_PATH}/backends")
target_include_directories(log_test PUBLIC "${imgui_PATH}")

target_link_libraries(log_test PRIVATE spdlog::spdlog)
target_link_libraries(log_test PRIVATE glfw)
target_link_libraries(log_test PRIVATE libglew_static)
target_link_libraries(log_test PRIVATE imgui)
