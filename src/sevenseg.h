#include "main.h"

#ifndef SEVENSEG_H
#define SEVENSEG_H

/* 
    A - Top
    B - Top Left
    C - Top Right
    D - Middle
    E - Bottom Left
    F - Bottom Right
    G - Bottom
*/

class Sevenseg
{
  public:
    Sevenseg() {}
    Sevenseg(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    float length;
    void draw(glm::mat4 VP, int number);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();

  private:
    VAO *A;
    VAO *B;
    VAO *C;
    VAO *D;
    VAO *E;
    VAO *F;
    VAO *G;
};

#endif // SEVENSEG_H
