//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"




//computes the surface area of the halfedge_mesh m by computing and summing up the 
//areas of all polygonal faces
//method is not restricted to triangle meshes
float compute_surface_area(const halfedge_mesh& m);
