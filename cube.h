#ifndef CUBE_H
#define CUBE_H
#include <GL/glew.h>
#include <vector>
#include <Eigen/Dense>

#define X 1
#define SHIFT_X 2
#define Y 3
#define SIFIT_Y 4
#define Z 5
#define SHIFT_Z 6

#define S 7
#define Q 8
#define A 9

#define TRANS_RIGHT 10
#define TRANS_LEFT 11
#define TRANS_UP 12
#define TRANS_DOWN 13
#define TRANS_FOWARD 14
#define TRANS_BACKWARD 15

class Cube
{
public:
    Cube();
    void setVertices(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
    void Draw();
    void select();
    void diselect();
    void selectAll();
    void diselectAll();

    void scaling(int op);

    void translate(int op);
private:
    std::vector<GLfloat> vertices;

    std::vector<GLfloat> origin;
    GLfloat edgeLength;

    bool selected = false;
    bool all = false;

    std::vector<GLfloat> colour =
    {
      255, 0, 0,
      255, 0, 0,
      255, 0, 0,
      255, 0, 0,

      0, 255, 0,
      0, 255, 0,
      0, 255, 0,
      0, 255, 0,

      0, 0, 255,
      0, 0, 255,
      0, 0, 255,
      0, 0, 255,

      255, 255, 0,
      255, 255, 0,
      255, 255, 0,
      255, 255, 0,

      0, 255, 255,
      0, 255, 255,
      0, 255, 255,
      0, 255, 255,

      255, 0, 255,
      255, 0, 255,
      255, 0, 255,
      255, 0, 255};

    std::vector<GLfloat> colour_b = {
      0, 0, 0,
      0, 0, 0,
      0, 0, 0,
      0, 0, 0,

      0, 0, 0,
      0, 0, 0,
      0, 0, 0,
      0, 0, 0,

      0, 0, 0,
      0, 0, 0,
      0, 0, 0,
      0, 0, 0,

      0, 0, 0,
      0, 0, 0,
      0, 0, 0,
      0, 0, 0,

      0, 0, 0,
      0, 0, 0,
      0, 0, 0,
      0, 0, 0,

      0, 0, 0,
      0, 0, 0,
      0, 0, 0,
      0, 0, 0};
};

#endif // CUBE_H
