#include "main.h"
#include "sevenseg.h"

Sevenseg::Sevenseg(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = glm::vec3(0, 0, 0);

    static const GLfloat A[] = {
        -0.09, 0.1, 0,
        -0.09, 0.09, 0,
         0.09, 0.09, 0,
         0.09, 0.09, 0, 
         0.09, 0.1, 0,
        -0.09, 0.09, 0,
    };

    static const GLfloat B[] = {
         -0.1, 0.1, 0,
         -0.1, 0, 0,
         -0.09, 0.1, 0,
         -0.09, 0.1, 0,
         -0.1, 0, 0,
         -0.09, 0, 0,
    };

    static const GLfloat C[] = {
         0.09, 0.1, 0,
         0.09, 0, 0,
         0.1, 0.1, 0,
         0.1, 0.1, 0,
         0.09, 0, 0,
         0.1, 0, 0,
    };

    static const GLfloat D[] = {
         0.09, 0.01, 0,
        -0.09, 0.01, 0,
        -0.09, -0.01, 0,
        -0.09, -0.01, 0,
         0.09, -0.01, 0,
         0.09, 0.01, 0,         
    };

    static const GLfloat E[] = {
         -0.09, 0, 0,
         -0.1, 0, 0,
         -0.1, -0.1, 0,
         -0.1, -0.1, 0,
         -0.09, -0.1, 0,
         -0.09, 0, 0,
    };

    static const GLfloat F[] = {
        0.1, 0, 0,
        0.09, 0, 0,
        0.09, -0.1, 0,
        0.09, -0.1, 0,
        0.1, -0.1, 0,
        0.1, 0, 0,
    };

    static const GLfloat G[] = {
         0.09, -0.09, 0,
        -0.09, -0.09, 0,
        -0.09, -0.1, 0,
        -0.09, -0.1, 0,
         0.09, -0.1, 0,
         0.09, -0.09, 0,
    };

    this->A = create3DObject(GL_TRIANGLES, 6, A, color, GL_FILL);
    this->B = create3DObject(GL_TRIANGLES, 6, B, color, GL_FILL);
    this->C = create3DObject(GL_TRIANGLES, 6, C, color, GL_FILL);
    this->D = create3DObject(GL_TRIANGLES, 6, D, color, GL_FILL);
    this->E = create3DObject(GL_TRIANGLES, 6, E, color, GL_FILL);
    this->F = create3DObject(GL_TRIANGLES, 6, F, color, GL_FILL);
    this->G = create3DObject(GL_TRIANGLES, 6, G, color, GL_FILL);
}

void Sevenseg::draw(glm::mat4 VP, int number)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    switch(number)
    {
        case 1:
        {
            draw3DObject(this->C);
            draw3DObject(this->F);
            break;
        }
        case 2:
        {
            draw3DObject(this->A);
            draw3DObject(this->C);
            draw3DObject(this->D);
            draw3DObject(this->E);
            draw3DObject(this->G);
            break;
        }
        case 3:
        {
            draw3DObject(this->A);
            draw3DObject(this->C);
            draw3DObject(this->D);
            draw3DObject(this->F);
            draw3DObject(this->G);
            break;
        }
        case 4:
        {
            draw3DObject(this->B);
            draw3DObject(this->C);
            draw3DObject(this->D);
            draw3DObject(this->F);
            break;
        }
        case 5:
        {
            draw3DObject(this->A);
            draw3DObject(this->B);
            draw3DObject(this->D);
            draw3DObject(this->F);
            draw3DObject(this->G);
            break;
        }
        case 6:
        {
            draw3DObject(this->A);
            draw3DObject(this->B);
            draw3DObject(this->D);
            draw3DObject(this->E);
            draw3DObject(this->F);
            draw3DObject(this->G);
            break;
        }
        case 7:
        {
            draw3DObject(this->A);
            draw3DObject(this->C);
            draw3DObject(this->F);
            break;
        }
        case 8:
        {
            draw3DObject(this->A);
            draw3DObject(this->B);
            draw3DObject(this->C);
            draw3DObject(this->D);
            draw3DObject(this->E);
            draw3DObject(this->F);
            draw3DObject(this->G);
            break;
        }
        case 9:
        {
            draw3DObject(this->A);
            draw3DObject(this->B);
            draw3DObject(this->C);
            draw3DObject(this->D);
            draw3DObject(this->F);
            draw3DObject(this->G);
            break;
        }
        case 0:
        {
            draw3DObject(this->A);
            draw3DObject(this->B);
            draw3DObject(this->C);
            draw3DObject(this->E);
            draw3DObject(this->F);
            draw3DObject(this->G);
            break;
        }
        default:
        {
            break;
        }
    }
}

void Sevenseg::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Sevenseg::tick()
{
    this->position.x -= speed.x;
    this->position.y -= speed.y;
}

bounding_box_t Sevenseg::bounding_box()
{
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = {x, y, 0.2, 0.2};
    return bbox;
}
