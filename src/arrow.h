#include "main.h"

#ifndef ARROW_H
#define ARROW_H

class Arrow
{
  public:
    Arrow() {}
    Arrow(float x, float y, float z, color_t color);
    glm::vec3 position;
    float speed;
    float rotation;
    float width;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();

  private:
    VAO *object;
};

#endif // ARROW_H
