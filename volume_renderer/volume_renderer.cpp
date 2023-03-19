#include "volume_renderer.h"

Kasumi::VolumeRenderer::VolumeRenderer()
{
	_frame = std::make_shared<Frame>(0.1, 0.1, 1024, 1024);
	_surface = std::make_shared<HinaPE::Geom::Sphere3>();
	as<HinaPE::Geom::Sphere3>(_surface.get())->_center = mVector3(0, 0, -15);
	as<HinaPE::Geom::Sphere3>(_surface.get())->_radius = 1;
}

void Kasumi::VolumeRenderer::render()
{
	real sigma_a = 0.1;
	mVector3 scatter = {0.8, 0.1, 0.5};
	mVector3 background_color = {0.572, 0.772, 0.921};
	_frame->fill_each_ray(
			[&](const mRay3 &ray) -> mVector3
			{
				auto res = _surface->closest_intersection(ray);
				if (res.is_intersecting)
				{
					mVector3 p1 = res.point;
					mVector3 p2 = res.point_far;
					real dist = (p2 - p1).length();
					real transmittance = std::exp(-dist * sigma_a);
					return background_color * transmittance + scatter * (1.0f - transmittance);
				} else
					return background_color;
			});
	_frame->write_to_file("output.ppm");
}
