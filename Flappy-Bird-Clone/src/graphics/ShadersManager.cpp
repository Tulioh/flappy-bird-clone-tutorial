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
}
