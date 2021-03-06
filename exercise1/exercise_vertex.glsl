//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015 - 2017 CGV TU Dresden - All Rights Reserved
//
#version 130

in vec4 in_position;
in vec4 in_color;
out vec4 fragment_color;

void main(void)
{

	gl_Position = in_position;
	fragment_color = in_color;
// *** Begin of tasks ***
// - 1.2.2 (b)
// Declare a new "in" variable with the name "in_color". Instead of setting
// "fragment_color" to the position, set it to "in_color. 
// 
// - 1.2.4 (a)
// Declare two new "uniform" variables with the type "vec4" (above the main function)
// that store the modelview and projection matrix. To apply the transformations
// multiply the value of "in_position" before setting "gl_Position".
// 
// - 1.2.5
// The algorithm to calculate the julia fractal needs a position as input.
// Declare another "out" variable and set it to the untransformed input
// position.


// *** End of tasks ***

}
