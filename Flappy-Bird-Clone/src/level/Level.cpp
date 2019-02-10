//
//  Level.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 05/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "Level.h"

#include <random>

#include "math/Matrix4f.h"
#include "math/Vector3f.h"
#include "graphics/ShadersManager.h"

Level::Level() {
    CreateBackground();
    m_bird = std::unique_ptr<Bird>(new Bird());
    CreatePipes();
}

void Level::CreateBackground()
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
    
    m_backgroundVertexArray = std::unique_ptr<VertexArray>(new VertexArray(verticies, verticesCount,
                                                                           indices, indicesCount,
                                                                           textureCoordinates, textureCoordinatesCount));
    m_backgroundTexture = std::unique_ptr<Texture>(new Texture("resources/textures/bg.jpg"));
}

void Level::CreatePipes() {
    const float WIDTH = 1.5f;
    const float HEIGHT = 8.0f;
    
    float verticies[] = {
        0.0f,    0.0f,  0.1f,
        0.0f,  HEIGHT,  0.1f,
        WIDTH,  HEIGHT, 0.1f,
        WIDTH,    0.0f, 0.1f,
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
    
    m_pipeVertexArray = std::unique_ptr<VertexArray>(new VertexArray(verticies, verticesCount,
                                                                    indices, indicesCount,
                                                                    textureCoordinates, textureCoordinatesCount));
    m_pipeTexture = std::unique_ptr<Texture>(new Texture("resources/textures/pipe.png"));
    
    std::uniform_real_distribution<float> unif(0.0f, 1.0f);
    std::default_random_engine re;
    
    for (int i = 0; i < 5 * 2; i += 2) {
        Pipe topPipe(m_index * 3.0f, unif(re) * 4.0f);
        Pipe bottomPipe(topPipe.GetX(), topPipe.GetY() - 11.5f);
        m_pipes.push_back(topPipe);
        m_pipes.push_back(bottomPipe);
        m_index += 2;
    }
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
        Vector3f backgroundPosition = Vector3f(i * 10 + m_xScroll * 0.03f, 0.0f, 0.0f);
        ShadersManager::getInstance().getBackgroundShader()->SetUniformMat4f("vw_matrix", Matrix4f::translate(backgroundPosition));
        m_backgroundVertexArray->Draw();
    }
    
    ShadersManager::getInstance().getBackgroundShader()->Unbind();
    m_backgroundVertexArray->Unbind();
    m_backgroundTexture->Unbind();
    
    RenderPipes();
    m_bird->Render();
}

void Level::RenderPipes() {
    m_pipeTexture->Bind();
    ShadersManager::getInstance().getPipeShader()->Bind();
    Vector3f position(m_xScroll * 0.05f, 0.0f, 0.0f);
    ShadersManager::getInstance().getPipeShader()->SetUniformMat4f("vw_matrix", Matrix4f::translate(position));
    m_pipeVertexArray->Bind();
    
    for (int i = 0; i < 5 * 2; i++) {
        ShadersManager::getInstance().getPipeShader()->SetUniformMat4f("ml_matrix", m_pipes[i].GetModelMatrix());
//        ShadersManager::getInstance().getPipeShader()->SetUniform1i("top", i % 2 == 0 ? 1 : 0);
        m_pipeVertexArray->Draw();
    }
    
    ShadersManager::getInstance().getPipeShader()->Unbind();
    m_pipeVertexArray->Unbind();
    m_pipeTexture->Unbind();
}

void Level::UpdatePipes() {
    
}
