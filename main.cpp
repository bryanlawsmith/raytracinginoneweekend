#include <iostream>
#include <cstdlib>
#include <cfloat>
#include <omp.h>

#include "vec3.hpp"
#include "ray.hpp"
#include "Sphere.hpp"
#include "HittableList.hpp"
#include "Camera.hpp"

vec3 RandomInUnitSphere()
{
	vec3 p;
	do
	{
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (p.squaredLength() >= 1.0);

	return p;
}

vec3 Color(const ray& r, Hittable* world)
{
	HitRecord rec;
	if (world->Hit(r, 0.001, FLT_MAX, rec))
	{
		vec3 target = rec.p + rec.normal + RandomInUnitSphere();
		return 	0.5 * Color(ray(rec.p, target-rec.p), world);
	}
	else
	{
		vec3 unitDirection = unitVector(r.Direction());

		float t = 0.5 * (unitDirection.y() + 1.0);

		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

vec3* g_Framebuffer;

int omp_thread_count() {
    int n = 0;
    #pragma omp parallel reduction(+:n)
    n += 1;
    return n;
}

int main(int argc, char** argv)
{
	int threads = omp_thread_count();
	std::cerr << "Thredcount: " << threads << std::endl;

	int nx = 1024;
	int ny = 512;
	int ns = 1;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	Camera cam;

	Hittable* list[2];
	list[0] = new Sphere(vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(vec3(0, -100.5, -1), 100);
	Hittable* world = new HittableList(list, 2);

	g_Framebuffer = new vec3[nx * ny];

	#pragma omp parallel for
	for (int j = 0; j < ny; j++)
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

			g_Framebuffer[i + j * nx] = accumulatedColor;
		}
		//std::cerr << "Scanline: " << j << " completed" << std::endl;
	}

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			int currentOffset = i + j * nx;

			int ir = (int)(255.99 * sqrt(g_Framebuffer[currentOffset][0]));
			int ig = (int)(255.99 * sqrt(g_Framebuffer[currentOffset][1]));
			int ib = (int)(255.99 * sqrt(g_Framebuffer[currentOffset][2]));

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}

	return 0;
}
