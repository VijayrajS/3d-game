#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    GLfloat mountain[] = {
        70.7/2, 0/2, 70.7/2,
        0/2, 50/2, 0/2,
        -70.7/2, 0/2, 70.7/2,
        -70.7/2, 0/2, 70.7/2,
        0/2, 50/2, 0/2,
        -70.7/2, 0/2, -70.7/2,
        -70.7/2, 0/2, -70.7/2,
        0/2, 50/2, 0/2,
        -70.7/2, 0/2, -70.7/2,
        -70.7/2, 0/2, -70.7/2,
        0/2, 50/2, 0/2,
        70.7/2, 0/2, -70.7/2,
        70.7/2, 0/2, -70.7/2,
        0/2, 50/2, 0/2,
        70.7/2, 0/2, 70.7/2,
    };

    GLfloat lava[] = {
        70.7/2, 1/2, 15/2,
        0/2, 50/2, 0/2,
        70.7/2, 1/2, -15/2,
        -70.7/2, 1/2,-15/2,
        0/2, 50/2, 0/2,
        -70.7/2, 1/2, 15/2,
        15/2, 1/2, 70.7/2,
        0/2, 50/2, 0/2,
        -15/2, 1/2, 70.7/2,
        -15/2, 1/2, -70.7/2,
        0/2, 50/2, 0/2,
        15/2, 1/2, -70.7/2,
    };

    GLfloat smoke[5000];
    float phi = M_PI / 3;

    for (int i = 0; i < 9 * 6; i += 9)
    {
        float u = i / 9;
        smoke[i] = 10*float(cos(u * phi));
        smoke[i + 1] = 100/2;
        smoke[i + 2] = 10*float(sin(u * phi));

        smoke[i + 3] = 0;
        smoke[i + 4] = 50/2;
        smoke[i + 5] = 0;

        smoke[i + 6] = 10*float(cos((u + 1) * phi));
        smoke[i + 7] = 100/2;
        smoke[i + 8] = 10*float(sin((u + 1) * phi));
    }

    this->mnt = create3DObject(GL_TRIANGLES, 15, mountain, {88, 93, 99}, GL_FILL);
    this->lava = create3DObject(GL_TRIANGLES, 12, lava, {255, 0, 0}, GL_FILL);
    this->smk = create3DObject(GL_TRIANGLES, 18, smoke, {139, 131, 120}, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->smk);
    draw3DObject(this->mnt);
    draw3DObject(this->lava);
}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Volcano::tick() {
    // this->rotation -= speed;
}

bounding_box_t Volcano::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->width, this->height };
    return bbox;
}
