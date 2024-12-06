//
// Created by Dylan Beaumont on 28/10/2024.
//

#include "Fish.h"

Fish::Fish(int joints, int *radii, Vector2 headPos, int headRadius, Color color) {
    this->nJoints = joints;
    this->speed = this->swimSpeed;
    this->angle = 0;
    this->inStealth = 0;
    this->body = new Joint[joints];
    this->color = color;
    Vector2 currentPos = headPos;
    this->head = Joint {currentPos, headRadius, 0};
    currentPos.x = currentPos.x - headRadius;
    for(int i = 0; i < joints; i++) {
        this->body[i] = Joint{currentPos, radii[i], 0};
        currentPos.x = currentPos.x-radii[0];
    }
}

void Fish::Update(float deltaTime) {
    // for(int i = 0; i < this->nJoints; i++) {
    //     std::cout << this->body[i].radius <<std::endl;
    // }
    // this->head.pos.x = 400 + 200*std::cos(deltaTime*1.5);
    // this->head.pos.y = 300 + 150*std::sin(deltaTime);
    this->head.pos.x = this->head.pos.x + std::cos(this->angle)*this->speed;
    this->head.pos.y = this->head.pos.y + std::sin(this->angle)*this->speed;
    if(this->timeUntilMove > 0) this->timeUntilMove -= deltaTime;

    if(this->speed > SWIM_SPEED*1.01) {
        this->speed -= SWIM_SPEED/20;
    } else if(this->speed > 0){
        this->speed -= SWIM_SPEED/10;
        this->isDodging = false;
    }

    if(this->timeUntilDodge > 0) {
        this->timeUntilDodge -= deltaTime;
    }

    this->body[0].pos = this->head.pos + Vector2Normalize(this->body[0].pos - this->head.pos) * this->head.radius;
    for(int i = 1; i < this->nJoints; i++) {
        this->body[i].pos = this->body[i-1].pos + Vector2Normalize(this->body[i].pos - this->body[i-1].pos) * std::max(this->body[i-1].radius, this->body[i].radius);
    }

    // head collision
    for(int i = 1; i < this->nJoints; i++) {
        if(Vector2Distance(this->head.pos, this->body[i].pos) < 40) {
            this->body[i].pos = this->head.pos + Vector2Normalize(this->body[i].pos - this->head.pos) * 40;
        }
    }
    // body collision and angle setting
    this->head.angle = std::atan2((this->head.pos-this->body[0].pos).y, (this->head.pos-this->body[0].pos).x);
    for(int i = 0; i < this->nJoints; i++) {
        if(i == 0) this->body[i].angle = std::atan2((this->head.pos-this->body[0].pos).y, (this->head.pos-this->body[0].pos).x);
        else this->body[i].angle = std::atan2((this->body[i-1].pos-this->body[i].pos).y, (this->body[i-1].pos-this->body[i].pos).x);
        for(int j = i+2; j < this->nJoints; j++) {
            if(Vector2Distance(this->body[i].pos, this->body[j].pos) < 40) {
                this->body[j].pos = this->body[i].pos + Vector2Normalize(this->body[j].pos - this->body[i].pos) * 40;
        }
    }
    }

}

