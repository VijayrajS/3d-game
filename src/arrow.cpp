#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.5;
    GLfloat g_vertex_buffer_data[] = {
        
        // Arrowhead square
        1, 0, 1,
        -1, 0, 1,
        1, 0, -1,
        1, 0, -1, 
        -1, 0, -1,
        -1, 0, 1,

        // Arrowhead
        1, 0, -1,
        0, -2, 0,
        1, 0, 1,
        1, 0, 1,
        0, -2, 0,
        -1, 0, 1,
        -1, 0, 1,        
        0, -2, 0,
        -1, 0, -1,
        -1, 0, -1,
        0, -2, 0,
        1, 0, -1,

        // Tail
        0.5, 0, 0.5,
        0.5, 0, -0.5,
        0.5, 1, 0.5,
        0.5, 1, 0.5,
        0.5, 1, -0.5,
        0.5, 0, -0.5,

        0.5, 0, 0.5,
        -0.5, 0, 0.5,
        -0.5, 1, 0.5,
        -0.5, 1, 0.5,
        0.5, 1, 0.5,
        0.5, 0, 0.5,

        -0.5, 1, 0.5,
        -0.5, 0, 0.5,
        -0.5, 0, -0.5,
        -0.5, 0, -0.5,
        -0.5, 1, -0.5,
        -0.5, 1, 0.5,

        -0.5, 1, -0.5,
        -0.5, 0, -0.5,
        0.5, 0, -0.5,
        0.5, 0, -0.5,
        -0.5, 1, -0.5,
        0.5, 1, -0.5,
    };

    this->object = create3DObject(GL_TRIANGLES, 42, g_vertex_buffer_data, color, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick() {
    this->rotation -= speed;
}

bounding_box_t Arrow::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->width, this->height };
    return bbox;
}
