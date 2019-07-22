/* This file contains utility funcations useful for scattering rays.
 */

#pragma once

#include "ray.hpp"

vec3 RandomInUnitSphere()
{
	vec3 p;
	do
	{
		// drand48 returns uniformly distributed doubles in the range [0.0, 1.0].
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (p.squaredLength() >= 1.0);

	return p;
}

vec3 Reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}