
cmake_minimum_required(VERSION 3.10)
project(log_test CXX)

add_subdirectory(vendor)

set(imgui_PATH "${CMAKE_SOURCE_DIR}/vendor/imgui")
file(GLOB imgui-backends "${imgui_PATH}/backends/imgui_impl_glfw.cpp" "${imgui_PATH}/backends/imgui_impl_opengl3.cpp")

file(GLOB main "src/*.cpp")

add_executable(log_test "${main}" "${imgui-backends}")

target_include_directories(log_test PRIVATE "${glfw3_PATH}/include")
target_include_directories(log_test PUBLIC "${imgui_PATH}/backends")

target_link_libraries(log_test PRIVATE spdlog::spdlog)
target_link_libraries(log_test PRIVATE glfw)
target_link_libraries(log_test PRIVATE libglew_static)
target_link_libraries(log_test PRIVATE imgui)
