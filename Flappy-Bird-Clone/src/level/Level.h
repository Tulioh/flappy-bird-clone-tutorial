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

#include "graphics/VertexArray.h"
#include "graphics/Texture.h"

#include "Bird.h"
#include "Pipe.h"

class Level {
public:
    Level();
    
    void Update();
    
    void Render();
private:
    void CreateBackground();
    void CreatePipes();
    void RenderPipes();
    void UpdatePipes();
    
    int m_xScroll = 0;
    int m_map = 0;
    
    int m_index = 0;
    
    std::unique_ptr<VertexArray> m_backgroundVertexArray;
    std::unique_ptr<Texture> m_backgroundTexture;
    
    std::unique_ptr<VertexArray> m_pipeVertexArray;
    std::unique_ptr<Texture> m_pipeTexture;
    
    std::unique_ptr<Bird> m_bird;
    std::vector<Pipe> m_pipes;
    
};

#endif /* Level_h */
