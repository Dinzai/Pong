#include "Globals.h"
#include "Math_Lib.h"
#include <string>

struct TransformComponent
{
    Vector2 lastPosition;
    Vector2 position;
    Vector2 size;
    Vector2 direction;
    float radius;
};

struct UI
{
    UI(int score, Vector2 position);

    void SetText(int score);

    void Draw();

    std::string scoreText;
    int theScore;

    Vector2 position;
    int fontSize = 30;
};

class Entity
{
public:
    Entity();

    void SetScore();

    virtual void FixedUpdate();

    virtual void Update();

    virtual void Render();

    float speed;
    TransformComponent tComp;
    int score;
    bool isPlayer;

    UI *ui;
};

class Paddle : public Entity
{
public:
    Paddle(Vector2 position, bool isPlayer);

    virtual void Update() override;
    virtual void Render() override;
};

class Ball : public Entity
{
public:
    Ball();

    virtual void Render() override;
};

inline bool RadialCollision(TransformComponent lhs, TransformComponent rhs)
{
    float sumRadius = lhs.radius + rhs.radius;
    float mag = Dinzai::GetMagnitude(lhs.position, rhs.position);

    if (sumRadius >= mag)
    {
        return true;
    }
    return false;
}

inline bool AABB(TransformComponent lhs, TransformComponent rhs)
{
    // LEFT
    float lhs_Left = lhs.position.x;
    float lhs_Right = lhs.position.x + lhs.size.x;
    float lhs_Top = lhs.position.y;
    float lhs_Bottom = lhs.position.y + lhs.size.y;
    // RIGHT
    float rhs_Left = rhs.position.x;
    float rhs_Right = rhs.position.x + rhs.size.x;
    float rhs_Top = rhs.position.y;
    float rhs_Bottom = rhs.position.y + rhs.size.y;

    return (lhs_Left < rhs_Right && lhs_Right > rhs_Left && lhs_Bottom > rhs_Top && lhs_Top < rhs_Bottom);
}

inline bool CustomCollision(TransformComponent lhs, TransformComponent rhs)
{
    float lhs_Left = lhs.position.x;
    float lhs_Right = lhs.position.x + lhs.size.x;
    float lhs_Top = lhs.position.y;
    float lhs_Bottom = lhs.position.y + lhs.size.y;

    float rhs_Left = rhs.position.x - rhs.radius;
    float rhs_Right = rhs.position.x + rhs.radius;
    float rhs_Top = rhs.position.y - rhs.radius;
    float rhs_Bottom = rhs.position.y + rhs.radius;

    return (lhs_Right > rhs_Left && lhs_Left < rhs_Right && lhs_Top < rhs_Bottom && lhs_Bottom > rhs_Top);
}