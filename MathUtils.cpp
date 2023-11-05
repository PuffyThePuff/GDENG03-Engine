#include "MathUtils.h"
#include <stdlib.h>
#include <cmath>

float MathUtils::randomFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int MathUtils::randomInt(int a, int b)
{
    int range = a - b + 1;
    int num = rand() % range + a;

    return num;
}

float MathUtils::toRadians(float theta)
{
    return theta * acos(0.f) / 90.f;
}

float MathUtils::toDegrees(float theta)
{
    return 90.f * theta / acos(0.f);
}
