//
//  Level.hpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 05/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef Level_h
#define Level_h

#include <memory>
#include <vector>
#include <random>

#include "graphics/VertexArray.h"
#include "graphics/Texture.h"

#include "Bird.h"
#include "Pipe.h"

class Level {
public:
    Level();
    ~Level();
    
    void Update();
    void Render();
private:
    const int OFFSET = 5.0f;
    const int MAX_PIPES = 10;
    const float PIPE_WIDTH = 1.5f;
    const float PIPE_HEIGHT = 8.0f;
    
    void CreateBackground();
    void CreatePipes();
    void RenderPipes();
    void UpdatePipes();
    bool Collision();
    void Reset();
    
    int m_xScroll = 0;
    int m_map = 0;
    int m_index = 0;
    float m_time = 0.0f;
    bool m_dead = false;
    
    std::uniform_real_distribution<float> m_float_distribuition;
    std::default_random_engine m_random;
    
    std::unique_ptr<VertexArray> m_backgroundVertexArray;
    std::unique_ptr<Texture> m_backgroundTexture;
    
    std::unique_ptr<VertexArray> m_pipeVertexArray;
    std::unique_ptr<Texture> m_pipeTexture;
    
    std::unique_ptr<VertexArray> m_fadeVertexArray;
    
    std::unique_ptr<Bird> m_bird;
    std::vector<Pipe> m_pipes;
    
};

#endif /* Level_h */
