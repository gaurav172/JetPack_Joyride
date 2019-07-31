#include "ball.h"
#include "main.h"

using namespace std;


#define GLM_ENABLE_EXPERIMENTAL 
Ball::Ball(float x, float y,float sx,float sy,float acc, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speedx = sx;
    this->speedy=sy;
    this->acc=acc;
    this->accx=0;
    this->accym=0;
    this->col=color;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat JetPack[]={
        -0.5f,-0.2f,0.0f,
        -0.1f,-0.2f,0.0f,
        -0.5f,0.5f,0.0f,
        -0.5f,0.5f,0.0f,
        -0.1f,0.5f,0.0f,
        -0.1f,-0.2f,0.0f
    };
    GLfloat JetPack2[]={
        -0.5f,-0.3f,0.0f,
        -0.1f,-0.3f,0.0f,
        -0.3f,-0.5f,0.0f,
    };
     GLfloat Body[]={
        0.5f,-0.3f,0.0f,
        -0.1f,-0.3f,0.0f,
        0.5f,0.1f,0.0f,
        0.5f,0.1f,0.0f,
        -0.1f,0.1f,0.0f,
        -0.1f,-0.3f,0.0f
    };
    GLfloat vertex_buffer_data1[] = {
        -1.0f,1.0f,0.0f,
        -1.0f,-1.0,0.0f,
        1.0f,-1.0f,0.0f,
        1.0f,-1.0f,0.0f,
        1.0f,1.0f,0.0f,
        -1.0f,1.0f,0.0f
    };
    for(int i=0;i<18;i++)
    {
        vertex_buffer_data1[i]*=0.5;
    }
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, this->col, GL_FILL);
    this->Jet    = create3DObject(GL_TRIANGLES, 6, JetPack, COLOR_JET, GL_FILL);
    this->Body    = create3DObject(GL_TRIANGLES, 6, Body, COLOR_BODY, GL_FILL);
    this->Jet2    = create3DObject(GL_TRIANGLES, 3, JetPack2, COLOR_JET2, GL_FILL);    
     GLfloat vertex_buffer_data[10000];
    int n=1000;
    double sz=n,Pi=3.1415;Pi*=2;
    float r1=0.2,r2=0.2;
    float cx=0.2,cy=0.3;
    for(int i=0;i<(n);i++)
    {
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
    this->Head = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_SKIN2, GL_FILL);
    GLfloat Legs[]={
        0.05f,-0.3f,0.0f,
        -0.1f,-0.5f,0.0f,
        0.2f,-0.5f,0.0f,
        0.35f,-0.3f,0.0f,
        0.2f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f
    };
    this->Legs = create3DObject(GL_TRIANGLES, 6, Legs, COLOR_SKIN2, GL_FILL);
    
}
void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    draw3DObject(this->Jet);
    draw3DObject(this->Body);
    draw3DObject(this->Head);
    draw3DObject(this->Legs);
    if(this->fft==1)
        draw3DObject(this->Jet2);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    if(this->position.y<=-2.5 && this->speedy<0)
    {
        this->position.y==-2.5;
        this->speedy=0;
        this->acc=0;
    }
    if(this->position.y>-1.999)
    {
        this->acc=-0.001;
    }
    this->speedx+=this->accx;
    this->speedy+=(this->acc+this->accym);
    if(this->position.y+this->speedy>=3.5)
    {
        this->speedy=0;
        this->position.y=3.5;
    }
    this->position.y+=this->speedy;
    this->position.x+=this->speedx;
}


