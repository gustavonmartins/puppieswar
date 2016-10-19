#ifndef SHADERCOMPILER_H
#define SHADERCOMPILER_H

#include <glad/glad.h>

#include <string>
#include <vector>

class ShaderCompiler {
public:
    ShaderCompiler();
    virtual ~ShaderCompiler();

    void addShader(std::string,GLenum const);
    GLuint compileProgram();
    void deleteProgram(GLuint const);

protected:

private:
    void checkProgramStatus();
    bool checkShaderStatus(const GLuint&, const std::string&);
    void deleteShaderObject();

    std::vector<GLuint> ShaderList;


};

#endif // SHADERCOMPILER_H
