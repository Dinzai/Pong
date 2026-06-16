#pragma once
#include "Globals.h"
#include <math.h>

namespace Dinzai
{
    inline Vector2 GetDistance(Vector2 lhs, Vector2 rhs)
    {
        return Vector2{lhs.x - rhs.x, lhs.y - rhs.y};
    }

    inline float GetMagnitude(Vector2 lhs, Vector2 rhs)
    {
        Vector2 dist = GetDistance(lhs, rhs);
        return sqrt((dist.x * dist.x) + (dist.y * dist.y));
    }

    inline float GetAngle(Vector2 lhs, Vector2 rhs)
    {
        Vector2 dist = GetDistance(lhs, rhs);
        return atan2(dist.y, dist.x);
    }

    inline float GetLength(Vector2 vec)
    {
        return sqrt((vec.x * vec.x) + (vec.y * vec.y));
    }

    inline Vector2 Normalize(Vector2 vec)
    {
        float length = GetLength(vec);
        Vector2 newVec = {0, 0};
        if(length != 0)
        {
            return Vector2{vec.x / length, vec.y / length};
        }
        return newVec;
        
    }

}
