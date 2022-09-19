#include "Primitives/Cube.hpp"

Cube::Cube()
{
  createMesh();
}

void Cube::createMesh()
{
  // fill out the vertices
  vertCoords_ = {
    // front face
    /* v1 */ {-0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},
    /* v2 */ { 0.5f, 0.5f, 0.5f}, { 0.5f, 0.5f, 0.5f}, { 0.5f, 0.5f, 0.5f},
    /* v3 */ {-0.5f,-0.5f, 0.5f}, {-0.5f,-0.5f, 0.5f}, {-0.5f,-0.5f, 0.5f},
    /* v4 */ { 0.5f,-0.5f, 0.5f}, { 0.5f,-0.5f, 0.5f}, { 0.5f,-0.5f, 0.5f},

    // back face
    /* v5 */ {-0.5f, 0.5f,-0.5f}, {-0.5f, 0.5f,-0.5f}, {-0.5f, 0.5f,-0.5f},
    /* v6 */ { 0.5f, 0.5f,-0.5f}, { 0.5f, 0.5f,-0.5f}, { 0.5f, 0.5f,-0.5f},
    /* v7 */ {-0.5f,-0.5f,-0.5f}, {-0.5f,-0.5f,-0.5f}, {-0.5f,-0.5f,-0.5f},
    /* v8 */ { 0.5f,-0.5f,-0.5f}, { 0.5f,-0.5f,-0.5f}, { 0.5f,-0.5f,-0.5f}};

  // fill out the normals
  vertNormals_ = {
    // front face
    /* v1 */ { 0, 0, 1}, {-1, 0, 0}, { 0, 1, 0}, 
    /* v2 */ { 0, 0, 1}, { 1, 0, 0}, { 0, 1, 0},
    /* v3 */ { 0, 0, 1}, {-1, 0, 0}, { 0,-1, 0},
    /* v4 */ { 0, 0, 1}, { 1, 0, 0}, { 0,-1, 0},

    // back face
    /* v5 */ { 0, 0,-1}, {-1, 0, 0}, {0, 1, 0},
    /* v6 */ { 0, 0,-1}, { 1, 0, 0}, {0, 1, 0},
    /* v7 */ { 0, 0,-1}, {-1, 0, 0}, {0,-1, 0},
    /* v8 */ { 0, 0,-1}, { 1, 0, 0}, {0,-1, 0}};

  indices_ = {
    /*f1*/  0,  3,  9,  0,  6,  9,
    /*f2*/  4, 16, 22,  4, 10, 22,
    /*f3*/ 15, 12, 18, 15, 21, 18, 
    /*f4*/ 13,  1,  7, 13, 19,  7,
    /*f5*/  2,  5, 17,  2, 14, 17,
    /*f6*/  8, 11, 23,  8, 20, 23};  
}

const QVector<QVector3D> &Cube::vertCoords() const 
{
  return vertCoords_;
}

const QVector<QVector3D> &Cube::vertNormals() const 
{
  return vertNormals_;
}

const QVector<uint32> &Cube::indices() const 
{
  return indices_;
}
