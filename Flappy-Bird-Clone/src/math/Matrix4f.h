//
//  Matrix4f.hpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 04/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef Matrix4f_h
#define Matrix4f_h

#include "Vector3f.h"

class Matrix4f {
public:
    static Matrix4f identity();
    static Matrix4f orthographic(float left, float right, float bottom, float top, float near, float far);
    static Matrix4f translate(Vector3f& vector);
    static Matrix4f rotate(float angle);
    
    Matrix4f operator*(const Matrix4f& matrix4f);
    const float& operator[](unsigned int position) const;
    
private:
    static const int SIZE = 4 * 4;
    float elements[SIZE];
};

#endif /* Matrix4f_h */
