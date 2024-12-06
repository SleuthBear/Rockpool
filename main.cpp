#include <iostream>

#include "Crab.h"
#include "raylib.h"
#include "raymath.h"
#include "Leg.h"
#include "Fish.h"
#include "Seaweed.h"

void ReadInput(Fish *player);
void UpdateCrab(Crab *crab, Fish *player);
float ConstrainAngle(float x);
float InverseConstrainAngle(float x);
void CheckCollision(Fish *fish, Seaweed *seaweed);

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Rockpool");
    float time = 0.0f;
    Texture2D crabSprite = LoadTexture("resources/crabSprite.png");
    Crab crab = Crab({400, 300}, 50, 3.141592/2, crabSprite);
    Color seaweedColor = GREEN;
    seaweedColor.a -= 50;
    Seaweed seaweed = {{400, 300}, 100, seaweedColor};
    int radii[10] = {17, 20, 20, 19, 18, 17, 12, 2, 2, 2};
    Fish fish = Fish(10, radii, {100, 300}, 15, GOLD);
    while(!WindowShouldClose()) {
        // Toggle Fullscreen
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
            int display = GetCurrentMonitor();
            if (IsWindowFullscreen()) {
                SetWindowSize(screenWidth, screenHeight);
            } else {
                SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
            }
            ToggleFullscreen();
        }

        SetTargetFPS(60);
        float deltaTime = GetFrameTime();
        time += deltaTime;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        crab.Update();
        UpdateCrab(&crab, &fish);
        crab.Draw();
        ReadInput(&fish);
        fish.Update(deltaTime);
        seaweed.Update(time);
        CheckCollision(&fish, &seaweed);
        seaweed.Draw();
        fish.Draw();
        EndDrawing();
    }

    CloseWindow();

}

void ReadInput(Fish *player) {
    if(player->timeUntilMove > 0) return;
    float x_speed = 0;
    float y_speed = 0;
    if(IsKeyDown(KEY_LEFT)) x_speed += -1;
    if(IsKeyDown(KEY_RIGHT)) x_speed += 1;
    if(IsKeyDown(KEY_UP)) y_speed += -1;
    if(IsKeyDown(KEY_DOWN)) y_speed += 1;

    if(x_speed != 0 && y_speed != 0) {
        player->angle = std::atan2(y_speed,x_speed);
        player->speed = std::max(player->speed, player->swimSpeed);
    } else if (x_speed != 0) {
        player->angle = std::atan2(y_speed,x_speed);
        player->speed = std::max(player->speed, player->swimSpeed);
    } else if (y_speed != 0) {
        player->angle = std::atan2(y_speed,x_speed);
        player->speed = std::max(player->speed, player->swimSpeed);
    }

    if(IsKeyPressed(KEY_SPACE) && player->timeUntilDodge <= 0) {
        player->speed = 20;
        player->timeUntilDodge = 1;
        player->timeUntilMove = 0.3;
        player->isDodging = true;
    }
}

void CheckCollision(Fish *fish, Seaweed *seaweed) {
    if(Vector2Distance(fish->body[1].pos, seaweed->pos) < seaweed->radius) {
        fish->inStealth = true;
        seaweed->CircleCollide(fish->head.pos, fish->head.radius);
        for(int i = 0; i < fish->nJoints; i++) {
            seaweed->CircleCollide(fish->body[i].pos, fish->body[i].radius);
        }
    } else {
        fish->inStealth = false;
    }
}

void UpdateCrab(Crab *crab, Fish *player) {
    if(!player->inStealth && Vector2Distance(crab->pos, player->head.pos) > 50) {
        float targetAngle = std::atan2((player->head.pos-crab->pos).y, (player->head.pos-crab->pos).x);
        if(std::abs(targetAngle - crab->angle) < 3.141592f/2.0f) {
            crab->speed = std::min(Vector2Distance(crab->pos, player->head.pos)/200, crab->WALK_SPEED);
        }
        crab->angle = targetAngle;
    }
}

float ConstrainAngle(float x) {
    if(x < 0) {
        x = 2*3.141592 - x;
    }
    return x;
}


float InverseConstrainAngle(float x) {
    x = std::fmod(x, 3.141592f*2.0f);
    if(x < 3.141592) {
        x = -x + 2.0f*3.141592f;
    }
    return x;
}

