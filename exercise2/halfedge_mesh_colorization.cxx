//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh_colorization.h"





//create a circular colormap with n colors 
//interpolating red - yellow - green - cyan- blue - magenta and back to red 
colormap create_hsv_color_map(int n) 
{
	if(n <2)
		n=2;

	std::vector<vec3> cmap(n);
	for(int i = 0; i < n; ++i)
	{
		float f = i/(float)(n-1);
	//	std::cout << "f:" <<f<<std::endl;
		cmap[i](0)=cmap[i](1)=cmap[i](2)=0.0f;
			
			if(f <= 1.0f/5.0f) 
				cmap[i](0) =  1.0f;
			if(f > 1.0f/5.0f && f <=2.0f/5.0f)
				cmap[i](0) =  -5.0f*f + 2.0f;
			if(f > 4.0f/5.0f)
				cmap[i](0) = 5.0f*f-4.0f;

			if(f <= 1.0f/5.0f) 
				cmap[i](1) =  5.0f*f;
			if(f > 1.0f/5.0f && f <=3.0f/5.0f)
				cmap[i](1) =  1.0f;
			if(f > 3.0f/5.0f && f <= 4.0f/5.0f)
				cmap[i](1) = -5.0f*f+4.0f;


			
			if(f > 2.0f/5.0f && f <=3.0f/5.0f)
				cmap[i](2) =  5.0f*f-2.0f;
			if(f > 3.0f/5.0f && f <= 4.0f/5.0f)
				cmap[i](2) = 1.0f;
			if(f >4.0f/5.0f) 
				cmap[i](2) =  -5.0f*f+5.0f;
				
		
	}
	return cmap;
}

//create a grayscale colormap with n colors 
colormap create_grayscale_color_map(int n) 
{
	vec3 black(0,0,0);
	vec3 white(1,1,1);
	std::vector<vec3> cmap(n);
	for(int i = 0; i < n; ++i)
	{
		float alpha = i/(float)(n-1);

		cmap[i] = alpha*black + (1-alpha)*white;
			continue;
	}
		
	return cmap;
}


//interpolating red - yellow - green - cyan- blue - magenta and back to red 
colormap create_jet_color_map(int n) 
{
	vec3 darkblue(0,0,0.5);
	vec3 blue(0,0,1);
	vec3 cyan(0,1,1);
	vec3 yellow(1,1,0);
	vec3 red(1,0,0);
	vec3 darkred(0.5,0,0);
	std::vector<vec3> cmap(n);
	for(int i = 0; i < n; ++i)
	{
		float f = i/(float)(n-1);
		/*for(unsigned i = 0; i < steps;i++)
		{*/
			cmap[i](0) = 0;
			cmap[i](1) = 0;
			cmap[i](2) = 0;
			
			if((f >= 3.0f/8.0f) && (f < 5.0f/8.0f)) 
				cmap[i](0) = (4.0f * f - 3.0f/2.0f);
		
			if((f >= 5.0f/8.0f) && (f < 7.0f/8.0f))
			{
				cmap[i](0)=1.0f;
			}
			if(f >= 7.0f/8.0f)
				cmap[i](0)+= -4.0f * f + 9.0f/2.0f;
			
			
			if(f >= 1.0f/8.0f && f < 3.0f/8.0f)
				cmap[i](1)= (4.0f * f - 1.0f/2.0f);

			if(f >= 3.0f/8.0f && f < 5.0f/8.0f)
			{ 
				cmap[i](1)=1;
			}
			if(f >= 5.0f/8.0f && f < 7.0f/8.0f)
					cmap[i](1) += (-4.0f * f + 7.0f/2.0f);
			

			if(f < 1.0f/8.0f)
				cmap[i](2)= (4.0f * f + 1.0f/2.0f);

			if(f >= 1.0f/8.0f && f < 3.0f/8.0f)
			{
				cmap[i](2)=1.0;
			}
			if(f >= 3.0f/8.0f && f < 5.0f/8.0f)
				cmap[i](2) += -4.0f * f + 5.0f/2.0f;
			

	

		//}/**/

	/*//	std::cout << "f:" <<f<<std::endl;
		if(f < 1/5.0f)
		{
			float alpha = f*5;
		//	std::cout << alpha << std::endl;
			cmap[i] = alpha*darkblue + (1-alpha)*blue;
			continue;
		}
		if(f < 2/5.0f)
		{
			float alpha = f-(1.0f/5.0f);
			alpha *=5;
		//	std::cout << alpha << std::endl;
			cmap[i] = alpha*blue + (1-alpha)*cyan;
			continue;
		}
		if(f < 3/5.0f)
		{
			float alpha = f-(2.0f/5.0f);
			alpha *=5;
		//	std::cout << alpha << std::endl;
			cmap[i] = alpha*cyan + (1-alpha)*yellow;
			continue;
		}
		if(f < 4/5.0f)
		{
			float alpha = f-(3.0f/5.0f);
			alpha *=5;
		//	std::cout << alpha << std::endl;
			cmap[i] = alpha*yellow + (1-alpha)*red;
			continue;
		}
		
		{
			float alpha = f-(4.0f/5.0f);
			alpha *=5;
		//	std::cout << alpha << std::endl;
			cmap[i] = alpha*red + (1-alpha)*darkred;
			continue;
		}*/
		

	}
	return cmap;
}


//create color map with n color by random shuffling hsv colormap
colormap create_permutated_hsv_color_map(int n) 
{
	int m = n;
	if(m%2 == 0)
		m++;
	int step = m/2;
	colormap hsv_map  = create_hsv_color_map(m);
	colormap cmap(n);
	int j = 0;
	for(int i = 0; i < n; ++i)
	{
		cmap[i] =hsv_map[j];
		j=(j+step)%m;
	}
	return cmap;
}

void colorize_faces(halfedge_mesh& mesh,const std::vector<int>& face_attributes)
{
	int nmax= *std::max_element(face_attributes.begin(), face_attributes.end());
	int nmin= *std::min_element(face_attributes.begin(), face_attributes.end());
	int n =  nmax+1-nmin;
	colormap cmap = create_permutated_hsv_color_map(n);
	face_iterator fend = mesh.faces_end();
	for(face_iterator fit = mesh.faces_begin(); fit != fend; ++fit)
		mesh.color(*fit) = cmap[face_attributes[*fit]-nmin];
		
}	

void colorize_faces(halfedge_mesh& mesh,const std::vector<float>& face_attributes,float vmin, float vmax, int n)
{
	
	
	colormap cmap = create_jet_color_map(n);
	face_iterator fend = mesh.faces_end();
	for(face_iterator fit = mesh.faces_begin(); fit != fend; ++fit)
	{
		int idx = (int)((n-1)*(face_attributes[*fit]-vmin)/(vmax-vmin));
		idx = (std::max)(0,idx);
		idx = (std::min)(n-1,idx);
		mesh.color(*fit) = cmap[idx];
	}
		
}

void colorize_vertices(halfedge_mesh& mesh,const std::vector<float>& vertex_attributes,
	float vmin, float vmax, int n)
{
	colormap cmap = create_jet_color_map(n); 
	vertex_iterator vend = mesh.vertices_end();
	for(vertex_iterator vit = mesh.vertices_begin(); vit != vend; ++vit)
	{
		int idx = (int)((n-1)*(vertex_attributes[*vit]-vmin)/(vmax-vmin));
		idx = (std::max)(0,idx);
		idx = (std::min)(n-1,idx);
		mesh.color(*vit) = cmap[idx];
	}
}
