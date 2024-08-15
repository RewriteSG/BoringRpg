#include "Vector2.h"
#include <iostream>
Vector2::Vector2() : x(0), y(0)
{

}

Vector2::Vector2(int _x, int _y) : x(_x), y(_y)
{

}

int Vector2::GetX() const
{
    return x;
}

int Vector2::GetY() const
{
    return y;
}

int& Vector2::GetY()
{
    return y;
}

void Vector2::SetXandY(int _x, int _y)
{
    x = _x;
    y = _y;
}


Vector2& Vector2::operator-=(const Vector2& scalar)
{
    x -= scalar.x;
    y -= scalar.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2& scalar) const
{
    return Vector2(x - scalar.x, y - scalar.y);
}

Vector2& Vector2::operator+=(const Vector2& scalar)
{
    x += scalar.x;
    y += scalar.y;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2& scalar)
{
    x /= scalar.x;
    y /= scalar.y;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& scalar)
{
    x *= scalar.x;
    y *= scalar.y;
    return *this;
}
Vector2& Vector2::operator*=(const int& scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator=(const Vector2& scalar)
{
    x = scalar.x;
    y = scalar.y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& scalar)const
{
    return Vector2(x + scalar.x, y + scalar.y);
}

int Vector2::Distance(const Vector2& pos1,const Vector2& pos2)
{
    Vector2 diff = pos1 - pos2;
    int total = std::abs(diff.x) + std::abs(diff.y);
    return std::abs(total);
}

void Vector2::Clamp(int& value,const int& max, const int& min)
{
    value = std::max(min, std::min(value, max));
}

void Vector2::Clamp(Vector2& value, const Vector2& max,const Vector2& min)
{
    Clamp(value.x, max.x, min.x);
    Clamp(value.y, max.y, min.y);
}

void Vector2::Clamp(int* value, const int& max, const int& min)
{

}

void Vector2::Clamp(Vector2* value, const Vector2& max, const Vector2& min)
{
    Clamp(value->x, max.x, min.x);
    Clamp(value->y, max.y, min.y);
}

bool Vector2::operator==(const Vector2& scalar)
{
    return x == scalar.x && y == scalar.y;
}

bool Vector2::operator!=(const Vector2& scalar)
{
    return x != scalar.x || y != scalar.y;
}
