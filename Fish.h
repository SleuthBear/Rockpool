#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"

#ifndef FISH_H
#define FISH_H

const float SWIM_SPEED = 10.0f;

typedef struct Joint {
    Vector2 pos;
    int radius;
    float angle;
} Joint;


class Fish {
public:
    Fish(int joints, int *radii, Vector2 headPos, int headRadius, Color color);
    void Update(float deltaTime);
    void Draw();
    float timeUntilMove = 0;
    float timeUntilDodge = 0;
    bool isDodging;
    bool inStealth;
    float angle;
    float speed;
    int nJoints;
    Color color;
    float swimSpeed = 10.0f;
    Joint head;
    Joint *body;
};



#endif //FISH_H
