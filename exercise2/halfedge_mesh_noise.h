//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"

void add_noise_to_vertex_positions(halfedge_mesh& m,float sigma);
void add_noise_to_vertex_positions_in_normal_direction(halfedge_mesh& m,float sigma);
