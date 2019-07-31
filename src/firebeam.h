#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H
#define GLM_ENABLE_EXPERIMENTAL 

class Firebeam {
public:
    Firebeam() {}
    Firebeam(float cx, float cy,float len,float wid,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float speedx;
    float len;
    float cx;
    float cy;
    float wid;
    float speedy;
    float acc;
private:
    VAO *object;
};


#endif // BALL_H
