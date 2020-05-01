#include <iostream>
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

void Cube::scaling(int op) {
    if (!selected) return;

    Eigen::MatrixXf scalM(4,4);
    if (op == X) {
        scalM << 0.9, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1;
    }

    for (int i = 0; i < vertices.size(); i+=3) {
        Eigen::Vector4f v(vertices[i], vertices[i+1], vertices[i+2], 1);
        v = scalM*v;
    }
}

void Cube::translate(int op) {
    if (!selected) return;

    Eigen::MatrixXf scalM(4,4);

    switch (op) {
        case TRANS_RIGHT:
            scalM << 1, 0, 0, 1,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1;
        break;
        case TRANS_LEFT:
            scalM << 1, 0, 0, -1,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1;
        break;
        case TRANS_UP:
            scalM << 1, 0, 0, 0,
                     0, 1, 0, 1,
                     0, 0, 1, 0,
                     0, 0, 0, 1;
        break;
        case TRANS_DOWN:
            scalM << 1, 0, 0, 0,
                     0, 1, 0, -1,
                     0, 0, 1, 0,
                     0, 0, 0, 1;
        break;
        case TRANS_FOWARD:
            scalM << 1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 1,
                     0, 0, 0, 1;
        break;
        case TRANS_BACKWARD:
            scalM << 1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, -1,
                     0, 0, 0, 1;
        break;
    }

    for (int i = 0; i < vertices.size(); i+=3) {
        Eigen::Vector4f v(vertices[i], vertices[i+1], vertices[i+2], 1);
        v = scalM*v;
        vertices[i] = v[0];
        vertices[i+1] = v[1];
        vertices[i+2] = v[2];
    }
}
