//
//  Level.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 05/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "Level.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "graphics/ShadersManager.h"

Level::Level()
    : m_xScroll(0), m_map(0)
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
    m_backgroundTexture = std::shared_ptr<Texture>(new Texture("resources/textures/bg.jpg"));
    m_bird = std::shared_ptr<Bird>(new Bird());
}

void Level::Update() {
    m_xScroll--;
    
    if (-m_xScroll % 335 == 0) {
        m_map++;
    }
    
    m_bird->Update();
}

void Level::Render() {
    m_backgroundTexture->Bind();
    ShadersManager::getInstance().getBackgroundShader()->Bind();
    m_backgroundVertexArray->Bind();
    
    for (int i = m_map; i < m_map + 4; i++) {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(i * 10 + m_xScroll * 0.03f, 0, 0));
        ShadersManager::getInstance().getBackgroundShader()->SetUniformMat4f("vw_matrix", translation);
        m_backgroundVertexArray->Draw();
    }
    
    ShadersManager::getInstance().getBackgroundShader()->Unbind();
    m_backgroundTexture->Unbind();
    
    m_bird->Render();
}
