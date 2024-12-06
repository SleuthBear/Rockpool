//
// Created by Dylan Beaumont on 31/10/2024.
//

#ifndef LEG_H
#define LEG_H
#include "raylib.h"


class Leg {
public:
  float angle;
  float length;
  Vector2 hip;
  Vector2 knee;
  Vector2 foot;
  Vector2 plant;
  Vector2 vPlant;
  float stride;
  Leg();
  Leg(Vector2 hip, float length, float angle, float stride);
  void Update();
  void Draw(float jointSize, float limbThickness);
};



#endif //LEG_H
