//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh.h"

//smooth vertex positions with explicit integration of heat equation using uniform laplacian 
void smooth_vertex_positions_laplacian(halfedge_mesh& m,float lambda,int num_iters=10);	

//smooth vertex positions with explicit integration of heat equation using cotan laplacian 
void smooth_vertex_positions_laplacian_beltrami(halfedge_mesh& m,float lambda,int num_iters=10);
