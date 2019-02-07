//
//  Bird.hpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 06/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef Bird_h
#define Bird_h

#include "graphics/VertexArray.h"
#include "graphics/Texture.h"

#include <memory>
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

class Bird {
public:
    Bird();
    
    void Update();
    void Render();
private:
    void Fall();
    
    const float SIZE = 1.0f;
    std::shared_ptr<VertexArray> m_mesh;
    std::shared_ptr<Texture> m_texture;
    
    glm::vec3 m_position;
    float m_rotation = 0.0f;
    float m_delta = 0.0f;
};

#endif /* Bird_h */
