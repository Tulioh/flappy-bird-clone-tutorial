//
//  Bird.hpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 06/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef Bird_h
#define Bird_h

#include <memory>

#include "graphics/VertexArray.h"
#include "graphics/Texture.h"
#include "math/Matrix4f.h"
#include "math/Vector3f.h"

class Bird {
public:
    Bird();
    
    void Fall();
    void Update();
    void Render();
    void Reset();
    
    inline int GetY() const { return m_position.y; }
    inline int GetSize() const { return SIZE; }
private:
    const float SIZE = 1.0f;
    std::shared_ptr<VertexArray> m_mesh;
    std::shared_ptr<Texture> m_texture;
    
    Vector3f m_position;
    float m_rotation = 0.0f;
    float m_delta = 0.0f;
};

#endif /* Bird_h */
