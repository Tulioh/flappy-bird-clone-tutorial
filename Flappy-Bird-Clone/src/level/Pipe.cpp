//
//  Pipe.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 08/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "Pipe.h"

Pipe::Pipe(float x, float y) {
    m_position.x = x;
    m_position.y = y;
    m_mlMatrix = Matrix4f::translate(m_position);
}
