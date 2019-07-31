#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H
#define GLM_ENABLE_EXPERIMENTAL 

class Dragon {
public:
    Dragon() {}
    Dragon(float cx,color_t a);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx;
    double speedy;
    float cx;
    float cy;
private:
    VAO *object;
};


#endif // BALL_H
