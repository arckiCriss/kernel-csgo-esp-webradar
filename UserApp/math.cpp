
#include "math.h"

void inline cMath::SinCos(float radians, float* sine, float* cosine)
{
    *sine = sin(radians);
    *cosine = cos(radians);
}

void cMath::AngleVectors(const Vector& angles, Vector* forward)
{

    float RadY = M_PI / 180.0f * angles.y;
    float RadX = M_PI / 180.0f * angles.x;

    float sp, sy, cp, cy;

    sp = (float)sin(RadX);
    cp = (float)cos(RadX);

    sy = (float)sin(RadY);
    cy = (float)cos(RadY);

    forward->x = (cp * cy);
    forward->y = (cp * sy);
    forward->z = -sp;

}

void cMath::AngleVectors(const Vector& angles, Vector* forward, Vector* right, Vector* up)
{

    float sr, sp, sy, cr, cp, cy;

    SinCos(DEG2RAD(angles[0]), &sy, &cy);
    SinCos(DEG2RAD(angles[1]), &sp, &cp);
    SinCos(DEG2RAD(angles[2]), &sr, &cr);

    if (forward)
    {
        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }

    if (right)
    {
        right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
        right->y = (-1 * sr * sp * sy + -1 * cr * cy);
        right->z = -1 * sr * cp;
    }

    if (up)
    {
        up->x = (cr * sp * cy + -sr * -sy);
        up->y = (cr * sp * sy + -sr * cy);
        up->z = cr * cp;
    }
}

float cMath::DotProduct(Vector& v1, float* v2)
{
    return v1.x * v2[0] + v1.y * v2[1] + v1.z * v2[2];
}

float cMath::Dot(const Vector& v1, Vector& v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


float cMath::VecLength(Vector& vec)
{
    return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

float cMath::VecDist(const Vector& fVec1, Vector& fVec2)
{
    return sqrt(pow(fVec1.x - fVec2.x, 2) + pow(fVec1.y - fVec2.y, 2) + pow(fVec1.z - fVec2.z, 2));
}

float cMath::GetFov(QAngle eyePosition, Vector playerHeadPosition, Vector entityHeadPosition)
{
    QAngle newAngles = CalcAngle(playerHeadPosition, entityHeadPosition);

    float yaw = ((float)sin(fabsf(eyePosition.y - newAngles.y) * M_PI / 180)) * VecDist(playerHeadPosition, entityHeadPosition);
    float pitch = ((float)sin(fabsf(eyePosition.x - newAngles.x) * M_PI / 180)) * VecDist(playerHeadPosition, entityHeadPosition);

    return sqrt((yaw * yaw) + (pitch * pitch));
}

float cMath::GetDistance3D(Vector playerPosition, Vector enemyPosition) {
    return sqrt(powf(enemyPosition.x - playerPosition.x, 2.0f)
        + powf(enemyPosition.y - playerPosition.y, 2.0f)
        + powf(enemyPosition.z - playerPosition.z, 2.0f));
}

QAngle cMath::CalcAngle(Vector PlayerPos, Vector EnemyPos)
{
    QAngle AimAngles;
    Vector delta = PlayerPos - EnemyPos;
    float hyp = sqrt((delta.x * delta.x) + (delta.y * delta.y));
    AimAngles.x = atanf(delta.z / hyp) * M_RADPI;
    AimAngles.y = atanf(delta.y / delta.x) * M_RADPI;
    if (delta.x >= 0.0)
        AimAngles.y += 180.0f;

    return AimAngles;
}

Vector cMath::CalcAngle(Vector playerPosition, Vector enemyPosition, Vector aimPunch, Vector vecView, float yawRecoilReductionFactory, float pitchRecoilReductionFactor)
{
    Vector delta = Vector(playerPosition.x - enemyPosition.x,
        playerPosition.y - enemyPosition.y,
        (playerPosition.z + vecView.z)
        - enemyPosition.z);
    Vector tmp;
    float hyp = sqrt((delta.x * delta.x) + (delta.y * delta.y));
    tmp.x = atan(delta.z / hyp) * M_RADPI - (aimPunch.x * yawRecoilReductionFactory);
    tmp.y = atan(delta.y / delta.x) * M_RADPI - (aimPunch.y * pitchRecoilReductionFactor);
    tmp.z = 0;

    if (delta.x >= 0.0) tmp.y += 180.0f;

    tmp = NormalizeAngle(tmp);
    tmp = ClampAngle(tmp);

    return tmp;
}

Vector cMath::ClampAngle(Vector angle)
{
    while (angle.y > 180) angle.y -= 360;
    while (angle.y < -180) angle.y += 360;

    if (angle.x > 89.0f) angle.x = 89.0f;
    if (angle.x < -89.0f) angle.x = -89.0f;

    angle.z = 0.0f;

    return angle;
}

Vector cMath::NormalizeAngle(Vector angle)
{
    while (angle.x < -180.0f) angle.x += 360.0f;
    while (angle.x > 180.0f) angle.x -= 360.0f;

    while (angle.y < -180.0f) angle.y += 360.0f;
    while (angle.y > 180.0f) angle.y -= 360.0f;

    while (angle.z < -180.0f) angle.z += 360.0f;
    while (angle.z > 180.0f) angle.z -= 360.0f;

    return angle;
}


void cMath::VectorAngles(const Vector& dir, QAngle& angles)
{
    float hyp = sqrt((dir.x * dir.x) + (dir.y * dir.y));
    angles.x = atanf(dir.z / hyp) * M_RADPI;
    angles.y = atanf(dir.y / dir.x) * M_RADPI;
    if (dir.x >= 0.0)
        angles.y += 180.0f;
}

void cMath::ClampAngle(QAngle& angles)
{
    if (angles.x < -89.0f)
        angles.x = 89.0f;
    if (angles.x > 89.0f)
        angles.x = 89.0f;
    if (angles.y < -180.0f)
        angles.y += 360.0f;
    if (angles.y > 180.0f)
        angles.y -= 360.0f;
}

void cMath::VectorNormalize(Vector& v)
{
    float l = VecLength(v);
    if (l != 0.0f)
    {
        v /= l;
    }
    else
    {
        v.x = v.y = 0.0f; v.z = 1.0f;
    }
}

void cMath::SmoothAngle(const QAngle& ViewAngle, QAngle& DestAngles, float smooth)
{
    QAngle vecDelta = ViewAngle - DestAngles;
    ClampAngle(vecDelta);
    DestAngles = ViewAngle - vecDelta / 100.0f * smooth; // 50.0f is ur smooth value
}

void cMath::MakeVector(Vector angle, Vector& vector)
{
    float pitch = float(angle[0] * M_PI / 180);
    float yaw = float(angle[1] * M_PI / 180);
    float tmp = float(cos(pitch));
    vector[0] = float(-tmp * -cos(yaw));
    vector[1] = float(sin(yaw) * tmp);
    vector[2] = float(-sin(pitch));
}

Vector cMath::AngleToDirection(QAngle angle)
{
    // Convert angle to radians
    angle.x = (float)DEG2RAD(angle.x);
    angle.y = (float)DEG2RAD(angle.y);

    float sinYaw = sin(angle.y);
    float cosYaw = cos(angle.y);

    float sinPitch = sin(angle.x);
    float cosPitch = cos(angle.x);

    Vector direction;
    direction.x = cosPitch * cosYaw;
    direction.y = cosPitch * sinYaw;
    direction.z = -sinPitch;

    return direction;
}
