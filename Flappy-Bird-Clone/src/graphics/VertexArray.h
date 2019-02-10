//
//  VertexArray.hpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 04/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef VertexArray_h
#define VertexArray_h

class VertexArray {
public:
    VertexArray(float vertices[], unsigned int verticesCount,
                unsigned int indices[], unsigned indicesCount,
                float textureCoordinates[], unsigned int textureCoordinatesCount);
    VertexArray(int count);
    ~VertexArray();
    
    void Bind();
    void Unbind();
    void Draw();
    void Render();
private:
    unsigned int m_vao, m_vbo, m_ibo, m_tbo;
    unsigned int m_count;
};

#endif /* VertexArray_h */
