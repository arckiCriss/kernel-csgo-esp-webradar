#include <math.h>

#ifndef QAngle_h
#define QAngle_h

class QAngle
{
public:
    float x, y;

    QAngle()
    {
        x = y = 0.0f;
    }

    QAngle(float X, float Y)
    {
        x = X; y = Y;
    }

    QAngle(float XY)
    {
        x = XY; y = XY;
    }

    QAngle(float* v)
    {
        x = v[0]; y = v[1];
    }

    QAngle(const float* v)
    {
        x = v[0]; y = v[1];
    }

    inline QAngle& operator=(const QAngle& v)
    {
        x = v.x; y = v.y; return *this;
    }

    inline QAngle& operator=(const float* v)
    {
        x = v[0]; y = v[1]; return *this;
    }

    inline float& operator[](int i)
    {
        return ((float*)this)[i];
    }

    inline float operator[](int i) const
    {
        return ((float*)this)[i];
    }

    inline QAngle& operator+=(const QAngle& v)
    {
        x += v.x; y += v.y; return *this;
    }

    inline QAngle& operator-=(const QAngle& v)
    {
        x -= v.x; y -= v.y; return *this;
    }

    inline QAngle& operator*=(const QAngle& v)
    {
        x *= v.x; y *= v.y; return *this;
    }

    inline QAngle& operator/=(const QAngle& v)
    {
        x /= v.x; y /= v.y; return *this;
    }

    inline QAngle& operator+=(float v)
    {
        x += v; y += v; return *this;
    }

    inline QAngle& operator-=(float v)
    {
        x -= v; y -= v; return *this;
    }

    inline QAngle& operator*=(float v)
    {
        x *= v; y *= v; return *this;
    }

    inline QAngle& operator/=(float v)
    {
        x /= v; y /= v; return *this;
    }

    inline QAngle operator-() const
    {
        return QAngle(-x, -y);
    }

    inline QAngle operator+(const QAngle& v) const
    {
        return QAngle(x + v.x, y + v.y);
    }

    inline QAngle operator-(const QAngle& v) const
    {
        return QAngle(x - v.x, y - v.y);
    }

    inline QAngle operator*(const QAngle& v) const
    {
        return QAngle(x * v.x, y * v.y);
    }

    inline QAngle operator/(const QAngle& v) const
    {
        return QAngle(x / v.x, y / v.y);
    }

    inline QAngle operator+(float v) const
    {
        return QAngle(x + v, y + v);
    }

    inline QAngle operator-(float v) const
    {
        return QAngle(x - v, y - v);
    }

    inline QAngle operator*(float v) const
    {
        return QAngle(x * v, y * v);
    }

    inline QAngle operator/(float v) const
    {
        return QAngle(x / v, y / v);
    }

    inline float LengthSqr() const
    {
        return (x * x + y * y);
    }

    inline float Length() const
    {
        return sqrtf(x * x + y * y);
    }

    inline float DistTo(const QAngle& v) const
    {
        return (*this - v).Length();
    }

    inline float Dot(const QAngle& v) const
    {
        return (x * v.x + y * v.y);
    }

    inline bool IsZero() const
    {
        return (x > -0.01f && x < 0.01f
            && y > -0.01f && y < 0.01f);
    }
};

#endif /* QAngle_h */#pragma once
