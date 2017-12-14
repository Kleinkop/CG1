//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh_smoothing.h"
	

	
void smooth_vertex_positions_laplacian(halfedge_mesh& m,float lambda,int num_iters)
{
	//student begin

	halfedge_mesh new_mesh = m;
	for (int i = 0; i < num_iters; i++) {

		auto vend = m.vertices_end();
		for (auto vit = m.vertices_begin(); vit != vend; vit++) {

			short l = 0;
			vec3 mean = vec3(0,0,0);
			auto vvend = m.vertices_end(*vit);

			for (auto vvit = m.vertices_begin(*vit); vvit != vvend; vvit++) {
				mean += m.position(*vvit) - m.position(*vit);
				l++;
			}
			new_mesh.position(*vit) = m.position(*vit) + (lambda/l  * mean);
		}
		m = new_mesh;
	}
	//student end
}

	
void smooth_vertex_positions_laplacian_beltrami(halfedge_mesh& m,float lambda,int num_iters)
{
	//student begin
	std::cout <<"not yet implemented"<<std::endl;
	//student end
	
}

