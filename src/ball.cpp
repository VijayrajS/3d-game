#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotationx = 0;
    this->rotationy = 0;
    this->rotationz = 0;
    this->fuel = 100;

    float phi = M_PI/3;

       GLfloat body_front[100000];
       for(int i = 0; i < 18*6 ; i+=18)
       {
           float u = i/18;
           body_front[i] = float(cos(u*phi));
           body_front[i + 1] = float(sin(u*phi));
           body_front[i + 2] = 0;

           body_front[i + 3] = float(cos(u * phi));
           body_front[i + 4] = float(sin(u * phi));
           body_front[i + 5] = 3;

           body_front[i + 6] = float(cos((u+1) * phi));
           body_front[i + 7] = float(sin((u+1) * phi));
           body_front[i + 8] = 3;

           body_front[i + 9] = float(1 * cos(u * phi));
           body_front[i + 10] = float(sin(u * phi));
           body_front[i + 11] = 0;

           body_front[i + 12] = float(cos((u + 1) * phi));
           body_front[i + 13] = float(sin((u + 1) * phi));
           body_front[i + 14] = 3;

           body_front[i + 15] = float(cos((u + 1) * phi));
           body_front[i + 16] = float(sin((u + 1) * phi));
           body_front[i + 17] = 0;
       }

       GLfloat body_back[100000];
       for (int i = 0; i < 18 * 6; i += 18)
       {
           float u = i / 18;
           body_back[i] = float(1 * cos(u * phi));
           body_back[i + 1] = 1 * float(sin(u * phi));
           body_back[i + 2] = 0;

           body_back[i + 3] = 1 * float(cos(u * phi));
           body_back[i + 4] = 1 * float(sin(u * phi));
           body_back[i + 5] = -3;

           body_back[i + 6] = 1 * float(cos((u + 1) * phi));
           body_back[i + 7] = 1 * float(sin((u + 1) * phi));
           body_back[i + 8] = -3;

           body_back[i + 9] = float(1 * cos(u * phi));
           body_back[i + 10] = 1 * float(sin(u * phi));
           body_back[i + 11] = 0;

           body_back[i + 12] = 1 * float(cos((u + 1) * phi));
           body_back[i + 13] = 1 * float(sin((u + 1) * phi));
           body_back[i + 14] = -3;

           body_back[i + 15] = 1 * float(cos((u + 1) * phi));
           body_back[i + 16] = 1 * float(sin((u + 1) * phi));
           body_back[i + 17] = 0;
       }

       GLfloat nose[100000];
       for (int i = 0; i < 9 * 6; i += 9)
       {
           float u = i / 9;
           nose[i] = float(1 * cos(u * phi));
           nose[i + 1] = 1 * float(sin(u * phi));
           nose[i + 2] = 3;

           nose[i + 3] = 0;
           nose[i + 4] = -0.5;
           nose[i + 5] = 5;

           nose[i + 6] = 1 * float(cos((u + 1) * phi));
           nose[i + 7] = 1 * float(sin((u + 1) * phi));
           nose[i + 8] = 3;
       }

       GLfloat wings[] = {
           1, 0, 2,
           1, 0, -2.5,
           5, 0, -2.5,
           -1, 0, 2,
           -1, 0, -2.5,
           -5, 0, -2.5,

           1, 0, -4,
           1, 0, -2.5,
           3, 0, -4,
           -1, 0, -4,
           -1, 0, -2.5,
           -3, 0, -4,

       };

    GLfloat wings2[] = {
           float(2*cos(phi)), float(2*sin(phi)), -3, 
           float(cos(phi)), float(sin(phi)), -3,
           float(cos(phi)), float(sin(phi)), -2.5,

           -float(2*cos(phi)), float(2*sin(phi)), -3, 
           -float(cos(phi)), float(sin(phi)), -3,
           -float(cos(phi)), float(sin(phi)), -2.5,
    };

     GLfloat cockpit[] = {
           float(cos(phi)), float(sin(phi)), 1,
           float(cos(phi)), float(sin(phi)+ 0.01) , 2.9,
           float(cos(2*phi)), float(sin(2*phi)), 2.9,  

           float(cos(2*phi)), float(sin(2*phi)), 2.9,  
           float(cos(2*phi)), float(sin(2*phi)+ 0.01), 1,
           float(cos(phi)), float(sin(phi)), 1,
       };

    GLfloat exhaust[1000];

    for(int i = 0; i < 9*6 ; i += 9)
       {
           float u = i/9;
           exhaust[i] = float(cos(u*phi));
           exhaust[i + 1] = float(sin(u*phi));
           exhaust[i + 2] = -3;

           exhaust[i + 3] = float(cos((u+1) * phi));
           exhaust[i + 4] = float(sin((u+1) * phi));
           exhaust[i + 5] = -3;

           exhaust[i + 6] = 0;
           exhaust[i + 7] = 0;
           exhaust[i + 8] = -3;
       }

       this->object1 = create3DObject(GL_TRIANGLES, 18*6, body_front, {221, 198, 143}, GL_FILL);
       this->object2 = create3DObject(GL_TRIANGLES, 18*6, body_back, {221, 198, 143}, GL_FILL);
       this->object3 = create3DObject(GL_TRIANGLES, 54, nose, {73, 69, 41}, GL_FILL);
       this->object4 = create3DObject(GL_TRIANGLES, 12, wings, {78, 72, 60}, GL_FILL);
       this->object5 = create3DObject(GL_TRIANGLES, 6, cockpit, {25, 35, 25}, GL_FILL);
       this->object6 = create3DObject(GL_TRIANGLES, 54, exhaust, {25, 25, 35}, GL_FILL);
       this->object7 = create3DObject(GL_TRIANGLES, 6, wings2, {75, 61, 28}, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef

    glm::mat4 rotate_x = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y = glm::rotate((float)(this->rotationy * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z = glm::rotate((float)(this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));

    // No need as coords centered at 0, 0, 0 of cube arouund which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));

    Matrices.model *= (translate * rotate_y * rotate_x * rotate_z);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
    float angle =  M_PI / 180.0f;

    glm::mat4 velocity = glm::rotate((float)(this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));
    velocity = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0))*velocity;
    velocity = glm::rotate((float)(this->rotationy * M_PI / 180.0f), glm::vec3(0, 1, 0))*velocity;

    glm::vec4 vel_vector = {0, 0, this->speed, 1};
    vel_vector = velocity * vel_vector;

    this->position.x += vel_vector[0];
    this->position.y += vel_vector[1];
    this->position.z += vel_vector[2];

    if(this->fuel < 0) this->fuel = 0;
}

bool Ball::sea_coll()
{
    float theta = M_PI/180.0f;
    return ((this->position.y + 3 * sin(theta * this->rotationx) < -1) ||
            (this->position.y - 3 * sin(theta * this->rotationx) < -1) ||
            (this->position.y + 3 * sin(theta * this->rotationz) < -1) ||
            (this->position.y - 3 * sin(theta * this->rotationz) < -1));
}
