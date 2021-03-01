#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace slog = spdlog;

bool running = true; // forgive me. Will place in class

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        running = false;
        slog::info("Close window event");
    }
    
    if(key == GLFW_KEY_E && action == GLFW_PRESS) {
        glfwSetWindowPos(window, 500, 500);
        slog::info("Move window event");
    }
}

int main() {
    slog::set_pattern("[%H:%M:%S] [%t] [%^%l%$] %v");
    slog::set_level(slog::level::trace);
    slog::info("Start program...");

    /* 
        slog::enable_backtrace(10); // create ring buffer with capacity of 10  messages
        for (int i = 0; i < 100; i++) {
            slog::debug("Backtrace message {}", i); // not logged..
        }
        
        slog::dump_backtrace(); // e.g. if some error happened call this function
    */

    slog::info("Starting window creation...");

    if(!glfwInit())
    {
        const char* desc;
        int code = glfwGetError(&desc);
        slog::error("Failed to init glfw: [{}] {}", code, desc);
        slog::shutdown();
        return 1;
    }

    slog::debug("Adding glfw window hints");
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (window == NULL) 
    {
        const char* desc;
        int code = glfwGetError(&desc);
        slog::error("Failed to create window: [{}] {}", code, desc);
        slog::shutdown();
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    bool err = glewInit() != GLEW_OK;
    if(err) {
        slog::error("Failed to init OpenGL loader");
        slog::shutdown();
        glfwTerminate();
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glfwSetKeyCallback(window, key_callback);
    while(!glfwWindowShouldClose(window) && running) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);


        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    slog::debug("Cleaning up ImGui...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    slog::debug("Destroying window...");
    glfwDestroyWindow(window);
    glfwTerminate();

    slog::info("End of program...");
    slog::shutdown();

    return 0;
}