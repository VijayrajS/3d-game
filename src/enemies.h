#include "main.h"

#ifndef ENEMIES_H
#define ENEMIES_H

class Cannon
{
  public:
    Cannon() {}
    Cannon(float x, float y, float zS);
    glm::vec3 position;
    float speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    int alive;

  private:
    VAO *object;
    VAO *barrel;
    VAO *land;
};

class Para
{
  public:
    Para() {}
    Para(float x, float y, float z);
    glm::vec3 position;
    float speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();

  private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // ENEMIES_H
