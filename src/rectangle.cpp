#include "rectangle.h"
#include "main.h"

Rectangle::Rectangle(float x, float y, float z, float width, float height, float yw, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->width = width;
    this->height = height;
    GLfloat g_vertex_buffer_data[] = {
      width/2,  yw, height/2,
      width/2,  yw, -height/2,
      -width/2, yw, height/2,
      -width/2, yw, -height/2,
      -width/2, yw, height/2,
      width/2, yw, -height/2, 
    };

    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
}

void Rectangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rectangle::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Rectangle::tick() {
    this->position.x -= speed.x;
    this->position.y -= speed.y;
}

bounding_box_t Rectangle::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->width, this->height };
    return bbox;
}
