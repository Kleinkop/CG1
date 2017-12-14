//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh_volume.h"

vec3 cross_product2(vec3 a, vec3 b) {
	vec3 ab;
	ab.x() = a.y()*b.z() - a.z()*b.y();
	ab.y() = a.z()*b.x() - a.x()*b.z();
	ab.z() = a.x()*b.y() - a.y()*b.x();
	return ab;
}
float compute_volume(const halfedge_mesh& m)
{
	assert(m.is_triangle_mesh());
	float vol = 0;
	//student begin

	auto fend = m.faces_end();
	for (auto fit = m.faces_begin(); fit != fend; fit++) {
		auto vend = m.vertices_end(*fit);
		std::vector<vec3> points;
		for (auto vit = m.vertices_begin(*fit); vit != vend; vit++) {

			points.push_back(m.position(*vit));
		}
		vec3 a = points[0] * points[1];
		vec3 temp = (a.x() + a.y() + a.z()) * points[2];

		float l = sqrt(temp.x()*temp.x() + temp.y() * temp.y() + temp.z() * temp.z());

		vec3 c = cross_product2(points[0] , points[1]);
		float re = points[2].x() * c.x() + points[2].y() * c.y() + points[2].z() * c.z();

		vol += re;
	}
	//student end
	return vol/6;

}
