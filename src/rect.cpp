#include "rect.h"
#include "main.h"
#include <bits/stdc++.h>

#define GLM_ENABLE_EXPERIMENTAL 
Rect::Rect(vector<pair<float,float> > seg,float x,float y,color_t a,float sy) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->speedx = 0;
    this->speedy=sy;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[100];
    vertex_buffer_data[0]=seg[0].first+x;
    vertex_buffer_data[1]=seg[0].second+y;
    vertex_buffer_data[2]=0;
    vertex_buffer_data[3]=seg[1].first+x;
    vertex_buffer_data[4]=seg[1].second+y;
    vertex_buffer_data[5]=0;
    vertex_buffer_data[6]=seg[2].first+x;
    vertex_buffer_data[7]=seg[2].second+y;
    vertex_buffer_data[8]=0;
    vertex_buffer_data[9]=seg[1].first+x;
    vertex_buffer_data[10]=seg[1].second+y;
    vertex_buffer_data[11]=0;
    vertex_buffer_data[12]=seg[2].first+x;
    vertex_buffer_data[13]=seg[2].second+y;
    vertex_buffer_data[14]=0;
    vertex_buffer_data[15]=seg[3].first+x;
    vertex_buffer_data[16]=seg[3].second+y;
    vertex_buffer_data[17]=0;
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data,a, GL_FILL);
}

void Rect::draw(glm::mat4 VP) {
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

void Rect::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rect::tick() {
    // this->rotation += speed;
    this->position.x+=this->speedx;
    this->position.y += this->speedy;
}


