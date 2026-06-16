#include "Entity.h"
#include <iostream>
UI::UI(int score, Vector2 position)
{
    this->position = position;
    SetText(score);
}

void UI::SetText(int score)
{
    theScore = score;
    scoreText = "Score: ";
    std::string newString = std::to_string(theScore);
    scoreText.append(newString);
    std::cout << "Score: " << scoreText << '\n';
}

void UI::Draw()
{
    DrawText(scoreText.c_str(), position.x, position.y, fontSize, WHITE);
}

Entity::Entity()
{
    speed = 2;
    isPlayer = false;
    tComp.direction = {0, 0};

    
}

void Entity::FixedUpdate()
{
    if (isPlayer)
    {
        tComp.direction = {0, 0};
        if (IsKeyDown(KEY_W))
        {
            tComp.direction.y = -1;
        }

        if (IsKeyDown(KEY_S))
        {
            tComp.direction.y = 1;
        }
    }
}

void Entity::SetScore()
{
    ui->SetText(score);
}

void Entity::Update()
{
    FixedUpdate();
    tComp.direction = Dinzai::Normalize(tComp.direction);
    tComp.position.x += speed * tComp.direction.x;
    tComp.position.y += speed * tComp.direction.y;
}

void Entity::Render()
{
    DrawText("DO NOT INTIALIZE ENTITY", tComp.position.x, tComp.position.y, 50, BLACK);
}

Paddle::Paddle(Vector2 position, bool isPlayer) : Entity()
{
    tComp.size = {20, 120};
    tComp.position = position;
    this->isPlayer = isPlayer;
    speed = 6;
    score = 0;

    if (isPlayer)
    {
        ui = new UI(score, Vector2{position.x, position.y - screenHeight / 4});
    }
    else
    {
        ui = new UI(score, Vector2{position.x - 110, position.y - screenHeight / 4});
    }

}

void Paddle::Update()
{
    Entity::Update();
}

void Paddle::Render()
{
    DrawRectangleV(tComp.position, tComp.size, WHITE);
    ui->Draw();
}

Ball::Ball() : Entity()
{
    tComp.direction = {1, 0};
    tComp.position = {screenWidth / 2, screenHeight / 2};
    tComp.radius = 18;
    speed = 5;
}

void Ball::Render()
{
    DrawCircleV(tComp.position, tComp.radius, WHITE);
}