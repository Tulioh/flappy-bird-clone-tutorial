//
//  InputHandler.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 03/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "InputHandler.h"

void InputHandler::bind(GLFWwindow* window) {
    glfwSetKeyCallback(window, InputHandler::_glfwKeyCallback);
}

void InputHandler::_glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    InputHandler::getInstance().glfwKeyCallback(window, key, scancode, action, mods);
}

void InputHandler::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    m_pressedKeys[key] = action != GLFW_RELEASE;
}

bool InputHandler::isKeyDown(int keycode) {
    return m_pressedKeys[keycode];
}
