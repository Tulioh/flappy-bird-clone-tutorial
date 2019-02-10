//
//  ShadersManager.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 05/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "ShadersManager.h"

void ShadersManager::init() {
    m_backgroundShader = std::shared_ptr<Shader>(new Shader("resources/shaders/background.shader"));
    m_birdShader = std::shared_ptr<Shader>(new Shader("resources/shaders/bird.shader"));
    m_pipeShader = std::shared_ptr<Shader>(new Shader("resources/shaders/pipe.shader"));
    m_fadeShader = std::shared_ptr<Shader>(new Shader("resources/shaders/fade.shader"));
}
