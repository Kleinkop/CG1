//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"

//create a mesh containing a single quad
halfedge_mesh create_quad();

//create a unit coube mesh 
halfedge_mesh create_cube();

//create a regular tetraeder mesh
halfedge_mesh create_tetrahedron(float a=1);

//create a disc mesh
halfedge_mesh create_disk(float radius, int slices);

//create a cylinder mesh 
halfedge_mesh create_cylinder(float radius, float height,int stacks, int slices);

//create a sphere mesh
halfedge_mesh create_sphere(float radius, int slices, int stacks);

//create a torus mesh
 halfedge_mesh create_torus(float r,float R,int nsides,int rings);


//creates an icosaeder mesh in m 
// radius is the radius of the circum sphere
halfedge_mesh create_icosaeder(float radius);

//creates an octaeder mesh
// radius is the radius of the circum sphere
halfedge_mesh create_octaeder(float radius);

//create a unit arrow
halfedge_mesh create_unit_arrow(float stem_radius=0.04,float head_radius=0.1,float stem_height=0.8, int slices=30, int stem_stacks=1);
