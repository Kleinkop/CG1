//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh_stripification.h"
#include "halfedge_mesh_colorization.h"
#include "sample_set.h"




std::vector<std::vector<vertex_handle>> extract_strips(halfedge_mesh& mesh,int n_trials, bool colorize)
{
	//prepare result vector of strips
	std::vector<std::vector<vertex_handle>> strips;

	//check if mesh is  triangulated
	if(!mesh.is_triangle_mesh())
	{
		std::cout << "error mesh is not triangulated"<<std::endl;
		return strips;
	}
	
		
	//initialize strip index to -1 for each face
	std::vector<int> strip_indices(mesh.num_faces(),-1);

	
	//student begin

	//please look at sample_set.h data structure

	//usage of new pseudo random number generator of C++
	
	//prepare random engine (mersenne twister)
	std::mt19937 eng;
	//prepare random distribution
	std::uniform_int_distribution<int> dist(1,10);
	//sample a few numbers from distribution using engine
	for(int i = 0; i < 5; ++i)
		std::cout << "random int between 1 and 10: "<< dist(eng)<<std::endl;
	
	//student end

	if(colorize)
		colorize_faces(mesh,strip_indices);

	return strips;
}
