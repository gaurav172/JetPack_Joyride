#include "main.h"

#ifndef BALL_H
#define BALL_H
#define GLM_ENABLE_EXPERIMENTAL 

class Ball {
public:
    Ball() {}
    Ball(float x, float y,float sx,float sy,float acc ,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    color_t col;
    double speedx;
    double accx;
    double accym;
    double fft=0;
    double speedy;
    double acc;
private:
    VAO *object;
    VAO *Jet;
    VAO *Body;
    VAO * Head;
    VAO *Legs;
    VAO *Jet2;
};


#endif // BALL_H
