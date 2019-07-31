#include "main.h"

#ifndef COINS_H
#define COINS_H
#define GLM_ENABLE_EXPERIMENTAL 

class Coins {
public:
    Coins() {}
    Coins(float cx,float cy,double sx,double sy,double acc,color_t color,bool flag,float r1=0.5,float r2=0.5,int n=1000);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double cx;
    double cy;
    bool flag;
    color_t col;
    double speedx;
    double rad;
    double speedy;
    double acc;
private:
    VAO *object;
};


#endif // BALL_H
