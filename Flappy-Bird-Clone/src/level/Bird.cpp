//
//  Bird.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 06/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "Bird.h"

#include "graphics/ShadersManager.h"
#include "InputHandler.h"

#include "glm/gtc/matrix_transform.hpp"

Bird::Bird()
{
    float verticies[] = {
        -SIZE / 2.0f, -SIZE / 2.0f, -0.1f,
        -SIZE / 2.0f,  SIZE / 2.0f, -0.1f,
         SIZE / 2.0f,  SIZE / 2.0f, -0.1f,
         SIZE / 2.0f, -SIZE / 2.0f, -0.1f
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
    
    m_mesh = std::shared_ptr<VertexArray>(new VertexArray(verticies, verticesCount,
                                                          indices, indicesCount,
                                                          textureCoordinates, textureCoordinatesCount));
    m_texture = std::shared_ptr<Texture>(new Texture("resources/textures/bird.png"));
}

void Bird::Update() {
    m_position.y -= m_delta;

    if (InputHandler::getInstance().isKeyDown(GLFW_KEY_SPACE)) {
        m_delta = -0.15f;
    } else {
        m_delta += 0.01f;
    }
    
    m_rotation = -m_delta * 90.0f;
}

void Bird::Fall() {
    m_delta = -0.15f;
}

void Bird::Render() {
    ShadersManager::getInstance().getBirdShader()->Bind();
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_position);
    ShadersManager::getInstance().getBirdShader()->SetUniformMat4f("ml_matrix", translation);
    m_texture->Bind();
    m_mesh->Render();
    ShadersManager::getInstance().getBirdShader()->Unbind();
}
