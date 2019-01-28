#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, color_t color,int type);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void boom();
    void dragon();
    double speed;
    int type;
    int hit;
private:
    VAO *object1;
    VAO *object2;
};



#endif // ENEMY_H
