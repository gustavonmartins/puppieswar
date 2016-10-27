#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "../../I_Moveable.h"

struct MeshGeometry {
public:
    MeshGeometry();
    virtual ~MeshGeometry();

    void attachTo(I_Moveable*);
    void beCube();
    void bePlane();
    void* getIndexData();
    GLsizei getIndexCount();
    GLsizeiptr getIndexSize();
    void* getPositionsData();
    GLsizeiptr getPositionsSize();


protected:

private:

    std::vector<GLfloat> VerticesPositions;
    std::vector<GLshort> VerticesIndices;
    glm::mat4 _ModelPositionMatrix;


};



//**********************************************
struct Mesh {
public:
    Mesh(MeshGeometry* inputGeo);
    virtual ~Mesh();

    void attachToPosition(I_Moveable*);
    void draw(const GLuint&);
    void draw(const glm::mat4&, const GLuint&);

protected:

private:


    GLuint& resetGPUBindings();
    void draw(const glm::mat4&);
    void refreshMatrixOfObjectAttachedTo(glm::mat4&);

    MeshGeometry* myMeshGeo;

    GLuint currentProgram;

    GLuint _meshGeometryBuffer;
    GLuint _meshIndexBuffer;
    GLuint _VAO;
    GLint _ModelPosition_location_onShader;
    GLint _vposition_location_onShader;

    GLsizei _indexCount;

    glm::mat4 _ModelPositionMatrix;
    I_Moveable* _currentobjectToTrack;



};

#endif // MESH_H
