
#include "Loop.h"
#include <iostream>
Loop::Loop()
{
}

void Loop::Run()
{
    Init();
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
    CloseWindow();
}

void Loop::Init()
{
    InitWindow(screenWidth, screenHeight, "Title");
    SetTargetFPS(60);

    Paddle *player = new Paddle(Vector2{20, screenHeight / 2 - 60}, true);
    Paddle *opponenet = new Paddle(Vector2{screenWidth - 40, screenHeight / 2 - 60}, false);

    Ball *ball = new Ball();

    scene.AddToScene(Layers::ENTITY, player);
    scene.AddToScene(Layers::ENTITY, opponenet);
    scene.AddToScene(Layers::ENTITY, ball);
}

void Loop::AI()
{
    float angle = Dinzai::GetAngle(scene.renderables[Layers::ENTITY].at(1)->tComp.position, scene.renderables[Layers::ENTITY].at(2)->tComp.position);
    gameTimer += GetFrameTime();
    if (gameTimer >= 0.1)
    {
        if (angle >= 0.0)
        {
            scene.renderables[Layers::ENTITY].at(1)->tComp.direction.y = -1;
        }
        if (angle < -0.1)
        {
            scene.renderables[Layers::ENTITY].at(1)->tComp.direction.y = 1;
        }
        gameTimer = 0;
    }
}

inline void BallReset(Scene& scene)
{
    scene.renderables[Layers::ENTITY].at(2)->tComp.position = Vector2{screenWidth / 2, screenHeight / 2};
    scene.renderables[Layers::ENTITY].at(2)->tComp.direction = {1, 0};
    scene.renderables[Layers::ENTITY].at(2)->speed = 5;
}

void Loop::Score()
{
    if (didPlayerScore)
    {
        scene.renderables[Layers::ENTITY].at(0)->score++;
        scene.renderables[Layers::ENTITY].at(0)->SetScore();
        BallReset(scene);
        didPlayerScore = false;
    }
    if (didOpponenetScore)
    {
        scene.renderables[Layers::ENTITY].at(1)->score++;
        scene.renderables[Layers::ENTITY].at(1)->SetScore();
        BallReset(scene);
        didOpponenetScore = false;
    }
}

void Loop::Collision()
{
    if (scene.renderables[Layers::ENTITY].at(2)->tComp.position.x > screenWidth - scene.renderables[Layers::ENTITY].at(2)->tComp.radius)
    {
        didPlayerScore = true;
    }
    if (scene.renderables[Layers::ENTITY].at(2)->tComp.position.x < scene.renderables[Layers::ENTITY].at(2)->tComp.radius)
    {
        didOpponenetScore = true;
    }

    if (scene.renderables[Layers::ENTITY].at(2)->tComp.position.y < scene.renderables[Layers::ENTITY].at(2)->tComp.radius || scene.renderables[Layers::ENTITY].at(2)->tComp.position.y > screenHeight - scene.renderables[Layers::ENTITY].at(2)->tComp.radius)
    {
        scene.renderables[Layers::ENTITY].at(2)->tComp.direction.y *= -1;
    }

    if (scene.renderables[Layers::ENTITY].at(1)->tComp.position.y < 0 || scene.renderables[Layers::ENTITY].at(1)->tComp.position.y > screenHeight - scene.renderables[Layers::ENTITY].at(1)->tComp.size.y)
    {
        scene.renderables[Layers::ENTITY].at(1)->tComp.position = scene.renderables[Layers::ENTITY].at(1)->tComp.lastPosition;
    }
    else
    {
        scene.renderables[Layers::ENTITY].at(1)->tComp.lastPosition = scene.renderables[Layers::ENTITY].at(1)->tComp.position;
    }

    if (scene.renderables[Layers::ENTITY].at(0)->tComp.position.y < 0 || scene.renderables[Layers::ENTITY].at(0)->tComp.position.y > screenHeight - scene.renderables[Layers::ENTITY].at(0)->tComp.size.y)
    {
        scene.renderables[Layers::ENTITY].at(0)->tComp.position = scene.renderables[Layers::ENTITY].at(0)->tComp.lastPosition;
    }
    else
    {
        scene.renderables[Layers::ENTITY].at(0)->tComp.lastPosition = scene.renderables[Layers::ENTITY].at(0)->tComp.position;
    }

    if (CustomCollision(scene.renderables[Layers::ENTITY].at(0)->tComp, scene.renderables[Layers::ENTITY].at(2)->tComp))
    {
        scene.renderables[Layers::ENTITY].at(2)->speed += 1;
        scene.renderables[Layers::ENTITY].at(2)->tComp.direction.x = 1;
        scene.renderables[Layers::ENTITY].at(2)->tComp.direction.y = scene.renderables[Layers::ENTITY].at(0)->tComp.direction.y;
    }

    if (CustomCollision(scene.renderables[Layers::ENTITY].at(1)->tComp, scene.renderables[Layers::ENTITY].at(2)->tComp))
    {
        scene.renderables[Layers::ENTITY].at(2)->speed += 1;
        scene.renderables[Layers::ENTITY].at(2)->tComp.direction.x = -1;
        scene.renderables[Layers::ENTITY].at(2)->tComp.direction.y = scene.renderables[Layers::ENTITY].at(2)->tComp.direction.y;
    }
}

void Loop::Update()
{
    Score();
    Collision();
    AI();
    scene.UpdateScene();
}

void Loop::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    scene.DrawScene();
    EndDrawing();
}
