#include "main.h"

#ifndef NEEDLE_H
#define NEEDLE_H

class Needle
{
  public:
    Needle() {}
    Needle(float x, float y, float z,  color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float fuel);

  private:
    VAO *object;
};

#endif // NEEDLE_H
