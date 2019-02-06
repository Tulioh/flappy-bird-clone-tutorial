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

class Level {
public:
    Level();
    
    void Render();
private:
    std::shared_ptr<VertexArray> m_backgroundVertexArray;
};

#endif /* Level_h */
