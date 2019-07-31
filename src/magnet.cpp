#include "magnet.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL 
Magnet::Magnet(float cx,float cy,color_t a,int offset) {
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->speedx = 0;
    this->speedy=0;
    this->cx=cx;
    this->cy=cy;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        cx+0.5f,3.0f,0.0f,
        cx+0.5f,1.5f,0.0f,
        cx+0.7f,1.5f,0.0f,
        cx+0.7f,1.5f,0.0f,
        cx+0.7f,3.0f,0.0f,
        cx+0.5f,3.0f,0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data,a, GL_FILL);
      GLfloat vertex_buffer_data1[] = {
        cx-0.5f,3.0f,0.0f,
        cx-0.5f,2.8f,0.0f,
        cx+0.5f,2.8f,0.0f,
        cx+0.5f,2.8f,0.0f,
        cx+0.5f,3.0f,0.0f,
        cx-0.5f,3.0f,0.0f
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1,a, GL_FILL);
      GLfloat vertex_buffer_data2[] = {
        cx-0.5f,1.7f,0.0f,
        cx-0.5f,1.5f,0.0f,
        cx+0.5f,1.5f,0.0f,
        cx+0.5f,1.5f,0.0f,
        cx+0.5f,1.7f,0.0f,
        cx-0.5f,1.7f,0.0f
    };
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2,a, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // this->rotation += speed;
    this->position.x+=this->speedx;
    this->cx+=this->speedx;
    this->cy+=this->speedy;
    this->position.y += this->speedy;
}


