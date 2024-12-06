//
// Created by Dylan Beaumont on 2/11/2024.
//

#ifndef SEAWEED_H
#define SEAWEED_H
#include "raylib.h"


class Seaweed {
public:
    int nStrands;
    Vector2 *tips;
    Vector2 *bases;
    Vector2 pos;
    int radius;
    int strandRadius;
    Color color;
    Color lineColor;
    Seaweed(Vector2 pos, int radius, Color color);
    void Draw();
    void Update(float time);
    void CircleCollide(Vector2 pos, int radius);

};



#endif //SEAWEED_H
