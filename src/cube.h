#include "main.h"

#ifndef CUBE_H
#define CUBE_H

class Cube
{
  public:
    Cube() {}
    Cube(float x, float y, float z, float length, float breadth, float width, color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    float breadth;
    float length;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();

  private:
    VAO *object;
};

#endif // CUBE_H
