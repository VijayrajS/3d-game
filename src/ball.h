#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y);
    glm::vec3 position;
    float rotationx;
    float rotationy;
    float rotationz;

    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bool sea_coll();
    void tick();
    double speed;
    double fuel;

private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;

    VAO *inner_f;
    VAO *outer_f;
};

#endif // BALL_H
