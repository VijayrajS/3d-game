#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, float z, float rx, float rr, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rr;
    this->smokeon  = 1;

    GLfloat g_vertex_buffer_data2[100000]; // Body

    float phi = M_PI / 180;
    float r = rx;
    int angle = 0;

    for (int i = 0; i < 3240; i += 9)
    {
        g_vertex_buffer_data2[i] = r * cos(phi * angle);
        g_vertex_buffer_data2[i + 1] = r * sin(phi * angle);
        g_vertex_buffer_data2[i + 2] = 0;

        g_vertex_buffer_data2[i + 3] = r * cos(phi * (angle + 1));
        g_vertex_buffer_data2[i + 4] = r * sin(phi * (angle + 1));
        g_vertex_buffer_data2[i + 5] = 0;

        g_vertex_buffer_data2[i + 6] = 0;
        g_vertex_buffer_data2[i + 7] = 0;
        g_vertex_buffer_data2[i + 8] = 0;

        angle += 1;
    }

    this->object = create3DObject(GL_TRIANGLES, 1080, g_vertex_buffer_data2, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ring::tick() {
    // this->rotation -= speed;
}
