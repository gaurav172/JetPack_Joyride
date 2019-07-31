#include "main.h"

#ifndef BRICK_H
#define BRICK_H
#define GLM_ENABLE_EXPERIMENTAL 

class Brick {
public:
    Brick() {}
    Brick(color_t a,int offset);
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
