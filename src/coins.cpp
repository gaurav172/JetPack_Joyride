#include "coins.h"
#include "main.h"
// #include<bits/stdc++.h>

using namespace std;
#define GLM_ENABLE_EXPERIMENTAL 
Coins::Coins(float cx,float cy,double sx,double sy,double acc,color_t a,bool flag,float r1,float r2,int n) {
    if(flag)
    {
        r1*=0.7;
        r2*=0.7;
    }
    this->position = glm::vec3(cx, cy, 0);
    this->rotation = 0;
    this->speedx = sx;
    this->speedy=sy;
    this->cx=cx;
    this->cy=cy;
    this->flag=flag;
    this->rad=r2;
    this->acc=acc;
    this->col=a;
    cx=0;cy=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[10000];
    double sz=n,Pi=3.1415;Pi*=2;
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

void Coins::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coins::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coins::tick() {
    if(this->speedx==0 && this->speedy==0 && flag)
        this->rotation +=2;
    this->speedy+=this->acc;
    this->cx+=this->speedx;
    this->cy+=this->speedy;
    this->position.x+=this->speedx;
    this->position.y += this->speedy;
}


