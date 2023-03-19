#include "volume_renderer.h"

Kasumi::VolumeRenderer::VolumeRenderer()
{
	_frame = std::make_shared<Frame>(0.1, 0.1, 1024, 1024);
}

void Kasumi::VolumeRenderer::render()
{
	HinaPE::Geom::Sphere3 sphere;
	sphere._center = mVector3(0, 0, -30);
	sphere._radius = 1;
	_frame->fill_each_ray(
			[&](const mRay3 &ray) -> mVector3
			{
				auto res = sphere.closest_intersection(ray);
				if (res.is_intersecting)
				{
					return {0.972, 0.572, 0.921};
				} else
					return {0.572, 0.772, 0.921};
			});
	_frame->write_to_file("output.ppm");
}
