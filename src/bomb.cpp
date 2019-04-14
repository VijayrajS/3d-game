#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z, float rx, float ry, float rz, int flag, float sp)
{
    this->position = glm::vec3(x, y, z);
    this->rotationx = rx;
    this->rotationy = ry;
    this->rotationz = rz;
    this->bm = flag;
    this->speed = 0.5*bm + sp;

    float phi = M_PI / 3;

    GLfloat body_front[100000];
    for (int i = 0; i < 18 * 6; i += 18)
    {
        float u = i / 18;
        body_front[i] = 0.5 * float(cos(u * phi));
        body_front[i + 1] = 0.5 * float(sin(u * phi));
        body_front[i + 2] = 0;

        body_front[i + 3] = 0.5 * float(cos(u * phi));
        body_front[i + 4] = 0.5 * float(sin(u * phi));
        body_front[i + 5] = 1;

        body_front[i + 6] = 0.5 * float(cos((u + 1) * phi));
        body_front[i + 7] = 0.5 * float(sin((u + 1) * phi));
        body_front[i + 8] = 1;

        body_front[i + 9] = 0.5 * float(1 * cos(u * phi));
        body_front[i + 10] = 0.5 * float(sin(u * phi));
        body_front[i + 11] = 0;

        body_front[i + 12] = 0.5 * float(cos((u + 1) * phi));
        body_front[i + 13] = 0.5 * float(sin((u + 1) * phi));
        body_front[i + 14] = 1;

        body_front[i + 15] = 0.5 * float(cos((u + 1) * phi));
        body_front[i + 16] = 0.5 * float(sin((u + 1) * phi));
        body_front[i + 17] = 0;
    }

    GLfloat body_back[100000];
    for (int i = 0; i < 18 * 6; i += 18)
    {
        float u = i / 18;
        body_back[i] = 0.5*float(1 * cos(u * phi));
        body_back[i + 1] = 0.5*float(sin(u * phi));
        body_back[i + 2] = 0;

        body_back[i + 3] = 0.5 * float(cos(u * phi));
        body_back[i + 4] = 0.5 * float(sin(u * phi));
        body_back[i + 5] = -1;

        body_back[i + 6] = 0.5 * float(cos((u + 1) * phi));
        body_back[i + 7] = 0.5 * float(sin((u + 1) * phi));
        body_back[i + 8] = -1;

        body_back[i + 9] = 0.5 * float(1 * cos(u * phi));
        body_back[i + 10] = 0.5 * float(sin(u * phi));
        body_back[i + 11] = 0;

        body_back[i + 12] = 0.5 * float(cos((u + 1) * phi));
        body_back[i + 13] = 0.5 * float(sin((u + 1) * phi));
        body_back[i + 14] = -1;

        body_back[i + 15] = 0.5 * float(cos((u + 1) * phi));
        body_back[i + 16] = 0.5 * float(sin((u + 1) * phi));
        body_back[i + 17] = 0;
    }

    GLfloat nose[100000];
    for (int i = 0; i < 9 * 6; i += 9)
    {
        float u = i / 9;
        nose[i] = 0.5 * float(cos(u * phi));
        nose[i + 1] = 0.5 * float(sin(u * phi));
        nose[i + 2] = 1;

        nose[i + 3] = 0.5 * float(cos((u + 1) * phi));
        nose[i + 4] = 0.5 * float(sin((u + 1) * phi));
        nose[i + 5] = 1;

        nose[i + 6] = 0;
        nose[i + 7] = 0;
        nose[i + 8] = 2;
    }

    GLfloat exhaust[1000];

    for (int i = 0; i < 9 * 6; i += 9)
    {
        float u = i / 9;
        exhaust[i] = 0.5 * float(cos(u * phi));
        exhaust[i + 1] = 0.5 * float(sin(u * phi));
        exhaust[i + 2] = -1;

        exhaust[i + 3] = 0.5 * float(cos((u + 1) * phi));
        exhaust[i + 4] = 0.5 * float(sin((u + 1) * phi));
        exhaust[i + 5] = -1;

        exhaust[i + 6] = 0;
        exhaust[i + 7] = 0;
        exhaust[i + 8] = -1;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 108, body_front, {88, 67, 12}, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 108, body_back, {88, 67, 12}, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 54, nose, {128, 128, 0}, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 54, exhaust, {255, 165, 0}, GL_FILL);
}

void Bomb::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef

    glm::mat4 rotate_x = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate_y = glm::rotate((float)(this->rotationy * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_z = glm::rotate((float)(this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));

    // No need as coords centered at 0, 0, 0 of cube arouund which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    if(bm < 2)
        Matrices.model *= (translate * rotate_y * rotate_x * rotate_z);
    
    else
        Matrices.model *= (translate * this->cannonb);

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Bomb::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick()
{
    if(this->bm == 1)
    {
        float angle = M_PI / 180.0f;

        glm::mat4 velocity = glm::rotate((float)(this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));
        velocity = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0)) * velocity;
        velocity = glm::rotate((float)(this->rotationy * M_PI / 180.0f), glm::vec3(0, 1, 0)) * velocity;

        glm::vec4 vel_vector = {0, 0, this->speed, 1};
        vel_vector = velocity * vel_vector;

        this->position.x += vel_vector[0];
        this->position.y += vel_vector[1];
        this->position.z += vel_vector[2];
    }

    else if (this-> bm == 0)
    {
        glm::mat4 velocity = glm::rotate((float)(this->rotationy * M_PI / 180.0f), glm::vec3(0, 1, 0));

        glm::vec4 vel_vector = {0, 0, this->speed, 1};
        vel_vector = velocity * vel_vector;

        this->position.x += vel_vector[0];
        this->position.y -= 0.2;
        this->position.z += vel_vector[2];
    }

    else
    {
        glm::vec4 vel_vector = {0, 0, this->speed, 1};
        vel_vector = this->cannonb * vel_vector;

        this->position.x += vel_vector[0];
        this->position.y += vel_vector[1];
        this->position.z += vel_vector[2];
    }
    
}

bool Bomb::sea_coll()
{
    float theta = M_PI / 180.0f;
    return ((this->position.y + 3 * sin(theta * this->rotationx) < -1) ||
            (this->position.y - 3 * sin(theta * this->rotationx) < -1) ||
            (this->position.y + 3 * sin(theta * this->rotationz) < -1) ||
            (this->position.y - 3 * sin(theta * this->rotationz) < -1));
}
