//
// Created by Dylan Beaumont on 2/11/2024.
//

#include "Seaweed.h"
#include <complex>
#include <iostream>
#include <random>
#include "raymath.h"

Seaweed::Seaweed(Vector2 pos, int radius, Color color) {
    std::random_device rd;     // Only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(0,radius); // Guaranteed unbiased
    this->color = color;
    this->pos = pos;
    this->radius = radius;
    this->lineColor = color;
    this->nStrands = 6*static_cast<int>(std::sqrt(static_cast<float>(radius)));
    this->strandRadius = 6*radius/this->nStrands;
    lineColor.r = std::max(lineColor.r-100, 0);
    lineColor.g = std::max(lineColor.g-100, 0);
    lineColor.b = std::max(lineColor.b-100, 0);
    this->bases = new Vector2[nStrands];
    this->tips = new Vector2[nStrands];
    int distance;
    float angle;
    for(int i = 0; i < nStrands; i++) {
        distance = uni(rng);
        angle = (std::rand() % 200 - 100)/100.0f * 2*3.141592;
        bases[i] = {pos.x + distance*std::cos(angle), pos.y + distance*std::sin(angle)};
        tips[i] = {pos.x + distance*std::cos(angle), pos.y + distance*std::sin(angle)};
    }
}

void Seaweed::Update(float time) {

    for(int i = 0; i < nStrands; i++) {
        tips[i] = tips[i] + Vector2{std::cos(time)*strandRadius/50,std::cos(time)*strandRadius/100 };
        if(Vector2Distance(tips[i], bases[i]) > 2*strandRadius) {
            tips[i] = tips[i] + Vector2Normalize(bases[i]-tips[i])*std::min(Vector2Distance(bases[i], tips[i]), 1.0f);
        }

        for(int j = 0; j < nStrands; j++) {
            if (i != j) {
                if(Vector2Distance(tips[i], tips[j]) < 2*strandRadius) {
                    this->tips[i] = tips[j] + Vector2Normalize(tips[i] - tips[j]) * 2*strandRadius;
                }
           }
       }
    }
}

void Seaweed::CircleCollide(Vector2 point, int radius) {
    if(Vector2Distance(point, pos) < radius + this->radius) {
        for(int k = 0; k < 1; k++) {
            for(int i = 0; i < nStrands; i++) {
                if(Vector2Distance(point, tips[i]) < strandRadius + radius )
                    this->tips[i] = point + Vector2Normalize(tips[i] - point) * (strandRadius + radius);
            }
        }
    }


}

void Seaweed::Draw() {
    DrawCircleLines(pos.x, pos.y, radius, BLACK);
    for(int i = 0; i < nStrands; i++) {
        Vector2 points[2] = {tips[i], bases[i]};
        DrawCircle(bases[i].x, bases[i].y, strandRadius, lineColor);
        DrawSplineLinear(points, 2,  2*strandRadius, lineColor);

    }
    for(int i = 0; i < nStrands; i++) {
        DrawCircle(tips[i].x, tips[i].y, strandRadius, color);
    }
}