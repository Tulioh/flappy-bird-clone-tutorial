//
//  WindowManager.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 03/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "WindowManager.h"

#include <iostream>
#include <chrono>

#include "math/Matrix4f.h"
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
    
    InputHandler::getInstance().bind(m_window); 
    
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK) {
        std::cout << "Error! Faild to initialize GLEW." << std::endl;
    }
    
    GLCall(glActiveTexture(GL_TEXTURE0 + 0));
    
    Matrix4f pr_matrix = Matrix4f::orthographic(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0, 1.0f);
    
    ShadersManager::getInstance().init();
    ShadersManager::getInstance().getBackgroundShader()->SetUniformMat4f("pr_matrix", pr_matrix);
    ShadersManager::getInstance().getBackgroundShader()->SetUniform1i("u_Texture", 0);
    ShadersManager::getInstance().getBirdShader()->SetUniformMat4f("pr_matrix", pr_matrix);
    ShadersManager::getInstance().getBirdShader()->SetUniform1i("u_Texture", 0);
    
    m_level = std::shared_ptr<Level>(new Level());
}

WindowManager::~WindowManager() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void WindowManager::loop() {
    long lastTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    double delta = 0.0;
    double ns = 1000000000.0 / 60.0;
    long timer = std::chrono::system_clock::now().time_since_epoch().count();
    int updates = 0;
    int frames = 0;
    
    while (!glfwWindowShouldClose(m_window)) {
        long now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        delta += (now - lastTime) / ns;
        lastTime = now;
        
        if (delta >= 1.0) {
            update();
            updates++;
            delta--;
        }
        
        render();
        frames++;
        
        long currentTime = std::chrono::system_clock::now().time_since_epoch().count();
        
        if (currentTime - timer > 1000) {
            timer += 1000;
            updates = 0;
            frames = 0;
        }
    }
}

void WindowManager::update() {
    glfwPollEvents();
    m_level->Update();
}

void WindowManager::render() {
    GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    
    m_level->Render();
           
    glfwSwapBuffers(m_window);
}
