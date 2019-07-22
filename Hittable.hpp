#pragma once

#include "ray.hpp"

class Material;

struct HitRecord
{
	float t;
	vec3 p;
	vec3 normal;

	/* When a ray hits a surface, this records the material of that surface.
	 * This can then be used to calculate what, if any, scattering is performed. */
	Material* material;
};

class Hittable
{
public:
	virtual bool Hit(const ray& t, float tMin, float tMax, HitRecord& record) const = 0;
};
