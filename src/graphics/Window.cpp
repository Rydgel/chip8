#include <stdexcept>
#include "Window.hpp"

Window::Window(InputManager & im, const int width, const int height, const char *title)
: inputManager_(im)
{
    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window_ = GLFWwindowPtr(glfwCreateWindow(width, height, title, nullptr, nullptr));

    if (window_ == nullptr) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window.");
    }

    glfwMakeContextCurrent(window_.get());
    // VSYNC
    glfwSwapInterval(0);
    // Glad openGL loader
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);
    // don't draw the inside of an element
    glEnable(GL_CULL_FACE);
    // alpha support for textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);

    hideCursor();

    // Setting up viewport to draw inside
    int w, h;
    glfwGetFramebufferSize(window_.get(), &w, &h);
    glViewport(0, 0, w, h);

    // Set the required callback functions
    setupEventCallbacks();
    printGLInfos();
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(window_.get());
}

void Window::pollEvents()
{
    glfwPollEvents();
    // Mouse position
    double xpos, ypos;
    glfwGetCursorPos(window_.get(), &xpos, &ypos);
    inputManager_.setMousePosition(xpos, ypos);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window_.get());
}

void Window::closeWindow()
{
    glfwSetWindowShouldClose(window_.get(), 1);
}

void Window::changeTitle(const char *title)
{
    glfwSetWindowTitle(window_.get(), title);
}

void Window::hideCursor()
{
    glfwSetInputMode(window_.get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::showCursor()
{
    glfwSetInputMode(window_.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::printGLInfos()
{
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));
    printf("GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void Window::setupEventCallbacks()
{
    auto windowRawPtr = window_.get();

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(windowRawPtr, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetWindowUserPointer(windowRawPtr, this);

    glfwSetKeyCallback(windowRawPtr, (GLFWkeyfun) [](auto glfwWindow, auto... params) {
        auto window = static_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
        window->onKeyboardEvent(params...);
    });
}

void Window::onKeyboardEvent(int key, int scancode, int action, int mods)
{
    switch (action) {
        default: break;
        case GLFW_PRESS:
            inputManager_.keyPushed(key);
            break;
        case GLFW_RELEASE:
            inputManager_.keyReleased(key);
            break;
    }
}
