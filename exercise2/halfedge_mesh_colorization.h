//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"

typedef std::vector<vec3> colormap;


//create a circular colormap with n colors 
//interpolating red - yellow - green - cyan- blue - magenta and back to red 
colormap create_hsv_color_map(int n) ;

//create a grayscale colormap with n colors 
colormap create_grayscale_color_map(int n);

//interpolating red - yellow - green - cyan- blue - magenta and back to red 
colormap create_jet_color_map(int n);

//create color map with n color by random shuffling hsv colormap
colormap create_permutated_hsv_color_map(int n);

//colorize each face with a color corresponding to its face_attribute
//therefore face_attributes must have num_faces() elements
//this method is used e.g. to assign a different color to each face depending of 
//its corresponding shell index or strip index
void colorize_faces(halfedge_mesh& mesh,const std::vector<int>& face_attributes);
	
void colorize_faces(halfedge_mesh& mesh,const std::vector<float>& face_attributes,
	float vmin, float vmax, int n=1024);

void colorize_vertices(halfedge_mesh& mesh,const std::vector<float>& vertex_attributes,
	float vmin, float vmax, int n=1024);
