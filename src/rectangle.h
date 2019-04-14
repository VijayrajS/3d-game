#include "main.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
  public:
    Rectangle() {}
    Rectangle(float x, float y, float z, float width, float height, float yw, color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    float width;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();

  private:
    VAO *object;
};

#endif // RECTANGLE_H
