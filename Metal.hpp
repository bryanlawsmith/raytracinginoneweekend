#pragma once

#include "Material.hpp"
#include "Scattering.hpp"

class Metal : public Material
{
public:

	Metal(vec3 albedo, float fuzziness)
	: m_Albedo(albedo)
	, m_Fuzziness(fuzziness)
	{
		if (fuzziness < 0.0f) fuzziness = 0.0f;
		if (fuzziness > 1.0f) fuzziness = 1.0f;
	}

	virtual bool Scatter(const ray& in, const HitRecord& hitRecord, vec3 &attenuation, ray& scattered) const
	{
		vec3 reflected = Reflect(unit(in.Direction()), hitRecord.normal);

		scattered = ray(hitRecord.p, reflected + RandomInUnitSphere() * m_Fuzziness);

		attenuation = m_Albedo;

		return (dot(scattered.Direction(), hitRecord.normal) > 0.0);
	}

protected:

	vec3 m_Albedo;

	float m_Fuzziness;
};