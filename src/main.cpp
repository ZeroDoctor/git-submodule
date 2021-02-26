#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "GLFW/glfw3.h"

namespace slog = spdlog;

bool running = true; // forgive me. Will place in class

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        running = false;
        slog::info("Close window event");
    }
}

int main() {
    std::cout << "start program" << std::endl;

    slog::info("Using spdlog version {}.{}.{}!", SPDLOG_VER_MAJOR, SPDLOG_VER_MAJOR, SPDLOG_VER_PATCH);

    slog::warn("Easy padding in numbers like {:08d}", 12);
    slog::error("Example of an error in spdlog");
    slog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    slog::info("Support for floats {:03.2f}", 1.23456);
    slog::info("Positional args are {1} {0}...", "too", "supported");
    slog::info("{:>8} aligned, {:<8} aligned", "right", "left");

    // Runtime log levels
    slog::set_level(slog::level::info); // Set global log level to info
    slog::debug("This message should not be displayed!");
    slog::set_level(slog::level::trace); // Set specific logger's log level
    slog::debug("This message should be displayed...");

    slog::set_pattern("[%H:%M:%S] [%o] [%^%l%$] [%t] %v");
    slog::info("the start of sleep");

    // Customize msg format for all loggers
    
    slog::info("This an info message with custom format");
    // slog::set_pattern("%+"); // back to default format
    slog::set_level(slog::level::info);

    // Backtrace support
    // Loggers can store in a ring buffer all messages (including debug/trace) for later inspection.
    // When needed, call dump_backtrace() to see what happened:
    slog::enable_backtrace(10); // create ring buffer with capacity of 10  messages
    for (int i = 0; i < 100; i++) {
        slog::debug("Backtrace message {}", i); // not logged..
    }
    // e.g. if some error happened:
    slog::dump_backtrace(); // log them now!

    slog::info("Starting window creation...");

    if(!glfwInit())
    {
        const char* desc;
        int code = glfwGetError(&desc);
        slog::error("Failed to init glfw: [{}] {}", code, desc);
        slog::shutdown();
        return 1;
    }

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

    glfwSetKeyCallback(window, key_callback);
    while(!glfwWindowShouldClose(window) && running) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    slog::debug("Destroying window");
    glfwDestroyWindow(window);
    glfwTerminate();

    slog::info("End of program");
    slog::shutdown();

    return 0;
}