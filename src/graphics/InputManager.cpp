#include "InputManager.hpp"

void InputManager::keyPushed(int key)
{
    keyStates_[key] = true;
}

void InputManager::keyReleased(int key)
{
    keyStates_[key] = false;
}

int InputManager::getKeyState(int key)
{
    return keyStates_[key];
}

std::array<uint8_t, 16> InputManager::toChip8KeyStates()
{
    std::array<uint8_t, 16> keys;
    keys.fill(0);

    keys[0x01] = static_cast<uint8_t>(getKeyState(GLFW_KEY_4));
    keys[0x02] = static_cast<uint8_t>(getKeyState(GLFW_KEY_5));
    keys[0x03] = static_cast<uint8_t>(getKeyState(GLFW_KEY_6));
    keys[0x0c] = static_cast<uint8_t>(getKeyState(GLFW_KEY_7));
    keys[0x04] = static_cast<uint8_t>(getKeyState(GLFW_KEY_R));
    keys[0x05] = static_cast<uint8_t>(getKeyState(GLFW_KEY_T));
    keys[0x06] = static_cast<uint8_t>(getKeyState(GLFW_KEY_Y));
    keys[0x0d] = static_cast<uint8_t>(getKeyState(GLFW_KEY_U));
    keys[0x07] = static_cast<uint8_t>(getKeyState(GLFW_KEY_F));
    keys[0x08] = static_cast<uint8_t>(getKeyState(GLFW_KEY_G));
    keys[0x09] = static_cast<uint8_t>(getKeyState(GLFW_KEY_H));
    keys[0x0e] = static_cast<uint8_t>(getKeyState(GLFW_KEY_J));
    keys[0x0a] = static_cast<uint8_t>(getKeyState(GLFW_KEY_V));
    keys[0x00] = static_cast<uint8_t>(getKeyState(GLFW_KEY_B));
    keys[0x0b] = static_cast<uint8_t>(getKeyState(GLFW_KEY_N));
    keys[0x0f] = static_cast<uint8_t>(getKeyState(GLFW_KEY_M));

    return keys;
}

void InputManager::setMousePosition(double xpos, double ypos)
{
    mousePosition_.xPos = xpos;
    mousePosition_.yPos = ypos;
}

const MousePosition InputManager::getMousePosition()
{
    return mousePosition_;
}