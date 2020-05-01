#ifndef CUBE_H
#define CUBE_H
#include <GL/glew.h>
#include <vector>
#include <Eigen/Dense>

#define X 1
#define SHIFT_X 2
#define Y 3
#define SHIFT_Y 4
#define Z 5
#define SHIFT_Z 6

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
