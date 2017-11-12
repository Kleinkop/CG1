//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015 - 2017 CGV TU Dresden - All Rights Reserved
//
#include "exercise1.h"

#include <cgv/utils/ostream_printf.h>
#include <cgv/utils/file.h>
#include <cgv/utils/tokenizer.h>
#include <cgv/utils/convert.h>

using namespace cgv::utils;

// The constructor of this class
exercise1::exercise1():node("Exercise 1") 
{
	has_depthtesting = true;
	has_faceculling = true;
	angle_y = 0.0f;

	// Some random initializers for the julia fractal
	julia_c.x() = 0.45f;
	julia_c.y() = -0.3f;
	julia_zoom = 1.0f;

	// Set modelview and projection matrix to identity
	modelview_matrix.identity();
	projection_matrix.identity();

	// Check if the required version of OpenGL is supported 
	check_opengl_support();
}



// Initialize the shader and vertex buffer
bool exercise1::init(context& c) {

	GLenum glew_result;
	// Try to init the GLEW library which connects advanced OpenGL methods
	// with the appropriate implementations from the graphics driver
    glew_result = glewInit();
 
	// Declare the whole initialization as failed if GLEW could not be initialized
	if (glew_result != GLEW_OK) {
		std::cerr<<"GLEW could not be initialized: "<<glewGetErrorString(glew_result)<<std::endl;
		return false;
	}

	// Update the OpenGL viewport and the perspective projection
	resize(c.get_width(), c.get_height());

	// Load, compile and link the shader codes to a shader program
	create_shaders();
	// Create a vertex array and add buffers
	create_vertex_buffers();

	return true;
}


// Method that is called whenever a gui element was clicked
void exercise1::on_set(void* member_ptr)
{
	post_redraw();
}



// Create the gui elements
void exercise1::create_gui() {

	// Create a toggle button that controls the bool variable has_depthtesting.
	// Whenever this button is clicked the state of this variable is changed
	// and the post_redraw-method is called.
	add_member_control(this, "Perform Depth Testing", has_depthtesting, "toggle");

	// Create a toggle button that controls the bool variable has_faceculling.
	add_member_control(this, "Perform Backface Culling", has_faceculling, "toggle");

	// Create a value slider that controls the float variable angle_y.
	// Set the minimum value to 0 and the maximum to 360 and enable ticks
	add_member_control(this, "angle", angle_y, "value_slider", "min=0;max=360;ticks=true");

	// Create a value slider that controls the x-value of the julia_c seed
	add_member_control(this, "julia_c.x", julia_c.x(), "value_slider", "min=-1;max=1");

	// Create a value slider that controls the y-value of the julia_c seed
	add_member_control(this, "julia_c.y", julia_c.y(), "value_slider", "min=-1;max=1");

	// Create a value slider that controls the zoom factor.
	// Use a logarithmic scaling for the slider which emphasizes small values
	add_member_control(this, "julia_zoom", julia_zoom, "value_slider", "min=0.01;max=10;log=true");
}




// Check for OpenGL errors and print a message if neccessary
bool exercise1::check_error(const std::string &message)
{
	// Get the last error and clear the error flag
	GLenum gl_error = glGetError();

	// If an error occured then show an error message with a
	// custom prefix and the error code as a string.
	if (gl_error != GL_NO_ERROR) {
		std::cerr<<"Error: "<<message<<": ";
		// If there is an error string then print it, otherwise show the error code
		if (gluErrorString(gl_error))
			std::cout<<gluErrorString(gl_error)<<std::endl;
		else
			std::cout<<std::hex<<gl_error<<std::endl;
		return true;
	}

	return false;
}




// This method is called whenever the size of the main window changes
void exercise1::resize(unsigned int w, unsigned int h)
{
	// Adjust the viewport to correspont to the width and height
	glViewport(0, 0, w, h);
	// Update the projection matrix to account for the new aspect ratio
	projection_matrix = perspective(45.0f, w/(float)h, 0.01f, 100.0f);

}



