//
//  Level.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 05/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "Level.h"

#include "graphics/ShadersManager.h"

Level::Level()
{
    float verticies[] = {
        -10.0f, -10.0f * 9.0f / 16.0f, 0.0f,
        -10.0f,  10.0f * 9.0f / 16.0f, 0.0f,
          0.0f,  10.0f * 9.0f / 16.0f, 0.0f,
          0.0f, -10.0f * 9.0f / 16.0f, 0.0f
    };
    unsigned int verticesCount = sizeof(verticies);
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int indicesCount = sizeof(indices);
    
    float textureCoordinates[] = {
        0, 1,
        0, 0,
        1, 0,
        1, 1
    };
    unsigned int textureCoordinatesCount = sizeof(textureCoordinates);
    
    m_backgroundVertexArray = std::shared_ptr<VertexArray>(new VertexArray(verticies, verticesCount,
                                                                           indices, indicesCount,
                                                                           textureCoordinates, textureCoordinatesCount));
}

void Level::Render() {
    ShadersManager::getInstance().getBackgroundShader()->Bind();
    m_backgroundVertexArray->Render();
    ShadersManager::getInstance().getBackgroundShader()->Unbind();
}
