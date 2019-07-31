#include "main.h"
#include <bits/stdc++.h>

using namespace std;

#ifndef LIFE_H
#define LIFE_H
#define GLM_ENABLE_EXPERIMENTAL 

class Life {
public:
    Life() {}
    Life(float x,float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx;
    double speedy;
private:
    VAO *object;
    VAO *otr;
};


#endif // BALL_H
