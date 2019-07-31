#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H
#define GLM_ENABLE_EXPERIMENTAL 

class Magnet {
public:
    Magnet() {}
    Magnet(float cx,float cy,color_t a,int offset);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx;
    float cx;
    float cy;
    double speedy;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};


#endif // BALL_H
