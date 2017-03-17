#ifndef CHIP8_WINDOW_HPP
#define CHIP8_WINDOW_HPP

#include <glad.h>
#include <GLFW/glfw3.h>
#include <memory>


struct Window
{
    struct DestroyglfwWin
    {
        void operator()(GLFWwindow *ptr) { glfwDestroyWindow(ptr); }
    };

    using GLFWwindowPtr = std::unique_ptr<GLFWwindow, DestroyglfwWin>;

    Window(const int width, const int height, const char *title);
    ~Window() = default;

    void pollEvents();
    bool isOpen();
    void swapBuffers();
    void closeWindow();
    void changeTitle(const char *title);
    void hideCursor();
    void showCursor();
    void printGLInfos();

private:

    GLFWwindowPtr window_;
    void setupEventCallbacks();
};


#endif //CHIP8_WINDOW_HPP
