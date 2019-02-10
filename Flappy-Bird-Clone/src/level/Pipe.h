//
//  Pipe.hpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 08/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef Pipe_h
#define Pipe_h

#include "math/Vector3f.h"
#include "math/Matrix4f.h"
#include "graphics/Texture.h"
#include "graphics/VertexArray.h"

class Pipe {
public:
    Pipe(float x, float y);
    
    inline float GetX() { return m_position.x; }
    inline float GetY() { return m_position.y; }
    inline Matrix4f& GetModelMatrix() { return m_mlMatrix; }
private:
    Vector3f m_position;
    Matrix4f m_mlMatrix;
};

#endif /* Pipe_h */
