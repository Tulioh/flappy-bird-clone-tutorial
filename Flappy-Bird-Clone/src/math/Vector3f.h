//
//  Vector3f.hpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 03/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef Vector3f_h
#define Vector3f_h

struct Vector3f {
public:
    Vector3f()
        : x(0), y(0), z(0) {}
    
    Vector3f(float x, float y, float z)
        : x(x), y(y), z(z) {}
    
    inline void Reset() {
        x = 0;
        y = 0;
        z = 0;
    }

    float x, y, z;
};

#endif /* Vector3f_h */
