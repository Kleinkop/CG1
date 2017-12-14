//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include <random>
#include <cgv/math/fvec.h>

typedef cgv::math::fvec<float,3> vec3;
/*
Usage example:

//create a random engine called eng 
std::mt19937 eng; 
//create random distribution sampler for uniform points on  the unit sphere
uniform_point_on_unit_sphere_distribution sampler;
//sample a point p on the unit sphere using sampler and random engine eng
vec3 p = sampler(eng);
*/
class uniform_point_on_unit_sphere_distribution
{
	std::normal_distribution<float> normal_dist;
	
public:

	
	uniform_point_on_unit_sphere_distribution():normal_dist(0.0f,1.0f)
	{
	}

	//get a random point on the unit sphere using random engine eng
	template <typename Engine>
	vec3 operator()(Engine& eng) 
	{
		vec3 d;
	
		do
		{	
			d[0] = normal_dist(eng);
			d[1] = normal_dist(eng);
			d[2] = normal_dist(eng);
			
		}while(d.length() == 0);

		d.normalize();
		return d;
	}
};






