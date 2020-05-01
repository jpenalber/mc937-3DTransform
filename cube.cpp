#include "cube.h"

Cube::Cube() {
}

void Cube::select() {
    selected = true;
}

void Cube::diselect() {
    selected = false;
}

void Cube::selectAll() {
    all = true;
}

void Cube::diselectAll() {
    all = false;
}

void Cube::setVertices(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength) {
    GLfloat halfSideLength = edgeLength * 0.5f;
    this->edgeLength = edgeLength;

    origin = {centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength};

    vertices =
    {
        // front face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // back face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

        // left face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // right face
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

        // top face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

        // top face
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
    };
}

void Cube::Draw() {
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, (void*)&vertices[0]);
    glColorPointer(3, GL_FLOAT, 0, (void*)&colour[0]);

    glDrawArrays( GL_QUADS, 0, 24 );

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState( GL_VERTEX_ARRAY );

    if (selected) {
        GLfloat cordV[] = {
            origin[0], origin[1], origin[2],
            origin[0]+2*edgeLength, origin[1], origin[2],

            origin[0], origin[1], origin[2],
            origin[0], origin[1]+2*edgeLength, origin[2],

            origin[0], origin[1], origin[2],
            origin[0], origin[1], origin[2]+2*edgeLength
        };

        glEnableClientState( GL_VERTEX_ARRAY );
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer( 3, GL_FLOAT, 0, cordV );

        glDrawArrays( GL_LINES, 0, 6 );

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState( GL_VERTEX_ARRAY );
    }

}
