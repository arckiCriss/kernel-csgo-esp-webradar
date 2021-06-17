//
//  Vector.h
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

#include <cmath>

class Vector
{
public:
    float x, y, z;

    Vector()
    {
        x = y = z = 0.0f;
    }

    Vector(float X, float Y, float Z)
    {
        x = X; y = Y; z = Z;
    }

    Vector(float XYZ)
    {
        x = XYZ; y = XYZ; z = XYZ;
    }

    Vector(float* v)
    {
        x = v[0]; y = v[1]; z = v[2];
    }

    Vector(const float* v)
    {
        x = v[0]; y = v[1]; z = v[2];
    }

    inline Vector& operator=(const Vector& v)
    {
        x = v.x; y = v.y; z = v.z; return *this;
    }

    inline Vector& operator=(const float* v)
    {
        x = v[0]; y = v[1]; z = v[2]; return *this;
    }

    inline float& operator[](int i)
    {
        return ((float*)this)[i];
    }

    inline float operator[](int i) const
    {
        return ((float*)this)[i];
    }

    inline Vector& operator+=(const Vector& v)
    {
        x += v.x; y += v.y; z += v.z; return *this;
    }

    inline Vector& operator-=(const Vector& v)
    {
        x -= v.x; y -= v.y; z -= v.z; return *this;
    }

    inline Vector& operator*=(const Vector& v)
    {
        x *= v.x; y *= v.y; z *= v.z; return *this;
    }

    inline Vector& operator/=(const Vector& v)
    {
        x /= v.x; y /= v.y; z /= v.z; return *this;
    }

    inline Vector& operator+=(float v)
    {
        x += v; y += v; z += v; return *this;
    }

    inline Vector& operator-=(float v)
    {
        x -= v; y -= v; z -= v; return *this;
    }

    inline Vector& operator*=(float v)
    {
        x *= v; y *= v; z *= v; return *this;
    }

    inline Vector& operator/=(float v)
    {
        x /= v; y /= v; z /= v; return *this;
    }

    inline Vector operator-() const
    {
        return Vector(-x, -y, -z);
    }

    inline Vector operator+(const Vector& v) const
    {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    inline Vector operator-(const Vector& v) const
    {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    inline Vector operator*(const Vector& v) const
    {
        return Vector(x * v.x, y * v.y, z * v.z);
    }

    inline Vector operator/(const Vector& v) const
    {
        return Vector(x / v.x, y / v.y, z / v.z);
    }

    inline Vector operator+(float v) const
    {
        return Vector(x + v, y + v, z + v);
    }

    inline Vector operator-(float v) const
    {
        return Vector(x - v, y - v, z - v);
    }

    inline Vector operator*(float v) const
    {
        return Vector(x * v, y * v, z * v);
    }

    inline Vector operator/(float v) const
    {
        return Vector(x / v, y / v, z / v);
    }

    inline float Length() const
    {
        return sqrtf(x * x + y * y + z * z);
    }

    inline float LengthSqr() const
    {
        return (x * x + y * y + z * z);
    }

    inline float LengthXY() const
    {
        return sqrtf(x * x + y * y);
    }

    inline float LengthXZ() const
    {
        return sqrtf(x * x + z * z);
    }

    inline float DistTo(const Vector& v) const
    {
        return (*this - v).Length();
    }

    inline float Dot(const Vector& v) const
    {
        return (x * v.x + y * v.y + z * v.z);
    }

    inline Vector Cross(const Vector& v) const
    {
        return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    inline bool IsZero() const
    {
        return (x > -0.01f && x < 0.01f
            && y > -0.01f && y < 0.01f
            && z > -0.01f && z < 0.01f);
    }
};

#endif /* Vector_h */