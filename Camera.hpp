#pragma once

#include "ray.hpp"

class Camera
{
public:

	vec3 m_Origin;
	vec3 m_LowerLeftCorner;
	vec3 m_Horizontal;
	vec3 m_Vertical;

	Camera()
	{
		m_LowerLeftCorner = vec3(-2.0, -1.0, -1.0);
		m_Horizontal = vec3(4.0, 0.0, 0.0);
		m_Vertical = vec3(0.0, 2.0, 0.0);
		m_Origin = vec3(0.0, 0.0, 0.0);
	}

	ray GetRay(float u, float v)
	{
		return ray(m_Origin, m_LowerLeftCorner + m_Horizontal * u + m_Vertical * v - m_Origin);
	}
};
