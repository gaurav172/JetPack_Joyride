#include "main.h"

#ifndef RING_H
#define RING_H
#define GLM_ENABLE_EXPERIMENTAL 

class Ring {
public:
    Ring() {}
    Ring(float cx,float cy,float r,color_t a);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float cx;
    float cy;
    float r;
private:
    VAO *object;
};


#endif // BALL_H
