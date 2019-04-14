#include "needle.h"
#include "main.h"

Needle::Needle(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    GLfloat g_vertex_buffer_data[] = {
        0, 0.1, 0,
        0, -0.1, 0,
        -0.5, 0, 0,
    };

    this->object = create3DObject(GL_TRIANGLES, 3, g_vertex_buffer_data, color, GL_FILL);
}

void Needle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 100), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Needle::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Needle::tick(float fuel) {
    this->rotation = -fuel;
}

