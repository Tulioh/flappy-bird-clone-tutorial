//
//  WindowManager.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 03/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "WindowManager.h"

#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "graphics/GLDebugger.h"
#include "graphics/ShadersManager.h"
#include "InputHandler.h"
#include "level/Level.h"

const static int WINDOW_WIDTH = 1280;
const static int WINDOW_HEIGHT = 720;

WindowManager::WindowManager()
{
    if (!glfwInit()) {
        std::cout << "Error! Failed to initialize GLFW" << std::endl;
    }
    
    // Configure OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create the Window
    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird Clone", NULL, NULL);
    if (!m_window) {
        std::cout << "Error! Faild to create a Window." << std::endl;
        glfwTerminate();
    }
    
//    const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
//    glfwSetWindowPos(m_window, vidMode->width / 2, vidMode->height / 2);
    
//    InputHandler::getInstance().bind(m_window);
    
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK) {
        std::cout << "Error! Faild to initialize GLEW." << std::endl;
    }
    
    glm::mat4 pr_matrix = glm::ortho<float>(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0, 1.0f);
    
    ShadersManager::getInstance().init();
    ShadersManager::getInstance().getBackgroundShader()->Bind();
    ShadersManager::getInstance().getBackgroundShader()->SetUniformMat4f("pr_matrix", pr_matrix);
    ShadersManager::getInstance().getBackgroundShader()->Unbind();
    
    m_level = std::shared_ptr<Level>(new Level());
}

WindowManager::~WindowManager() {
    glfwTerminate();
}

void WindowManager::loop() {
    while(!glfwWindowShouldClose(m_window)) {
        update();
        render();
    }
}

void WindowManager::update() {
    glfwPollEvents();
    if (InputHandler::getInstance().getPressedKeys()[GLFW_KEY_SPACE] == GLFW_RELEASE) {
        //        std::cout << "FLAP!" << std::endl;
    }
}

void WindowManager::render() {
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    
    m_level->Render();
           
    glfwSwapBuffers(m_window);
}
