#pragma once

#include "Material.hpp"
#include "Scattering.hpp"

class Metal : public Material
{
public:

	Metal(vec3 albedo)
	: m_Albedo(albedo)
	{
	}

	virtual bool Scatter(const ray& in, const HitRecord& hitRecord, vec3 &attenuation, ray& scattered) const
	{
		vec3 reflected = Reflect(unit(in.Direction()), hitRecord.normal);

		scattered = ray(hitRecord.p, reflected);

		attenuation = m_Albedo;

		return (dot(scattered.Direction(), hitRecord.normal) > 0.0);
	}

protected:

	vec3 m_Albedo;
};