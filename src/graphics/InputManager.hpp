#ifndef CHIP8_INPUTMANAGER_HPP
#define CHIP8_INPUTMANAGER_HPP

#include <unordered_map>
#include <array>
#include <GLFW/glfw3.h>

struct MousePosition
{
    double xPos = 0;
    double yPos = 0;
};

struct InputManager
{
    void keyPushed(int key);
    void keyReleased(int key);
    int getKeyState(int key);
    std::array<uint8_t, 16> toChip8KeyStates();
    void setMousePosition(double xpos, double ypos);
    const MousePosition getMousePosition();

private:

    std::unordered_map<int, bool> keyStates_ {};
    MousePosition mousePosition_ {};
};


#endif //CHIP8_INPUTMANAGER_HPP
