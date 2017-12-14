//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"
#include <vector>

//extract triangle strips from halfedge mesh
//assumes a triagulated mesh
//one triangle strip is given by a vector of vertex handles in the correct order to be displayed with OpenGL
//n_trails is the number of random trials before a randomly grown strip is accepted
std::vector<std::vector<vertex_handle>> extract_strips(halfedge_mesh& mesh,
	int n_trials=10,bool colorize=true);
