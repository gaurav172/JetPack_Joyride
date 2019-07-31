#include "dragon.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL 
Dragon::Dragon(float cx,color_t a) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->speedx = 0;
    this->speedy=0.02;
    cy=1;
    this->cx=cx;
    this->cy=1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        cx,cy,0.0f,
        cx-1.0f,cy-1.0f,0.0f,
        cx,cy-1.0f,0.0f,
        cx,cy,0.0f,
        cx-1.0f,cy-2.0f,0.0f,
        cx,cy-2.0f,0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data,a, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick() {
    // this->rotation += speed;
    if(this->cy+this->speedy>=4 && this->speedy>0)
        this->speedy*=-1;
    if(this->cy+this->speedy<=-1 && this->speedy<0)
        this->speedy*=-1;
    this->position.x+=this->speedx;
    this->position.y += this->speedy;
    this->cx+=this->speedx;
    this->cy+=this->speedy;
}


