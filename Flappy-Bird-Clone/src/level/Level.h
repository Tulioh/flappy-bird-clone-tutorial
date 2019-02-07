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

#include "graphics/VertexArray.h"
#include "graphics/Texture.h"

#include "Bird.h"

class Level {
public:
    Level();
    
    void Update();
    
    void Render();
private:
    int m_xScroll;
    int m_map;
    
    std::shared_ptr<VertexArray> m_backgroundVertexArray;
    std::shared_ptr<Texture> m_backgroundTexture;
    std::shared_ptr<Bird> m_bird;
};

#endif /* Level_h */
