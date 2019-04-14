#include "cube.h"
#include "main.h"

Cube::Cube(float x, float y, float z, float l, float b, float h, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->length = l;
    this->height = h;
    this->breadth = b;
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

    this->object = create3DObject(GL_TRIANGLES, 36, g_vertex_buffer_data, color, GL_FILL);
}

void Cube::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cube::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cube::tick() {
    this->position.x -= speed.x;
    this->position.y -= speed.y;
}

bounding_box_t Cube::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->length, this->height };
    return bbox;
}
