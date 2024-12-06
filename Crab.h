//
// Created by Dylan Beaumont on 31/10/2024.
//

#ifndef CRAB_H
#define CRAB_H
#include <array>

#include "Leg.h"
#include "raylib.h"


class Crab {
public:
    int radius;
    float WALK_SPEED = 2.0f;
    float angle;
    float speed;
    Texture2D texture;
    float turnRate = 0.04f;
    std::array<Leg, 6> legs;
    Vector2 pos;
    Crab(Vector2 pos, int radius, float angle, Texture2D texture);
    void Update();
    void Draw();
};



#endif //CRAB_H
