//
//  Shader.hpp
//  opengl-course
//
//  Created by Túlio Henrique on 31/01/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include "GLDebugger.h"

#include <string>
#include <unordered_map>

#include "math/Matrix4f.h"

struct ShaderProgramSources {
    std::string VertexSources;
    std::string FragmentSources;
};

class Shader {
public:
    Shader() {}
    Shader(const std::string& filename);
    ~Shader();
    
    void Bind();
    void Unbind();
    
    // Set uniforms
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform2f(const std::string& name, float value1, float value2);
    void SetUniform3f(const std::string& name, float value1, float value2, float value3);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const Matrix4f& matrix);
    
    static const int VERTEX_ATTRIB = 0;
    static const int TCOORD_ATTRIB = 1;
private:
    ShaderProgramSources ParseShader(const std::string& filePath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    
    int GetUniformLocation(const std::string& name);
    
    void bindIfNecessary();
    
    bool m_binded;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
};

#endif /* Shader_h */
