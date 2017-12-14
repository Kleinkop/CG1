//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh_noise.h"
#include "random_utils.h"
#include <ctime>



	
void add_noise_to_vertex_positions(halfedge_mesh& m,float sigma)
{
	std::mt19937 eng((unsigned long)time(NULL)); 
	
	uniform_point_on_unit_sphere_distribution sampler;
	std::normal_distribution<float> normal_dist(0,sigma);

	vertex_iterator vend = m.vertices_end();
	for(vertex_iterator vit = m.vertices_begin(); vit != vend; ++vit)
	{
		vec3 random_direction = sampler(eng);
		float random_offset = normal_dist(eng);
		m.position(*vit) +=  random_offset*random_direction;	
	}			
}


void add_noise_to_vertex_positions_in_normal_direction(halfedge_mesh& m,float sigma)
{
	std::mt19937 eng((unsigned long)time(NULL)); 
	std::normal_distribution<float> normal_dist(0,sigma);

	vertex_iterator vend = m.vertices_end();
	for(vertex_iterator vit = m.vertices_begin(); vit != vend; ++vit)
	{
		
		float random_offset = normal_dist(eng);
		m.position(*vit) +=  random_offset*m.normal(*vit);	
	}			
}
