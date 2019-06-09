#pragma once

#include "Hittable.hpp"

class HittableList : public Hittable
{
public:

	Hittable** m_List;
	int m_ListSize;

	HittableList() {}
	HittableList(Hittable** list, int n);

	bool Hit(const ray& ray, float tMin, float tMax, HitRecord& record) const;
};


HittableList::HittableList(Hittable** list, int n)
: m_List(list)
, m_ListSize(n)
{}

bool HittableList::Hit(const ray& ray, float tMin, float tMax, HitRecord& record) const
{
	HitRecord tempRec;
	bool hitAnything = false;
	float closestSoFar = tMax;

	for (int i = 0; i < m_ListSize; i++)
	{
		if (m_List[i]->Hit(ray, tMin, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			record = tempRec;
		}
	}

	return hitAnything;
}
