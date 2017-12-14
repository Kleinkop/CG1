//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh_area.h"
#include "halfedge_mesh_colorization.h"
#include <list>
	

static vec3 cross_product(vec3 a, vec3 b) {
	vec3 ab;
	ab.x() = a.y()*b.z() - a.z()*b.y();
	ab.y() = a.z()*b.x() - a.x()*b.z();
	ab.z() = a.x()*b.y() - a.y()*b.x();
	return ab;
}
float compute_surface_area_triangle(const halfedge_mesh& m)
{
	float re = 0;
	//student begin
	auto fend = m.faces_end();
	for (auto fit = m.faces_begin(); fit != fend; fit++) {
		std::vector<vec3> points;
		auto vend = m.vertices_end(*fit);
		auto vit = m.vertices_begin(*fit);
		for (int i = 0; i < 3; i++) {
			if (vit == vend) {
				break;
			}
			points.push_back(m.position(*vit));
			vit++;
		}
		vec3 a = points[0];
		vec3 b = points[1];
		vec3 c = points[2];

		vec3 temp = cross_product(a,b) + cross_product(b,c) + cross_product(c,a);
		re += 0.5 * sqrt(temp.x()*temp.x() + temp.y()*temp.y() + temp.z()*temp.z());

	}

	//student end
	return re;
}

float compute_surface_area(const halfedge_mesh& m)
{
	float re = 0;

	//student begin
	halfedge_mesh a = m;
	a.triangulate();

	re = compute_surface_area_triangle(a);
	//student end
	return re;
}


 float compute_surface_area_old(const halfedge_mesh& m)
{
	 float re = 0;


	//student begin
	auto fend = m.faces_end();
	for (auto fit = m.faces_begin(); fit != fend; fit++) {

		vec3 normal = m.normal(*fit);
		normal.normalize();
		std::cout << normal.length() << std::endl;

		auto hit = m.halfedges_begin(*fit);
		vec3 reference =  1.5f *  ( m.position(m.target(*hit)) - m.position(m.origin(*hit)) ) + m.position(m.origin(*hit));
		float face_area = 0;

		auto hend = m.halfedges_end(*fit);
		for (hit = m.halfedges_begin(*fit); hit != hend; hit++) {
			vec3 origin = m.position(m.origin(*hit));
			vec3 target = m.position(m.target(*hit));


			vec3 cross = cross_product(origin - reference, target - reference);
			float a = cross.x() * normal.x() + cross.y() * normal.y() + cross.z() * normal.z();

			face_area = face_area +  0.5f * a;
		}
		re += abs(face_area);

	}

	//student end
	return re;
}