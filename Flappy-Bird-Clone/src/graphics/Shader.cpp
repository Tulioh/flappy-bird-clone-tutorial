//
//  Shader.cpp
//  opengl-course
//
//  Created by Túlio Henrique on 31/01/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filePath)
    : m_RendererID(0), m_binded(false)
{
    ShaderProgramSources source = ParseShader(filePath);
    m_RendererID = CreateShader(source.VertexSources, source.FragmentSources);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSources Shader::ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);
    
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    std::string line;
    std::stringstream stringStream[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            stringStream[(int)type] << line << '\n';
        }
    }
    
    return { stringStream[0].str(), stringStream[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::string shaderType = (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex";
        std::cout << "Failed to compile " << shaderType << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }
    
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));
    
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    
    return program;
}

void Shader::Bind() {
    GLCall(glUseProgram(m_RendererID));
    m_binded = true;
}

void Shader::Unbind() {
    GLCall(glUseProgram(0));
    m_binded = false;
}

void Shader::SetUniform1i(const std::string& name, int value) {
    bindIfNecessary();
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value) {
    bindIfNecessary();
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform2f(const std::string& name, float value1, float value2) {
    bindIfNecessary();
    GLCall(glUniform2f(GetUniformLocation(name), value1, value2));
}

void Shader::SetUniform3f(const std::string& name, float value1, float value2, float value3) {
    bindIfNecessary();
    GLCall(glUniform3f(GetUniformLocation(name), value1, value2, value3));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    bindIfNecessary();
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const Matrix4f& matrix) {
    bindIfNecessary();
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0]));
}

int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }
    
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) {
        std::cout << "Warning uniform '" << name << "' doesn't exist!" << std::endl;
    }
    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::bindIfNecessary() {
    if (!m_binded) {
        Bind();
    }
}
