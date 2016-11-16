#include "ShaderCompiler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>




ShaderCompiler::ShaderCompiler() {

}

ShaderCompiler::~ShaderCompiler() {
    //dtor
}

void ShaderCompiler::addShader(std::string _sourceCodeFile, GLenum _type) {

    std::ifstream shader_source_aux3(_sourceCodeFile);
    if (!shader_source_aux3.is_open()) {
        std::cout << "Shader file cannot be opened: " << _sourceCodeFile << std::endl;
        throw std::runtime_error("Shader file could not be opened!");
    }

    std::stringstream shader_source_aux2;
    shader_source_aux2 << shader_source_aux3.rdbuf();
    std::string shader_source_aux(shader_source_aux2.str());
    const char* shader_source = shader_source_aux.c_str();

    GLuint ShaderID = 0;



    ShaderID = glCreateShader(_type);
    glShaderSource(ShaderID, 1, &shader_source, NULL);
    glCompileShader(ShaderID);


    if (checkShaderStatus(ShaderID, _sourceCodeFile)) {
        ShaderList.push_back(ShaderID);
    } else {
        throw std::runtime_error("Shader didnt compile! See error files");
    }



}

bool ShaderCompiler::checkShaderStatus(const GLuint& _shader, const std::string& _fileName) {

    GLint status = 0;

    glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);

    if (status != 1) {
        std::cout << _fileName << " failed to compile" << std::endl;

        GLint logLength;
        std::string logText;

        glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &logLength);
        logText.resize(logLength);
        glGetShaderInfoLog(_shader, logLength, NULL, &logText[0]);

        std::ofstream WriteErrorToFile(_fileName + ".error", std::ofstream::app);
        WriteErrorToFile << "----------------" << _fileName << " debug info: \n";
        WriteErrorToFile << logText;
        WriteErrorToFile.close();

        return false;
    }

    else {
        return true;
    }

}

GLuint ShaderCompiler::compileProgram() {
    GLuint ProgramID;

    ProgramID = glCreateProgram();
    for (GLuint& currentShader : ShaderList) {
        glAttachShader(ProgramID, currentShader);
    }
    glLinkProgram(ProgramID);
    //glGetProgramInfoLog(ProgramID);

    for (GLuint& currentShader : ShaderList) {
        glDeleteShader(currentShader);
    }
    ShaderList.clear();
    std::cout<<"Shader compilation successful, ID: "<<ProgramID<<std::endl;
    return ProgramID;
}

void ShaderCompiler::deleteProgram(GLuint _programID) {
    glDeleteProgram(_programID);
}
