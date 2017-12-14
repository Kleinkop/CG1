//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"


bool load_obj(halfedge_mesh& m,const std::string& filename);

bool store_obj(halfedge_mesh& m,const std::string& filename);