void Fish::Draw() {
    Color color = this->color;
    if(inStealth) {
        color = GRAY;
        color.a -= 100;
        std::vector<Vector2> points;
        points.push_back(this->head.pos + Vector2{this->head.radius*std::cos(this->head.angle), this->head.radius*std::sin(this->head.angle)});
        points.push_back(this->head.pos + Vector2{this->head.radius*std::cos(this->head.angle+3.141592f/2.0f), this->head.radius*std::sin(this->head.angle+3.141592f/2.0f)});
        // get all left sides points
        for(int i = 0; i < this->nJoints; i++) {
            if(i == 1) {
                points.push_back(this->body[i].pos + Vector2{this->body[i].radius*std::cos(this->body[i].angle+2.8f/2.0f), this->body[i].radius*std::sin(this->body[i].angle+2.8f/2.0f)});
                points.push_back(this->body[i].pos + Vector2{2*this->body[i].radius*std::cos(this->body[i].angle+0.5f+3.141592f/2.0f), 2*this->body[i].radius*std::sin(this->body[i].angle+0.5f+3.141592f/2.0f)});
                points.push_back(this->body[i].pos + Vector2{this->body[i].radius*std::cos(this->body[i].angle+3.4f/2.0f), this->body[i].radius*std::sin(this->body[i].angle+3.4f/2.0f)});
            } else {
                points.push_back(this->body[i].pos + Vector2{this->body[i].radius*std::cos(this->body[i].angle+3.141592f/2.0f), this->body[i].radius*std::sin(this->body[i].angle+3.141592f/2.0f)});
            }
        }
        // get all right sides points
        for(int i = this->nJoints - 1; i > 0; i--) {
            if(i == 1) {
                points.push_back(this->body[i].pos + Vector2{this->body[i].radius*std::cos(this->body[i].angle-2.8f/2.0f), this->body[i].radius*std::sin(this->body[i].angle-2.8f/2.0f)});
                points.push_back(this->body[i].pos + Vector2{2*this->body[i].radius*std::cos(this->body[i].angle-0.5f-3.141592f/2.0f), 2*this->body[i].radius*std::sin(this->body[i].angle-0.5f-3.141592f/2.0f)});
                points.push_back(this->body[i].pos + Vector2{this->body[i].radius*std::cos(this->body[i].angle-3.4f/2.0f), this->body[i].radius*std::sin(this->body[i].angle-3.4f/2.0f)});
            } else {
                points.push_back(this->body[i].pos + Vector2{this->body[i].radius*std::cos(this->body[i].angle-3.141592f/2.0f), this->body[i].radius*std::sin(this->body[i].angle-3.141592f/2.0f)});

            }
        }
        points.push_back(this->head.pos + Vector2{this->head.radius*std::cos(this->head.angle-3.141592f/2.0f), this->head.radius*std::sin(this->head.angle-3.141592f/2.0f)});
        points.push_back(this->head.pos + Vector2{this->head.radius*std::cos(this->head.angle), this->head.radius*std::sin(this->head.angle)});
        DrawSplineLinear(points.data(), points.size(), 3, BLACK);
    }

    Vector2 point[4];
    point[2] = (this->head.pos + Vector2{this->head.radius*std::cos(this->head.angle), this->head.radius*std::sin(this->head.angle)});
    point[1] = (this->head.pos + Vector2{this->head.radius*std::cos(this->head.angle+3.141592f/2.0f), this->head.radius*std::sin(this->head.angle+3.141592f/2.0f)});
    point[0] = (this->head.pos + Vector2{this->head.radius*std::cos(this->head.angle-3.141592f/2.0f), this->head.radius*std::sin(this->head.angle-3.141592f/2.0f)});
    DrawTriangle(point[2], point[0], point[1], color);
    for(int i = 0; i < nJoints; i++) {
        point[3] = point[1];
        point[2] = point[0];
        point[0] = (this->body[i].pos + Vector2{this->body[i].radius*std::cos(this->body[i].angle-3.141592f/2.0f), this->body[i].radius*std::sin(this->body[i].angle-3.141592f/2.0f)});
        point[1] = (this->body[i].pos + Vector2{this->body[i].radius*std::cos(this->body[i].angle+3.141592f/2.0f), this->body[i].radius*std::sin(this->body[i].angle+3.141592f/2.0f)});
        DrawTriangle(point[3], point[2], point[0], color);
        DrawTriangle(point[3], point[0], point[1], color);
    }

    Vector2 finStart = (this->body[1].pos + Vector2{this->body[1].radius*std::cos(this->body[1].angle-3.141592f/2.0f), this->body[1].radius*std::sin(this->body[1].angle-3.141592f/2.0f)});
    Vector2 finTip = body[1].pos + Vector2{2*this->body[1].radius*std::cos(this->body[1].angle-0.5f-3.141592f/2.0f), 2*this->body[1].radius*std::sin(this->body[1].angle-0.5f-3.141592f/2.0f)};
    DrawSplineSegmentLinear(finStart, finTip, 5, color);

    finStart = (body[1].pos + Vector2{this->body[1].radius*std::cos(this->body[1].angle+3.141592f/2.0f), this->body[1].radius*std::sin(this->body[1].angle+3.141592f/2.0f)});
    finTip = body[1].pos + Vector2{2*this->body[1].radius*std::cos(this->body[1].angle+0.5f+3.141592f/2.0f), 2*this->body[1].radius*std::sin(this->body[1].angle+0.5f+3.141592f/2.0f)};
    DrawSplineSegmentLinear(finStart, finTip, 5, color);


}