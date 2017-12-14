//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <cgv/math/fvec.h>


// A vec3 that stores points is defined as a three-component
// vector from the cgv library.
typedef cgv::math::fvec<float, 3> vec3;
// A vec2 that stores points is defined as a two-component
// vector from the cgv library.
typedef cgv::math::fvec<float, 3> vec2;

// A face point contains indices for a vertex, a normal
// and a texture coordinate
struct face_corner {
	int index_vertex;
	int index_normal;
	int index_texcoord;
};

// A face is a list of face points
struct face {
	std::vector<face_corner> corners;
};


class obj_reader {
	
private:
	// List of points. Access this list with the method "get_vertices".
	std::vector<vec3> vertices;
	// List of normals. Access this list with the method "get_normals".
	std::vector<vec3> normals;
	//List of texture coordinates. Access the list with method "get_texcoords".
	std::vector<vec2> texcoords;
	// List of faces. Access this list with the method "get_faces".
	std::vector<face> faces;
	
	
	// The minimum and maximum point of the bounding box
	vec3 bbox_min, bbox_max;
	
	// This method is called for every line in the obj file that contains
	// a vertex definition. 
	// The parameter "line" contains a string stream which contains the 
	// complete line and has the reading position at the first entry of
	// the actual definition.
	void process_vertex(std::stringstream &line);

	// This method is called for every line in the obj file that contains
	// a texture coordinate definition. 
	// The parameter "line" contains a string stream which contains the 
	// complete line and has the reading position at the first entry of
	// the actual definition.
	void process_texcoord(std::stringstream &line);

	// This method is called for every line in the obj file that contains
	// a normal definition and works similar to process_vertex.
	// The parameter "line" contains a string stream which contains the 
	// complete line and has the reading position at the first entry of
	// the actual definition.
	void process_normal(std::stringstream &line);

	// This method is called for every line in the obj file that contains
	// a face definition. 
	// The parameter "line" contains a string stream which contains the 
	// complete line and has the reading position at the first entry of
	// the actual definition.
	void process_face(std::stringstream &line);
	
	// Calculate the bounding box. This method is called after the mesh
	// was loaded. The results are stored in bbox_min and bbox_max.
	// They are used in get_center and get_max_extent.
	void calculate_bounding_box();

public:
	// Read the obj file whose name is stored in the variable "filename".
	// After calling this constructor, 3 lists are filled:
	//  * vertices: A list of vec3 elements that contain the vertex positions
	//  * normals: A list of normals that contain the normal positions
	//  * faces: A list of faces that contain the face positions
	// All three lists can be used from an object of this class by calling
	// the getters below.
	obj_reader(const std::string &filename);
	
	// Get the list of vertices
	const std::vector<vec3> &get_vertices();
	
	// Get the list of normals
	const std::vector<vec3> &get_normals();

	// Get the list of texture coordinates
	const std::vector<vec2> &get_texcoords();
	
	// Get the list of faces
	const std::vector<face> &get_faces();

	// Get the minimum point of the bounding box
	const vec3 &get_bbox_min();
	
	// Get the maximum point of the bounding box
	const vec3 &get_bbox_max();
};
