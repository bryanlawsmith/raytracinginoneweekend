#pragma once

#include "vec3.hpp"

class ray
{
public:

	vec3 m_Origin;
	vec3 m_Direction;

	ray() {}
	ray(const vec3& origin, const vec3& direction)
	{
		m_Origin = origin;
		m_Direction = direction;
		m_Direction.normalize();
	}

	vec3 Origin() const { return m_Origin; }
	vec3 Direction() const { return m_Direction; }
	vec3 PointAtParameter(float t) const { return m_Origin + m_Direction * t; }
};
