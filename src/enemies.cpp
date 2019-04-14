#include "enemies.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->alive = 1;

    float l = 3, h = 3, b = 6;
    GLfloat g_vertex_buffer_data[] = {

        // Back face
         l/2, h/2, -b/2,
         l/2, -h/2, -b/2,
        -l/2, h/2, -b/2,
        -l/2, h/2, -b/2,
        -l/2, -h/2, -b/2,
         l/2, h/2, -b/2,

        // Front face
        l/2, h/2, b/2,
         l/2, -h/2, b/2,
        -l/2, h/2, b/2,
        -l/2, h/2, b/2,
        -l/2, -h/2, b/2,
         l/2, h/2, b/2,

        // Top face
        l/2, h/2, b/2,
        l/2, h/2, -b/2,
        -l/2, h/2, -b/2,
        -l/2, h/2, -b/2,
        -l/2, h/2, b/2,
        l/2, h/2, b/2,

        // Bottom face
        l/2, -h/2, b/2,
        l/2, -h/2, -b/2,
        -l/2, -h/2, -b/2,
        -l/2, -h/2, -b/2,
        -l/2, -h/2, b/2,
        l/2, -h/2, b/2,

        // Right face
        -l/2, -h/2, -b/2,
        -l/2, h/2, -b/2,
        -l/2, -h/2, b/2,
        -l/2, h/2, -b/2,
        -l/2, h/2, b/2,
        -l/2, -h/2, b/2,

         // Left face
        l/2, -h/2, -b/2,
        l/2, h/2, -b/2,
        l/2, -h/2, b/2,
        l/2, h/2, -b/2,
        l/2, h/2, b/2,
        l/2, -h/2, b/2,
    };

    GLfloat barrel[] = {
        // Front face
        -0.15, 1.5, -0.15,
        0.15, 5.5, -0.15, 
        -0.15, 5.5, -0.15, 
        0.15, 1.5, -0.15, 
        -0.15, 1.5, -0.15, 
        -0.15, 5.5, -0.15,

         // Back face
        -0.15, 1.5, 0.15,
        0.15, 5.5, 0.15,
        -0.15, 5.5, 0.15,
        0.15, 1.5, 0.15,
        -0.15, 5.5, 0.15,
        -0.15, 5.5, 0.15,

        // Right face
        -0.15, 1.5, -0.15,
        -0.15, 1.5, 0.15,
        -0.15, 5.5, 0.15,
        -0.15, 1.5, -0.15,
        -0.15, 5.5, 0.15,
        -0.15, 5.5, -0.15,

        // Left face
        0.15, 1.5, -0.15,
        0.15, 1.5, 0.15,
        0.15, 5.5, 0.15,
        0.15, 1.5, -0.15,
        0.15, 5.5, 0.15,
        0.15, 5.5, -0.15,
    };

    GLfloat land[] = 
    {
        8, -1.3, 8,
        8, -1.3, -8,
        -8, -1.3, 8,
        -8, -1.3, 8,
        8, -1.3, -8,
        -8, -1.3, -8,
    };

    this->object = create3DObject(GL_TRIANGLES, 36, g_vertex_buffer_data, {80, 165, 0}, GL_FILL);
    this->barrel = create3DObject(GL_TRIANGLES, 24, barrel, {163, 165, 0}, GL_FILL);
    this->land = create3DObject(GL_TRIANGLES, 6, land, {0, 50, 0}, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 100), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    if(this->alive)
    {
        draw3DObject(this->object);
        draw3DObject(this->barrel);
    }

    draw3DObject(this->land);
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
    // this->rotation = -fuel;
}

Para::Para(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    GLfloat body[] = {
        -1.0f, -1.0f, -1.0f, // triangle 1 : begin
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f, -1.0f, // triangle 2 : begin
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, // triangle 2 : end
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f
    };

    GLfloat head[] = {
        -1.0f, 0, -1.0f, // triangle 1 : begin
        -1.0f, 0, 1.0f,
        -1.0f, 2.0f, 1.0f, // triangle 1 : end
        1.0f, 2.0f, -1.0f, // triangle 2 : begin
        -1.0f, 0, -1.0f,
        -1.0f, 2.0f, -1.0f, // triangle 2 : end
        1.0f, 0, 1.0f,
        -1.0f, 0, -1.0f,
        1.0f, 0, -1.0f,
        1.0f, 2.0f, -1.0f,
        1.0f, 0, -1.0f,
        -1.0f, 0, -1.0f,
        -1.0f, 0, -1.0f,
        -1.0f, 2.0f, 1.0f,
        -1.0f, 2.0f, -1.0f,
        1.0f, 0, 1.0f,
        -1.0f, 0, 1.0f,
        -1.0f, 0, -1.0f,
        -1.0f, 2.0f, 1.0f,
        -1.0f, 0, 1.0f,
        1.0f, 0, 1.0f,
        1.0f, 2.0f, 1.0f,
        1.0f, 0, -1.0f,
        1.0f, 2.0f, -1.0f,
        1.0f, 0, -1.0f,
        1.0f, 2.0f, 1.0f,
        1.0f, 0, 1.0f,
        1.0f, 2.0f, 1.0f,
        1.0f, 2.0f, -1.0f,
        -1.0f, 2.0f, -1.0f,
        1.0f, 2.0f, 1.0f,
        -1.0f, 2.0f, -1.0f,
        -1.0f, 2.0f, 1.0f,
        1.0f, 2.0f, 1.0f,
        -1.0f, 2.0f, 1.0f,
        1.0f, 0, 1.0f
    };
    GLfloat chute[] = {
        4, 4, 3,
        4, 4, -3,
        -4, 4, 3,
        -4, 4, 3,
        4, 4, -3,
        -4, 4, -3,
    };

    GLfloat cord[] = {
        0,0,0,
        4, 4, -3,
        4, 4, 3,
        0,0,0,
        -4, 4, 3,
        -4, 4, -3,
   };

    this->object = create3DObject(GL_TRIANGLES, 36, body, {75, 144, 75}, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 36, head, {255, 130, 71}, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, chute, {110, 139, 61}, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 6, cord, {105, 139, 105}, GL_FILL);
}

void Para::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 100), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Para::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Para::tick()
{
    this->position.y -= 0.05;
}
