#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H
#define GLM_ENABLE_EXPERIMENTAL 

class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx;
    float wid;
    double speedy;
    float cx;
    float cy;
    double acc;
private:
    VAO *object;
};


#endif // BALL_H
