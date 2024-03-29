#include "brick.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL 
Brick::Brick(color_t a,int offset) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->speedx = 0;
    this->speedy=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -4.0f,-3.0f,0.0f,
        -4.0f,-4.0,0.0f,
        -3.0f,-4.0f,0.0f,
        -3.0f,-4.0f,0.0f,
        -3.0f,-3.0f,0.0f,
        -4.0f,-3.0f,0.0f
    };
    GLfloat vertex_buffer_data1[10000];
    int sz=18;
    for(int i=0;i<18*(100);i++)
    {
        if(i%3==0)
            vertex_buffer_data1[i]=vertex_buffer_data[i%18]+2*(i/sz)+offset-10;
        else
            vertex_buffer_data1[i]=vertex_buffer_data[i%18];
    }
    this->object = create3DObject(GL_TRIANGLES, 6*(100), vertex_buffer_data1,a, GL_FILL);
}

void Brick::draw(glm::mat4 VP) {
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

void Brick::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Brick::tick() {
    // this->rotation += speed;
    this->position.x+=this->speedx;
    this->position.y += this->speedy;
}


