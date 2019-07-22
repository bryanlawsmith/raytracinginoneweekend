#pragma once

#include "ray.hpp"
#include "Hittable.hpp"

class Material
{
public:
	virtual bool Scatter(const ray& in, const HitRecord& hitRecord, vec3 &attenuation, ray& scattered) const = 0;
};