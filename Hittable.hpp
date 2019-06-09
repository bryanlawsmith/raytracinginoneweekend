#pragma once

#include "ray.hpp"

struct HitRecord
{
	float t;
	vec3 p;
	vec3 normal;
};

class Hittable
{
public:
	virtual bool Hit(const ray& t, float tMin, float tMax, HitRecord& record) const = 0;
};