// Create and define the vertex array and add a number of vertex buffers
void exercise1::create_vertex_buffers()
{
	/*** Begin of task 1.2.3 ***
	Fill the positions-array and your color array with 12 rows, each
	containing 4 entries, to define a tetrahedron. */

	// Define 3 vertices for one face
	GLfloat positions[] = {
		1, 1, 1, 1, //1
		-1, 1, -1, 1, //2
		1, -1, -1, 1, //4
		
		1, 1, 1, 1, //1
		-1, 1, -1, 1, // 2
		-1, -1, 1, 1, // 3
		
		1, 1, 1, 1, //1
		-1, -1, 1, 1, //3
		1, -1, -1, 1, // 4

		-1, 1, -1, 1, //2
		-1, -1, 1, 1, //3
		1, -1 , -1, 1 //4
	};
	
	// Generate the vertex array 
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	// Generate a position buffer to be appended to the vertex array	
	glGenBuffers(1, &position_buffer_id);
	// Bind the buffer for subsequent settings
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_id);

	// Supply the position data
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// The buffer shall now be linked to the shader attribute
	// "in_position". First, get the location of this attribute in 
	// the shader program
	check_error("Could not create position buffe2wr");

	GLuint vid = glGetAttribLocation(program_id, "in_position");
	// Enable this vertex attribute array
	glEnableVertexAttribArray(vid);
	// Set the format of the data to match the type of "in_position"
	glVertexAttribPointer(vid, 4, GL_FLOAT, GL_FALSE, 0, 0);
	// Print an error message if something went wrong
	check_error("Could not create position buffewr");

	/*** Begin of task 1.2.2 (a)
	Create another buffer that will store color information. This works nearly
	similar to the code above that creates the position buffer. Store the buffer
	id into the variable "color_buffer_id" and bind the color buffer to the
	shader variable "in_color".***/

	GLfloat colors[] = {
		1,0,0,1, //1
		1,0,0,1, //2
		1,0,0,1, //3

		0,1,0,1, //1
		0,1,0,1, //3
		0,1,0,1, //4

		0,0,1,1, //1
		0,0,1,1, //2
		0,0,1,1, //4

		0.7,0.2,0.5,1, //2
		0.7,0.2,0.5,1, //3
		0.7,0.2,0.5,1  //4
	};


	glGenBuffers(1, &color_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLint pos_color = glGetAttribLocation(program_id, "in_color");
	glEnableVertexAttribArray(pos_color);
	glVertexAttribPointer(pos_color, 4, GL_FLOAT, GL_FALSE, 0, 0);	

	/*** End of task 1.2.2 (a) ***/


	// Unbind the vertex array to leave OpenGL in a clean state
	glBindVertexArray(0);
}



// Delete the shader and vertex buffer
void exercise1::clear(context &c)
{
	// Only perform deletion if the context is still valid
	if (!c.is_created())
		return;

	// Delete the shader program
	delete_shaders();
	// Delete the vertex buffers
	delete_vertex_buffers();
}



// Read, Compile and link the shader codes to a shader program
void exercise1::create_shaders() 
{
	std::string vertex_shader, fragment_shader;

	// Try to read the vertex shader from disk
	// Read the file "exercise_vertex.glsl" into the string
	// variable vertex_shader. Read it as a text file (true).
	// Fail if the file could not be read.
	if (!file::read("exercise_vertex.glsl", vertex_shader, true)) {
		std::cerr<<"Error: Could not read vertex shader!"<<std::endl;
		return;
	} 

	// Convert the string into a more low-level array of char
	// which will be the input of the vertex shader
	const char *vertex_content = vertex_shader.c_str();

	/*** Begin of task 1.2.1 ***
	Use the appropriate OpenGL commands to create a shader object for
	the vertex shader, set the source code and let it compile. Store the
	ID of this shader object in the variable "vertex_shader_id".
	Read the file "exercise_fragment.glsl" from disk, create a shader
	code object and let the code compile. Store the IDs in the variable
	"fragment_shader_id. Finally, create a shader program with its handle
	stored in "program_id", attach both shader objects and link them.
	For error checking you can use the method "check_error(message)" after 
	every OpenGL call. This method queries the openGL error state and if 
	an error exists prints the message "message" and the human readable error.
	*/
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &vertex_content, NULL);
	glCompileShader(vertex_shader_id);
	check_error("Could not compile the vertex shader");


	if (!file::read("exercise_fragment.glsl", fragment_shader, true)) {
		std::cerr << "Error: Could not read fragment shader!" << std::endl;
		return;
	}

	const char *fragment_content = fragment_shader.c_str();

	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &fragment_content, NULL);
	glCompileShader(fragment_shader_id);

	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);

	glLinkProgram(program_id);
	/*** End of task 1.2.1 ***/

	// Check if everything went well
	check_error("Could not link shader program");
}



// Draw the scene
void exercise1::draw(context& c) 
{
	// Update the states that are controlled by has_depthtesting and has_faceculling
	update_states();

	// Activate the shader program
	glUseProgram(program_id);

	/*** Begin of task 1.2.4 (b) ***
	Set the shader variables for the modelview and projection matrix.
	First, find the location of these variables using glGetUniformLocation and
	then set them with the command glUniformMatrix4fv. For the data pointer you
	can just pass the matrix itself. Before setting the modelview matrix, apply
	a translation of (0, 0, -4). After you implemented the rotate_y-method also
	apply a rotation about the angle "angle_y". To multiply two mat4 variables you
	can use the "*"-operator.
	*/

	/*** End of task 1.2.4 (b) ***/


	// Bind the vertex array 
	glBindVertexArray(vertex_array_id);
	// Draw the bound vertex array. Start at element 0 and draw 3*4 vertices
	glDrawArrays(GL_TRIANGLES, 0, 12);
	// Unbind the vertex array
	glBindVertexArray(0);
	// Deactivate the shader program
	glUseProgram(0);

	// Check for errors
	check_error("Could not draw buffers");
}




