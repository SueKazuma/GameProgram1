#include "Vector2.h"
#include <math.h>

float VSize(VECTOR2 v)
{
    //ルート
    return sqrtf(v.x * v.x + v.y * v.y);
}

VECTOR2 VSub(VECTOR2 v1, VECTOR2 v2)
{
    //x軸、y軸の長さを求める
    VECTOR2 r;
    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    return r;
}

VECTOR2 VAdd(VECTOR2 v1, VECTOR2 v2)
{
    //半径rを返す
    VECTOR2 r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    return r;
}

VECTOR2 operator +(VECTOR2 v1, VECTOR2 v2)
{
    VECTOR2 r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    return r;
}

VECTOR2 VScale(VECTOR2 v, float s)
{
    VECTOR2 r;
    r.x = v.x * s;
    r.y = v.y * s;
    return r;
}

VECTOR2 VNorm(VECTOR2 v)
{
    float len = VSize(v);
    return VScale(v, 1.0f / len);
}

bool CircleHit(VECTOR2 obj1, VECTOR2 obj2, float r)
{
    VECTOR2 d = VSub(obj1, obj2); // 差
    if (VSize(d) < r) { // obj1とobj2の距離が半径より小さい
        return true; // 当たっているので、true
    }
    return false; // 当たってない
}
