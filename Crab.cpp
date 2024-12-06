//
// Created by Dylan Beaumont on 31/10/2024.
//

#include "Crab.h"
#include "raylib.h"
#include "raymath.h"
#include <complex>
float const MATH_PI = 3.141592;

Crab::Crab(Vector2 pos, int radius, float angle, Texture2D texture) {

    this->radius = radius;
    this->angle = angle;
    this->pos = pos;
    this->texture = texture;
    this->legs[0] = Leg{pos + Vector2{std::cos(angle+MATH_PI/2.0f+0.5f), std::cos(angle+MATH_PI/2.0f)}*static_cast<float>(radius),1.0f*radius, angle+MATH_PI/2.0f, 1.0f*radius};
    this->legs[1] = Leg{pos + Vector2{std::cos(angle+MATH_PI/2.0f-1.0f), std::cos(angle+MATH_PI/2.0f-1.0f)}*static_cast<float>(radius),1.0f*radius, angle+MATH_PI/2.0f,1.0f*radius};
    this->legs[2] = Leg{pos + Vector2{std::cos(angle+MATH_PI/2.0f+1.0f), std::cos(angle+MATH_PI/2.0f+1.0f)}*static_cast<float>(radius),1.0f*radius, angle+MATH_PI/2.0f, 1.0f*radius};
    this->legs[3] = Leg{pos + Vector2{std::cos(angle-MATH_PI/2.0f-0.5f), std::cos(angle-MATH_PI/2.0f+0.5f)}*static_cast<float>(radius),1.0f*radius, angle-MATH_PI/2.0f,1.0f*radius};
    this->legs[4] = Leg{pos + Vector2{std::cos(angle-MATH_PI/2.0f-1.0f), std::cos(angle-MATH_PI/2.0f-1.0f)}*static_cast<float>(radius),1.0f*radius, angle-MATH_PI/2.0f,1.0f*radius};
    this->legs[5] = Leg{pos + Vector2{std::cos(angle-MATH_PI/2.0f+1.0f), std::cos(angle-MATH_PI/2.0f+1.0f)}*static_cast<float>(radius),1.0f*radius, angle-MATH_PI/2.0f,1.0f*radius};
}

void Crab::Update() {
    pos.x = pos.x + std::cos(angle)*speed;
    pos.y = pos.y + std::sin(angle)*speed;
    if(this->speed > WALK_SPEED*1.01) {
        this->speed -= WALK_SPEED/20;
    } else if(this->speed > 0){
        this->speed -= WALK_SPEED/10;
    }
    legs[0].hip = pos + Vector2{std::cos(angle+MATH_PI/2.0f+0.5f), std::sin(angle+MATH_PI/2.0f+0.5f)}*static_cast<float>(radius);;
    legs[1].hip = pos + Vector2{std::cos(angle+MATH_PI/2.0f+1.0f), std::sin(angle+MATH_PI/2.0f+1.0f)}*static_cast<float>(radius);
    legs[2].hip = pos + Vector2{std::cos(angle+MATH_PI/2.0f), std::sin(angle+MATH_PI/2.0f)}*static_cast<float>(radius);
    legs[3].hip = pos + Vector2{std::cos(angle-MATH_PI/2.0f-0.5f), std::sin(angle-MATH_PI/2.0f-0.5f)}*static_cast<float>(radius);
    legs[4].hip = pos + Vector2{std::cos(angle-MATH_PI/2.0f-1.0f), std::sin(angle-MATH_PI/2.0f-1.0f)}*static_cast<float>(radius);
    legs[5].hip = pos + Vector2{std::cos(angle-MATH_PI/2.0f), std::sin(angle-MATH_PI/2.0f)}*static_cast<float>(radius);
    legs[0].angle = angle + MATH_PI/2.0f-0.5f;
    legs[1].angle = angle + MATH_PI/2.0f-0.5f;;
    legs[2].angle = angle + MATH_PI/2.0f-0.5f;;
    legs[3].angle = angle - MATH_PI/2.0f+0.5f;;
    legs[4].angle = angle - MATH_PI/2.0f+0.5f;;
    legs[5].angle = angle - MATH_PI/2.0f+0.5f;;
    for(int i = 0; i < 6; i++) {
        legs[i].Update();
    }
}

void Crab::Draw() {
    Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destRec = {pos.x, pos.y, (float)radius*4, (float)radius*4};
    Vector2 origin = {(float)radius*2,(float)radius*2 };
    // DrawCircle(pos.x, pos.y, this->radius, ORANGE);
    for(int i = 0; i < 6; i++) {
        legs[i].Draw(radius/9.0f, radius/6.0f);
    }
    DrawTexturePro(texture, sourceRec, destRec, origin, angle*180/3.141592+90.0f, WHITE);

}