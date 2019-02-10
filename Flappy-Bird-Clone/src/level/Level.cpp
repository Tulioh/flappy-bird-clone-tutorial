//
//  Level.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 05/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "Level.h"

#include "math/Matrix4f.h"
#include "math/Vector3f.h"
#include "graphics/ShadersManager.h"
#include "InputHandler.h"

Level::Level()
    : m_float_distribuition(0.0f, 1.0f)
{
    m_fadeVertexArray = std::unique_ptr<VertexArray>(new VertexArray(6));
    CreateBackground();
    m_bird = std::unique_ptr<Bird>(new Bird());
    CreatePipes();
}

Level::~Level() {
    m_backgroundVertexArray->Unbind();
    m_backgroundTexture->Unbind();
    m_pipeVertexArray->Unbind();
    m_pipeTexture->Unbind();
    m_fadeVertexArray->Unbind();
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
    float verticies[] = {
        0.0f,        0.0f,  0.1f,
        0.0f,        PIPE_HEIGHT,  0.1f,
        PIPE_WIDTH,  PIPE_HEIGHT, 0.1f,
        PIPE_WIDTH,   0.0f, 0.1f,
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
    
    for (int i = 0; i < MAX_PIPES; i += 2) {
        Pipe topPipe(OFFSET + m_index * 3.0f, m_float_distribuition(m_random) * 4.0f);
        Pipe bottomPipe(topPipe.GetX(), topPipe.GetY() - 11.5f);
        m_pipes.push_back(topPipe);
        m_pipes.push_back(bottomPipe);
        m_index += 2;
    }
}

void Level::Update() {
    if (!m_dead) {
        m_xScroll--;
        
        if (-m_xScroll % 335 == 0) {
            m_map++;
        }
        if (-m_xScroll > 250 && -m_xScroll % 120 == 0) {
            UpdatePipes();
        }
    }
    
    m_bird->Update();
    
    if (!m_dead && Collision()) {
        m_bird->Fall();
        m_dead = true;
    }
    
    if (m_dead && InputHandler::getInstance().isKeyDown(GLFW_KEY_SPACE)) {
        m_bird->Reset();
        Reset();
    }
    
    m_time += 0.01f;
}

void Level::Render() {
    m_backgroundTexture->Bind();
    ShadersManager::getInstance().getBackgroundShader()->Bind();
    ShadersManager::getInstance().getBackgroundShader()->SetUniform2f("bird", 0, m_bird->GetY());
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
    
    ShadersManager::getInstance().getFadeShader()->Bind();
    ShadersManager::getInstance().getFadeShader()->SetUniform1f("time", m_time);
    m_fadeVertexArray->Render();
    ShadersManager::getInstance().getFadeShader()->Unbind();
}

void Level::RenderPipes() {
    ShadersManager::getInstance().getPipeShader()->Bind();
    ShadersManager::getInstance().getPipeShader()->SetUniform2f("bird", 0, m_bird->GetY());
    Vector3f position(m_xScroll * 0.05f, 0.0f, 0.0f);
    ShadersManager::getInstance().getPipeShader()->SetUniformMat4f("vw_matrix", Matrix4f::translate(position));
    m_pipeTexture->Bind();
    m_pipeVertexArray->Bind();
    
    for (int i = 0; i < 5 * 2; i++) {
        ShadersManager::getInstance().getPipeShader()->SetUniformMat4f("ml_matrix", m_pipes[i].GetModelMatrix());
        ShadersManager::getInstance().getPipeShader()->SetUniform1i("top", i % 2 == 0 ? 1 : 0);
        m_pipeVertexArray->Draw();
    }
    
    m_pipeVertexArray->Unbind();
    m_pipeTexture->Unbind();
    ShadersManager::getInstance().getPipeShader()->Unbind();
}

void Level::UpdatePipes() {    
    Pipe topPipe(OFFSET + m_index * 3.0f, m_float_distribuition(m_random) * 4.0f);
    Pipe bottomPipe(topPipe.GetX(), topPipe.GetY() - 11.5f);
    m_pipes[m_index % 10] = topPipe;
    m_pipes[(m_index + 1) % 10] = bottomPipe;
    m_index += 2;
}

bool Level::Collision() {
    for (int i = 0; i < MAX_PIPES; i++) {
        float birdX = -m_xScroll * 0.05f;
        float birdY = m_bird->GetY();
        float pipeX = m_pipes[i].GetX();
        float pipeY = m_pipes[i].GetY();
        
        float birdX0 = birdX - m_bird->GetSize() / 2.0f;
        float birdX1 = birdX + m_bird->GetSize() / 2.0f;
        float birdY0 = birdY - m_bird->GetSize() / 2.0f;
        float birdY1 = birdY + m_bird->GetSize() / 2.0f;
        
        float pipeX0 = pipeX;
        float pipeX1 = pipeX + PIPE_WIDTH;
        float pipeY0 = pipeY;
        float pipeY1 = pipeY + PIPE_HEIGHT;
        
        if ((birdX1 > pipeX0 && birdX0 < pipeX1) && (birdY1 > pipeY0 && birdY0 < pipeY1 )) {
            return true;
        }
    }
    
    return false;
}

void Level::Reset() {
    m_xScroll = 0;
    m_map = 0;
    m_index = 0;
    m_time = 0.0f;
    m_dead = false;
}
