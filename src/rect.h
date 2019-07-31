#include "main.h"
#include <bits/stdc++.h>

using namespace std;

#ifndef RECT_H
#define RECT_H
#define GLM_ENABLE_EXPERIMENTAL 

class Rect {
public:
    Rect() {}
    Rect(vector<pair<float,float> > seg,float x,float y,color_t a,float sy);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx;
    double speedy;
private:
    VAO *object;
};


#endif // BALL_H
