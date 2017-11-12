//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015 - 2017 CGV TU Dresden - All Rights Reserved
//
#include <cgv/gui/trigger.h>
#include <cgv/gui/provider.h>
#include <cgv/render/drawable.h>
#include <cgv/render/context.h>
#include <cgv_gl/gl/gl.h>
#include <cgv/math/fmat.h>
#include <cgv/math/fvec.h>
#include <string>

using namespace cgv::base;
using namespace cgv::signal;
using namespace cgv::gui;
using namespace cgv::math;
using namespace cgv::render;
using namespace cgv::utils;


// a 4x4 matrix type called mat4
typedef fmat<float, 4, 4> mat4;
// a 4-component vector type called vec4
typedef fvec<float, 4> vec4;
// a 2-component vector type called vec2
typedef fvec<float, 2> vec2;


// The main class for this exercise
class exercise1 : public node, 
				  public drawable, 
				  public provider
{	
public:
	// The constructor of this class
	exercise1();
	
	// Initialize the shader and vertex buffer
	virtual bool init(context &c);
	// Create the gui elements
	virtual void create_gui();

	// Draw the scene
	virtual void draw(context& c);

	// This method is called whenever the size of the main window changes
	virtual void resize(unsigned int w, unsigned int h);

	// Delete the shader and vertex buffer
	virtual void clear(context &c);

	// Print something on the main window
	void stream_stats(std::ostream& os);

	// Method that is called whenever a gui element was clicked
	void on_set(void* member_ptr);


private:
	// This string might contain the openGL error message if neccessary
	std::string opengl_message;

	bool has_faceculling,	// Shall back face culling be activated?
		 has_depthtesting;	// Shall depth testing be activated?

	mat4 modelview_matrix,	// The modelview matrix
		 projection_matrix;	// The projection matrix

	vec2 julia_c; 			// Seed for the julia fractal
	float julia_zoom;		// Zoom factor for the julia fractal

	float angle_y;			// Rotation angle around the Y-axis

	// The following variables hold OpenGL object IDs
	GLuint vertex_shader_id,	// ID of the vertex shader
           fragment_shader_id,	// ID of the fragment shader
           program_id,			// ID of the shader program
           vertex_array_id,		// ID of the vertex array
           position_buffer_id,	// ID of the position buffer
           color_buffer_id,		// ID of the color buffer
	       uv_map_buffer_id;	// ID of the uv_map


	// Read, Compile and link the shader codes to a shader program
	void create_shaders();
	// Create and define the vertex array and add a number of vertex buffers
	void create_vertex_buffers();

	// Delete the shaders
	void delete_shaders();
	// Delete all vertex buffers
	void delete_vertex_buffers();

	// Calculate a perspective transformation matrix and return the result
	mat4 perspective(float fovy, float aspect, float znear, float zfar);
	// Calculate a translation matrix and return the result
	mat4 translate(float x, float y, float z);
	// Calculate a rotation matrix around the Y-axis and return the result
	mat4 rotate_y(float angle);

	// Update the OpenGL states that are controlled by the has_...-variables
	void update_states();
	// Check if the correct version of OpenGL is supported
	void check_opengl_support();

protected:
	// Check for OpenGL errors and print a message if neccessary
	bool check_error(const std::string &message);
};

