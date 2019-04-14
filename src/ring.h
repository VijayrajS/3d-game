#include "main.h"

#ifndef RING_H
#define RING_H

class Ring
{
  public:
    Ring() {}
    Ring(float x, float y, float z, float rx, float r, color_t color);
    glm::vec3 position;
    float speed;
    float rotation;
    int smokeon;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();

  private:
    VAO *object;
};

#endif // RING_H
