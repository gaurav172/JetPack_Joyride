#include "boom.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

#define GLM_ENABLE_EXPERIMENTAL 
Boom::Boom(float cx,float cy,float theta,color_t a) {
    this->position = glm::vec3(cx, cy, 0);
    this->rotation = 0;
    this->speedx = -0.3;
    this->speedy = -0.03;
    this->cx=cx;
    this->cy=cy;
    this->theta=theta;
    // this->accy=-0.001;
    this->accx=0.004;
    float r1=1.5,r2=0.5;
    float Pi=3.1415;
    cx=0;cy=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        cx,cy,0.0f,
        cx+r2*sin(theta),cy+r2*cos(theta),0.0f,
        cx+r1*sin(theta-Pi/4),cy+r1*cos(theta-Pi/4),0.0f,
        cx,cy,0.0f,
        cx+r2*sin(theta),cy+r2*cos(theta),0.0f,
        cx+r1*sin(theta+Pi/4),cy+r1*cos(theta+Pi/4),0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data,a, GL_FILL);
}

void Boom::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 inv = glm::inverse (translate);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model = (translate * rotate);
    glm::mat4 MVP = (VP * Matrices.model);
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boom::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boom::tick() {
    // this->rotation += speed;

    this->speedy+=this->accy;
    this->speedx+=this->accx;
    this->position.y += this->speedy;
    this->position.x += this->speedx;
    this->cx += this->speedx;
    this->cy += this->speedy;
    this->rotation+=4;
}


