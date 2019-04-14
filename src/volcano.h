#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H

class Volcano
{
  public:
    Volcano() {}
    Volcano(float x, float y, float z, color_t color);
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
    VAO *mnt;
    VAO *lava;
    VAO *smk;
    VAO *top;
};

#endif // ARROW_H
