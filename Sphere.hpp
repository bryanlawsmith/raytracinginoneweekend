#pragma once

#include "Hittable.hpp"
#include "Material.hpp"

class Sphere : public Hittable
{
public:

	vec3 m_Centre;
	float m_Radius;
	Material* m_Material;

	Sphere() {}
	Sphere(vec3 centre, float r, Material* material);

	// Hittable interface implementation.
	virtual bool Hit(const ray& r, float tMin, float tMax, HitRecord& record) const;
};

Sphere::Sphere(vec3 centre, float r, Material* material)
: m_Centre(centre)
, m_Radius(r)
, m_Material(material)
{}

bool Sphere::Hit(const ray& r, float tMin, float tMax, HitRecord& record) const
{
	vec3 rayToSphere = r.Origin() - m_Centre;
	float a = dot(r.Direction(), r.Direction());
	float b = dot(rayToSphere, r.Direction());
	float c = dot(rayToSphere, rayToSphere) - m_Radius * m_Radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp < tMax && temp > tMin)
		{
			record.t = temp;
			record.p = r.PointAtParameter(record.t);
			record.normal = (record.p - m_Centre) / m_Radius;
			record.material = m_Material;
			return true;
		}

		temp = (-b + sqrt(b * b  - a * c)) / a;
		if (temp < tMax && temp > tMax)
		{
			record.t = temp;
			record.p = r.PointAtParameter(record.t);
			record.normal = (record.p - m_Centre) / m_Radius;
			record.material = m_Material;
			return true;
		}
	}
	return false;
}
