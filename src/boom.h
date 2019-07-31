#include "main.h"
#include <bits/stdc++.h>

using namespace std;

#ifndef BOOM_H
#define BOOM_H
#define GLM_ENABLE_EXPERIMENTAL 

class Boom {
public:
    Boom() {}
    Boom(float cx,float cy,float theta,color_t a);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx;
    double accx;
    float theta;
    double accy;
    float cx;
    float cy;
    double speedy;
private:
    VAO *object;
};


#endif // BALL_H
