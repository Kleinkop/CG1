//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "obj_reader.h"

#include <iostream>
#include <fstream>

#include <cgv/utils/convert.h>

using namespace std;


obj_reader::obj_reader(const std::string &filename)
{
	// Create a new file stream and open the file
	ifstream file; 

	// At least in windows we can handle non-ascii characters
	// by using wide chars to open the file
#ifdef _WIN32
	std::wstring ws = cgv::utils::str2wstr(filename);
	file.open(ws.c_str());
#else
	file.open(filename.c_str());
#endif

	// Show an error message if the file could not be loaded
	if (!file.is_open()) {
		std::cerr<<"Error: Could not find file "<<filename<<"."<<std::endl;
		return;
	}
	
	// This string represents one line of the file
	string str_line;
	
	// Repeat the following instructions as long as there are
	// lines left to read. The lines shall end with a return (\n) character
	while(getline(file, str_line, '\n')) {
		// Convert the line from a string to a string stream.
		// The stringstream has methods to extract numbers and to
		// split the string further
		stringstream line(str_line);
		
		// Read characters until the first whitespace and store the
		// result in the variable "definition_type" that contains
		// the id of the definition in the rest of the line
		string definition_type;
		line>>definition_type;
		
		// If the definition type is "v" then a vertex is defined
		if (definition_type == "v")
			process_vertex(line);
		else
		// If the definition type is "vn" then a normal is defined
		if (definition_type == "vn")
			process_normal(line);
		else
		// If the definition type is "f" then a face is defined
		if (definition_type == "f")
			process_face(line);
	}

	// All done. Close this file
	file.close();
	
	// Calculate the bounding box
	calculate_bounding_box();
}




// Calculate the bounding box. This method is called after the mesh
// was loaded. The results are stored in bbox_min and bbox_max.
// They are used in get_center and get_max_extent.
void obj_reader::calculate_bounding_box()
{
	// Set the minimum point to a very large value and the maximum
	// point to a very small value.
	bbox_max = -std::numeric_limits<float>::max();
	bbox_min = -bbox_max;	
	
	vector<vec3>::iterator iter;
	for (iter = vertices.begin(); iter != vertices.end(); iter++) {
		for (int i=0; i<3; i++) {
			if ((*iter)[i] > bbox_max[i])
				bbox_max[i] = (*iter)[i];
			if ((*iter)[i] < bbox_min[i])
				bbox_min[i] = (*iter)[i];
		}
	}
	
}




// Get the minimum point of the bounding box
const vec3& obj_reader::get_bbox_min()
{
	return bbox_min;
}




// Get the maximum point of the bounding box
const vec3& obj_reader::get_bbox_max()
{
	return bbox_max;
}





// This method is called for every line in the obj file that contains
// a vertex definition. 
// The parameter "line" contains a string stream which contains the 
// complete line and has the reading position at the first entry of
// the actual definition.
void obj_reader::process_vertex(std::stringstream &line)
{
	// The method must parse the string stream and read 3 floating point
	// values which are stored into a variable of the type "vec3". This
	// variable must be added to the list of vertices.
	vec3 new_vertex;
	// Extract 3 floating point numbers from the line
	// and store them in x(), y() or z().
	line>>new_vertex.x()>>new_vertex.y()>>new_vertex.z();
	
	// Add this vertex to the list of vertices
	vertices.push_back(new_vertex);
}




// This method is called for every line in the obj file that contains
// a normal definition and works similar to process_vertex.
// The parameter "line" contains a string stream which contains the 
// complete line and has the reading position at the first entry of
// the actual definition.
void obj_reader::process_normal(std::stringstream &line)
{
	// The method must parse the string stream and read 3 floating point
	// values which are stored into a variable of the type "vec3". This
	// variable must be added to the list of normales.	

	vec3 new_normal;
	line>>new_normal.x()>>new_normal.y()>>new_normal.z();
	normals.push_back(new_normal);
	
}

void obj_reader::process_texcoord(std::stringstream &line)
{
	vec2 new_texcoord;
	line>>new_texcoord.x()>>new_texcoord.y();
	texcoords.push_back(new_texcoord);	
}




// This method is called for every line in the obj file that contains
// a face definition. 
// The parameter "line" contains a string stream which contains the 
// complete line and has the reading position at the first entry of
// the actual definition.
void obj_reader::process_face(std::stringstream &line)
{
	// The method must parse the line and read the definition. More information
	// on how this line is defined can be found in the body of this method.	
	face new_face;

	// The parameter "line" is a string stream that contains the line
	// of the .obj-file where a normal is defined. The reading pointer
	// if this stream lies at the first face point.
	// The result of this method is the filled variable "new_face"
	// that has the type "face". A face has one property "corners" which
	// is a list of "face_point"s.

	// Split the line into face points that are separated by whitespaces
	string entry;
	while(getline(line, entry, ' ')) {
		
		// Do nothing if the variable "entry" does not contain any data
		if (entry.empty())
			continue;

		// Make a stream from this face point definition
		stringstream entry_stream(entry);

		face_corner new_corner;		
		
		string value;
		
		getline(entry_stream, value, '/');
		if (!cgv::utils::from_string(new_corner.index_vertex, value))
			new_corner.index_vertex = -1;

		value = "";
		getline(entry_stream, value, '/');
		if (!cgv::utils::from_string(new_corner.index_texcoord, value))
			new_corner.index_texcoord = -1;
		
		value = "";
		getline(entry_stream, value, '/');
		if (!cgv::utils::from_string(new_corner.index_normal, value))
			new_corner.index_normal = -1;

		new_face.corners.push_back(new_corner);
	}

	faces.push_back(new_face);
	
}



// Get the list of vertices
const vector<vec3> &obj_reader::get_vertices() {
	return vertices;
}



	
// Get the list of normals
const vector<vec3> &obj_reader::get_normals() {
	return normals;
}



	
// Get the list of faces
const vector<face> &obj_reader::get_faces() {
	return faces;
}

	
// Get the list of faces
const vector<vec2> &obj_reader::get_texcoords() {
	return texcoords;
}



