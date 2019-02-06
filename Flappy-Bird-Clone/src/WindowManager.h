//
//  WindowManager.hpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 03/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef WindowManager_h
#define WindowManager_h

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "level/Level.h"
#include "graphics/Shader.h"

class WindowManager {
private:
    void render();
    void update();
    
public:
    WindowManager();
    ~WindowManager();
    
    void loop();
    
private:
    GLFWwindow* m_window;
    std::shared_ptr<Level> m_level;
};

#endif /* WindowManager_h */
