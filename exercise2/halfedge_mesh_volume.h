//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"

//compute the volume of halfedge_mesh m
//assume m is triangulated and closed
float compute_volume(const halfedge_mesh& m);
