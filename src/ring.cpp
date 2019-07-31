#include "ring.h"
#include "main.h"
// #include<bits/stdc++.h>

using namespace std;
#define GLM_ENABLE_EXPERIMENTAL 
Ring::Ring(float cx,float cy,float r,color_t a) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->cx=cx;
    this->cy=cy;
    this->r=r;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[10000];
    float r1=r,r2=r;
    int n=1000;
    double sz=1000,Pi=3.1415;Pi=-M_PI;
    for(int i=0;i<(n);i++)
    {
        swap(r1,r2);
        vertex_buffer_data[9*i]=cx;
        vertex_buffer_data[9*i+1]=cy;
        vertex_buffer_data[9*i+2]=0;
        vertex_buffer_data[9*i+3]=cx+(r1*cos((Pi*i)/sz));
        vertex_buffer_data[9*i+4]=cy+(r1*(sin((Pi*i)/sz)));
        vertex_buffer_data[9*i+5]=0;
        vertex_buffer_data[9*i+6]=cx+(r2*cos((Pi*((i+1)%n)/sz)));
        vertex_buffer_data[9*i+7]=cy+(r2*(sin((Pi*((i+1)%n)/sz))));
        vertex_buffer_data[9*i+8]=0;
    }
        this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, a, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
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

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
    // this->rotation += speed;
    // this->speedy+=this->acc;
    // this->cx+=this->speedx;
    // this->cy+=this->speedy;
    // this->position.x+=this->speedx;
    // this->position.y += this->speedy;
}


