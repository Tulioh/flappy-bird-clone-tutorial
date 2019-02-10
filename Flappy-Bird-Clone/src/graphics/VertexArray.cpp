//
//  VertexArray.cpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 04/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "VertexArray.h"

#include "GLDebugger.h"
#include "Shader.h"

#include <iostream>

VertexArray::VertexArray(int count)
: m_count(count), m_ibo(0)
{
    GLCall(glGenVertexArrays(1, &m_vao));
}

VertexArray::VertexArray(float vertices[], unsigned int verticesCount,
                         unsigned int indices[], unsigned indicesCount,
                         float textureCoordinates[], unsigned int textureCoordinatesCount)
    : m_count(indicesCount)
{
    GLCall(glGenVertexArrays(1, &m_vao));
    GLCall(glBindVertexArray(m_vao));
    
    GLCall(glGenBuffers(1, &m_vbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, verticesCount, vertices, GL_STATIC_DRAW));
    GLCall(glVertexAttribPointer(Shader::VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    GLCall(glEnableVertexAttribArray(Shader::VERTEX_ATTRIB));
    
    GLCall(glGenBuffers(1, &m_tbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_tbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, textureCoordinatesCount, textureCoordinates, GL_STATIC_DRAW));
    GLCall(glVertexAttribPointer(Shader::TCOORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, (void*)0));
    GLCall(glEnableVertexAttribArray(Shader::TCOORD_ATTRIB));
    
    GLCall(glGenBuffers(1, &m_ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount, indices, GL_STATIC_DRAW));
    
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
}

VertexArray::~VertexArray() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    if (m_tbo > 0) {
        glDeleteVertexArrays(1, &m_tbo);
    }
    if (m_ibo > 0) {
        glDeleteBuffers(1, &m_ibo);
    }
}

void VertexArray::Bind() {
    GLCall(glBindVertexArray(m_vao));
    if (m_ibo > 0) {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
    }
}

void VertexArray::Unbind() {
    GLCall(glBindVertexArray(0));
    if (m_ibo > 0) {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
}

void VertexArray::Draw() {
    if (m_ibo > 0) {
        GLCall(glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, 0));
    } else {
        GLCall(glDrawArrays(GL_TRIANGLES, 0, m_count));
    }
}

void VertexArray::Render() {
    Bind();
    Draw();
}
