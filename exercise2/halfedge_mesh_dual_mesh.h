//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"

//creates a new mesh which is the dual mesh of m
halfedge_mesh create_dual_mesh(const halfedge_mesh& m);
