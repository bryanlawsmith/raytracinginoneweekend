#include <iostream>
#include <cfloat>
#include "vec3.hpp"
#include "ray.hpp"
#include "Sphere.hpp"
#include "HittableList.hpp"
#include "Camera.hpp"

vec3 Color(const ray& r, Hittable* world)
{
	HitRecord rec;
	if (world->Hit(r, 0.0, FLT_MAX, rec))
	{
		return 	0.5 * vec3(rec.normal.x() + 1.0, rec.normal.y() + 1.0, rec.normal.z() + 1.0);
	}
	else
	{
		vec3 unitDirection = unitVector(r.Direction());

		float t = 0.5 * (unitDirection.y() + 1.0);

		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main(int argc, char** argv)
{
	int nx = 400;
	int ny = 200;
	int ns = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	Camera cam;

	Hittable* list[2];
	list[0] = new Sphere(vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(vec3(0, -100.5, -1), 100);
	Hittable* world = new HittableList(list, 2);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 accumulatedColor(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = (float)(i + drand48()) / (float)nx;
				float v = (float)(j + drand48()) / (float)ny;
				ray r = cam.GetRay(u, v);
				vec3 p = r.PointAtParameter(2.0);
				accumulatedColor += Color(r, world);
			}

			accumulatedColor /= (float)ns;
			int ir = (int)(255.99 * accumulatedColor[0]);
			int ig = (int)(255.99 * accumulatedColor[1]);
			int ib = (int)(255.99 * accumulatedColor[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}
