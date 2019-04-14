#include "main.h"

#ifndef BOMB_H
#define BOMB_H

class Bomb
{
  public:
    Bomb() {}
    Bomb(float x, float y, float z, float rx, float ry, float rz, int flag, float speed);
    glm::vec3 position;
    glm::mat4 cannonb;
    float speed;
    float rotationx;
    float rotationy;
    float rotationz;
    float width;
    float height;
    int bm;      // Bomb or missile flag
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bool sea_coll();
    bounding_box_t bounding_box();

  private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // BOMB_H