// Delete all vertex buffers
void exercise1::delete_vertex_buffers(void)
{
	// Disable all vertex buffers
    glDisableVertexAttribArray(uv_map_buffer_id);
    glDisableVertexAttribArray(color_buffer_id);
    glDisableVertexAttribArray(position_buffer_id);
      
	// Delete the buffers
    glDeleteBuffers(1, &uv_map_buffer_id);
    glDeleteBuffers(1, &color_buffer_id);
    glDeleteBuffers(1, &position_buffer_id);
 
	// Finally delete the vertex array
    glDeleteVertexArrays(1, &vertex_array_id);
	check_error("Could not destroy vertex buffers");
}




// Delete the shaders
void exercise1::delete_shaders(void)
{ 
	// Detach the vertex shader from the program
    glDetachShader(program_id, vertex_shader_id);
	// Detach the fragment shader from the program
    glDetachShader(program_id, fragment_shader_id);
 
	// Delete the vertex and fragment shader
    glDeleteShader(fragment_shader_id);
    glDeleteShader(vertex_shader_id);
 
	// Finally, delete the program
    glDeleteProgram(program_id);
	check_error("Could not delete shaders");
}




void exercise1::update_states()
{
	// If has_faceculling is set then enable backface culling
	// and disable it otherwise
	if (has_faceculling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// If has_depthtesting is set then enable depth testing
	// and disable it otherwise
	if (has_depthtesting)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}



// Calculate a perspective transformation matrix and return the result
mat4 exercise1::perspective(float fovy, float aspect, float znear, float zfar)
{
	// Convert the field-of-view angle from degrees to radians
	float fovy_radians = fovy*(float)M_PI/180.0f;
	// Calculate all needed values just as gluPerspective does
	float f = cos(fovy_radians/2.0f)/sin(fovy_radians/2.0f);
	float a = (zfar+znear)/(znear-zfar);
	float b = (2*zfar*znear)/(znear-zfar);

	// Fill the data of a matrix
	float matrix_data[16] = {
		f/aspect, 0,  0, 0,
		0       , f,  0, 0,
		0       , 0,  a, b,
		0       , 0,  -1, 0
	};

	// Create a new matrix from the data
	mat4 matrix = matrix_data;
	// Return its transpose.
	// Note: The transpose is returned because the mat4 class stores the matrix
	// data in a column wise order while the upper definition of matrix_data is
	// a row-wise definition, i.e. the data is defined row-by-row.
	return transpose(matrix);
}



// Calculate a translation matrix and return the result
mat4 exercise1::translate(float x, float y, float z)
{
	// Create translation matrix data from the input parameters
	float matrix_data[16] = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};

	// Create a matrix from the data
	mat4 matrix = matrix_data;
	// Return the transpose
	return transpose(matrix);
}



// Calculate a rotation matrix around the Y-axis and return the result
mat4 exercise1::rotate_y(float angle)
{
	/*** Begin of task 1.2.4 (c) ***
	Implement the creation of a rotation around the Y-axis. First,
	convert the angle from degrees to radians and then define two
	new variables which contain the sine and cosine of this value.
	Finally replace the corresponding values from "matrix_data" below
	to create the rotation matrix.
	*/

	// Create the matrix data for the rotation matrix
	float matrix_data[16] = {
		 1, 0, 0, 0,
		 0, 1, 0, 0,
		 0, 0, 1, 0,
		 0, 0, 0, 1
	};

	/*** End of task 1.2.4 (c) ***/

	// Create a matrix from the data
	mat4 matrix = matrix_data;
	// Return the transpose
	return transpose(matrix);
}




// Check if the correct version of OpenGL is supported
void exercise1::check_opengl_support()
{
	bool success = true;
	int ogl_major, ogl_minor, glsl_major, glsl_minor;

	std::vector<token> toks;
	// Read the version string and tokenize it at "." and whitespaces
	bite_all(tokenizer((char*)glGetString(GL_VERSION)).set_ws(". "), toks);
	// If there are at least two tokens then extract the major and minor version number
	if (toks.size()>=2) {
		success = from_string(ogl_major, to_string(toks[0])) & success;
		success = from_string(ogl_minor, to_string(toks[1])) & success;
	} else 
		success = false;

	toks.clear();
	// Read the shading language version string and tokenize it at "." and whitespaces
	bite_all(tokenizer((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)).set_ws(". "), toks);
	if (toks.size()>=2) {
		success = from_string(glsl_major, to_string(toks[0])) & success;
		success = from_string(glsl_minor, to_string(toks[1])) & success;
	} else 
		success = false;

	if (!success) {
		opengl_message = "ERROR: COULD NOT PARSE OPENGL-VERSION STRING!\n";
		return;
	}

	if (ogl_major<3 || (glsl_minor<3 && glsl_major == 1)) { 
		std::stringstream error_msg;
		error_msg<<"ERROR: YOUR VERSION OF OPENGL IS TOO OLD!"<<std::endl;
		error_msg<<"  - Needed Opengl-Version: 3.0. On this system: "<<glGetString(GL_VERSION)<<std::endl;
		error_msg<<"  - Needed GLSL-Version: 1.3. On this system: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;

		opengl_message = error_msg.str();
	}
}




// Print something on the main window
void exercise1::stream_stats(std::ostream& os)
{
	// Print the OpenGL error message if available
	oprintf(os, opengl_message.c_str());
}
