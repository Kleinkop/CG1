//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"

//returns a vector of face handles containing one face_handle of each shell
std::vector<face_handle> extract_shells(halfedge_mesh& m,bool colorize); 

//return number of connected components or shells (first betti number)
int count_shells(const halfedge_mesh& m);

