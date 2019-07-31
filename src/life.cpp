#include "life.h"
#include "main.h"
#include <bits/stdc++.h>

#define GLM_ENABLE_EXPERIMENTAL 
Life::Life(float x,float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speedx = 0;
    this->speedy=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
 GLfloat vertex_buffer_data[10000];
    int n=500;
    double sz=500,Pi=3.1415;Pi=M_PI;
    float r1=0.2,r2=0.2;
    float cx=-r1+0.01,cy=0;
    int j=0;
    for(int i=0;i<(2*n);i++,j++)
    {
        if(i==n)
        {
            cx=r1-0.01;
            j=0;
        }
        swap(r1,r2);
        vertex_buffer_data[9*i]=cx;
        vertex_buffer_data[9*i+1]=cy;
        vertex_buffer_data[9*i+2]=0;
        vertex_buffer_data[9*i+3]=cx+(r1*cos((Pi*j)/sz));
        vertex_buffer_data[9*i+4]=cy+(r1*(sin((Pi*j)/sz)));
        vertex_buffer_data[9*i+5]=0;
        vertex_buffer_data[9*i+6]=cx+(r2*cos((Pi*((j+1)%n)/sz)));
        vertex_buffer_data[9*i+7]=cy+(r2*(sin((Pi*((j+1)%n)/sz))));
        vertex_buffer_data[9*i+8]=0;
    }
    int i=18*n;
    vertex_buffer_data[i]=-r1+0.01-r1;
    i++;
     vertex_buffer_data[i]=0;
    i++;
     vertex_buffer_data[i]=0;
    i++;
     vertex_buffer_data[i]=r1-0.01+r1;
    i++;
     vertex_buffer_data[i]=0;
    i++;
     vertex_buffer_data[i]=0;
    i++;
     vertex_buffer_data[i]=0;
    i++;
     vertex_buffer_data[i]=-0.5f;
    i++;
     vertex_buffer_data[i]=0;
    i++;
    this->object = create3DObject(GL_TRIANGLES, 6*n+3, vertex_buffer_data, COLOR_RED, GL_FILL);
     GLfloat vertex_buffer_data1[10000];
    n=500;
    sz=n,Pi=3.1415;Pi*=2;
    r1=0.5;r2=0.5;cx=0;cy=-0.1;
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
        this->otr = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_SKIN, GL_FILL);
}

void Life::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->otr);
    draw3DObject(this->object);

}

void Life::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Life::tick() {
    // this->rotation += speed;
    this->position.x+=this->speedx;
    this->position.y += this->speedy;
}


