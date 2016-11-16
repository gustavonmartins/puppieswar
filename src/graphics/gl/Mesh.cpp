#include "Mesh.h"
#include <iostream>

MeshGeometry::MeshGeometry() {
//ctor
}

MeshGeometry::~MeshGeometry() {
    //dtor

}

void MeshGeometry::beCube() {
    VerticesPositions = {
        -2.5f, -2.5f, -2.5f,
        -2.5f, +2.5f, -2.5f,
        +2.5f, -2.5f, -2.5f,
        +2.5f, +2.5f, -2.5f,
        +2.5f, -2.5f, +2.5f,
        +2.5f, +2.5f, +2.5f,
        -2.5f, -2.5f, +2.5f,
        -2.5f, +2.5f, +2.5f
    };

    VerticesIndices = {
        0, 1, 2,
        2, 1, 3,
        2, 3, 4,
        4, 3, 5,
        4, 5, 6,
        6, 5, 7,
        6, 7, 0,
        0, 7, 1,
        6, 0, 2,
        2, 4, 6,
        7, 5, 3,
        7, 3, 1
    };
}

void MeshGeometry::bePlane() {
    VerticesPositions = {
        -25.0f, -25.0f, 0.0f,
        -25.0f, +25.0f, 0.0f,
        +25.0f, -25.0f, 0.0f,
        +25.0f, +25.0f, 0.0f,
    };

    VerticesIndices = {
        0, 1, 2,
        2, 1, 3
    };
}

GLsizei MeshGeometry::getIndexCount() {
    return VerticesIndices.size();
}

void* MeshGeometry::getIndexData() {
    return VerticesIndices.data();
}

GLsizeiptr MeshGeometry::getIndexSize() {
    return sizeof(GLshort) * VerticesIndices.size();
}

void* MeshGeometry::getPositionsData() {
    return VerticesPositions.data();
}

GLsizeiptr MeshGeometry::getPositionsSize() {
    return sizeof(GLfloat) * VerticesPositions.size();
}




//**********************************************



Mesh::Mesh(MeshGeometry* inputGeo):

    myMeshGeo(inputGeo),
    currentProgram(-1),

    _meshGeometryBuffer(-1),
    _meshIndexBuffer(-1),
    _VAO(-1),

    _ModelPosition_location_onShader(-1),
    _vposition_location_onShader(-1),
    _indexCount(-1),


    _currentobjectToTrack(nullptr)

{

    glGenBuffers(1, &_meshGeometryBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _meshGeometryBuffer);
    glBufferData(GL_ARRAY_BUFFER, myMeshGeo->getPositionsSize(), myMeshGeo->getPositionsData(), GL_STATIC_DRAW);

    glGenBuffers(1, &_meshIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _meshIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, myMeshGeo->getIndexSize(), myMeshGeo->getIndexData(), GL_STATIC_DRAW);

    _indexCount = myMeshGeo->getIndexCount();

    std::cout << "_meshGeometryBuffer: " << _meshGeometryBuffer << std::endl;
    std::cout << "_meshIndexBuffer: " << _meshIndexBuffer << std::endl;

}

Mesh::~Mesh() {
    glDeleteBuffers(1, &_meshGeometryBuffer);
    glDeleteBuffers(1, &_meshIndexBuffer);
    glDeleteVertexArrays(1, &_VAO);

}


void Mesh::attachToPosition(I_Moveable* objectToTrack) {
    if (nullptr == objectToTrack && _currentobjectToTrack != nullptr) {
        refreshMatrixOfObjectAttachedTo(_ModelPositionMatrix);
    } else if (nullptr != objectToTrack) {
        _currentobjectToTrack = objectToTrack;
        refreshMatrixOfObjectAttachedTo(_ModelPositionMatrix);
    }
}

I_Moveable* Mesh::getAttachee(){
    return _currentobjectToTrack;
}

void Mesh::refreshMatrixOfObjectAttachedTo(glm::mat4& MatrixToChange) {
    MatrixToChange =
        glm::translate(glm::mat4(1.0f), glm::vec3(_currentobjectToTrack->getPosition().axis_one, _currentobjectToTrack->getPosition().axis_two, _currentobjectToTrack->getPosition().axis_three)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}

GLuint& Mesh::resetGPUBindings() {

    _vposition_location_onShader = glGetAttribLocation(currentProgram, "vPosition");
    _ModelPosition_location_onShader = glGetUniformLocation(currentProgram, "ModelPosition_Matrix");

    glDeleteVertexArrays(1, &_VAO);
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _meshGeometryBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _meshIndexBuffer);
    glVertexAttribPointer(_vposition_location_onShader, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(_vposition_location_onShader);
    glBindVertexArray(0); //Just for safety!
    std::cout << "_VAO: " << _VAO << " " << _meshGeometryBuffer << " " << _meshIndexBuffer << " " << _vposition_location_onShader << std::endl;
    return _VAO;
}


void Mesh::draw(const glm::mat4& ModelPositionMatrix) {

    glUniformMatrix4fv(_ModelPosition_location_onShader, 1, GL_FALSE, &ModelPositionMatrix[0][0]);

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, 0);
}

void Mesh::draw(const glm::mat4& ModelPositionMatrix, const  GLuint& renderProgram) {

    if (currentProgram != renderProgram ) {
        currentProgram = renderProgram;
        resetGPUBindings();
        glUseProgram(currentProgram);

        std::cout << "Program changed!" << std::endl;
    }

    draw(ModelPositionMatrix);
}

void Mesh::draw(const GLuint& renderProgram) {
    if (currentProgram != renderProgram ) {
        currentProgram = renderProgram;
        resetGPUBindings();
        glUseProgram(currentProgram);

        std::cout << "Program changed to " << renderProgram << std::endl;
    }

    attachToPosition(nullptr);
    draw(_ModelPositionMatrix);
}

