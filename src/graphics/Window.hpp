#ifndef CHIP8_WINDOW_HPP
#define CHIP8_WINDOW_HPP

#include <glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "InputManager.hpp"


struct Window
{
    struct DestroyglfwWin
    { void operator()(GLFWwindow *ptr) { glfwDestroyWindow(ptr); } };
    using GLFWwindowPtr = std::unique_ptr<GLFWwindow, DestroyglfwWin>;

    Window(InputManager & im, int width, int height, const char *title);

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
    InputManager & inputManager_;
    void setupEventCallbacks();
    void onKeyboardEvent(int key, int scancode, int action, int mods);
};


#endif //CHIP8_WINDOW_HPP
