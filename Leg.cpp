//
// Created by Dylan Beaumont on 31/10/2024.
//

#include "Leg.h"
#include "raymath.h"
#include <complex>

Leg::Leg() {

}

Leg::Leg(Vector2 hip, float length, float angle, float stride) {
    this->hip = hip;
    this->length = length;
    this->angle = angle;
    this->knee = hip;
    this->foot = hip;
    this->knee.x += (length/2.0)*std::cos(angle);
    this->knee.y += (length/2.0)*std::sin(angle);
    this->foot.x += (length)*std::cos(angle);
    this->foot.y += (length)*std::sin(angle);
    this->stride = stride;
    this->plant = foot;
    this->vPlant = foot;
}

void Leg::Update() {
    vPlant = hip + Vector2{std::cos(angle), std::sin(angle)}*stride;
    if(Vector2Distance(vPlant, plant) > stride) {
        plant = vPlant;
    }
    float distanceToPlant = Vector2Distance(plant, foot);
    foot = foot  + Vector2Normalize(plant-foot) * std::min(10.0f, distanceToPlant);
    knee = hip + Vector2Normalize(knee-hip)*length/2.0f;
    knee = foot + Vector2Normalize(knee-foot)*length/2.0f;
}

void Leg::Draw(float jointSize, float limbThickness) {
    Vector2 points[3] = {foot, knee, hip};
    Color color = RED;
    color.r -= 20;
    color.g += 20;
    DrawSplineLinear(points, 3, limbThickness, color);
    DrawCircle(foot.x, foot.y, jointSize, color);
    DrawCircle(hip.x, hip.y, jointSize, color);
    DrawCircle(knee.x, knee.y, jointSize, color);
}


