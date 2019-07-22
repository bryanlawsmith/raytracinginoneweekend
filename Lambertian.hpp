#pragma once

#include "Material.hpp"
#include "Scattering.hpp"

class Lambertian : public Material
{
public:

	Lambertian(vec3 albedo)
	: m_Albedo(albedo)
	{
	}

	virtual bool Scatter(const ray& in, const HitRecord& hitRecord, vec3 &attenuation, ray& scattered) const override
	{
		vec3 target = hitRecord.p + hitRecord.normal + RandomInUnitSphere();

		// TODO: I'm not sure this reflection function is 100% sensible?
		scattered = ray(hitRecord.p, target - hitRecord.p);
		attenuation = m_Albedo;

		return true;
	}

protected:

	/* Albedo color of this surface. */
	vec3 m_Albedo;
};