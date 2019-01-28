#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coin {
public:
    Coin() {}
    Coin(float x, float y, color_t color,int type);
    glm::vec3 position;
    int type;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick2();
    void powerup();
    void fire();
    double speed;
private:
    VAO *object;
};

#endif // COIN_H
