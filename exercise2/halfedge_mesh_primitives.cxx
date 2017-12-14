//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh_primitives.h"
#include "halfedge_mesh.h"

halfedge_mesh create_quad()
{
	halfedge_mesh m;		
	std::vector<vertex_handle> vhandles = m.new_vertices(4);	
	m.position(vhandles[0]).set(-0.5f, -0.5f,  0);
	m.position(vhandles[1]).set(0.5f, -0.5f,  0);
	m.position(vhandles[2]).set(0.5f, 0.5f,  0);
	m.position(vhandles[3]).set(-0.5f, 0.5f,  0);
	m.new_face(vhandles);
	m.complete();
	return m;
}

halfedge_mesh create_cube()
{
	//student begin
	halfedge_mesh m;
	std::vector<vertex_handle> vhandles = m.new_vertices(8);
	m.position(vhandles[0]).set(-0.5f, -0.5f, -0.5f);
	m.position(vhandles[1]).set(0.5f, -0.5f, -0.5f);
	m.position(vhandles[2]).set(0.5f, -0.5f, 0.5f);
	m.position(vhandles[3]).set(-0.5f, -0.5f, 0.5f);
	m.position(vhandles[4]).set(-0.5f, 0.5f, -0.5f);
	m.position(vhandles[5]).set(0.5f, 0.5f, -0.5f);
	m.position(vhandles[6]).set(0.5f, 0.5f, 0.5f);
	m.position(vhandles[7]).set(-0.5f, 0.5f, 0.5f);

	std::vector<vertex_handle> face_vhandles;
	face_vhandles.clear();
	face_vhandles.push_back(vhandles[0]);
	face_vhandles.push_back(vhandles[1]);
	face_vhandles.push_back(vhandles[2]);
	face_vhandles.push_back(vhandles[3]);
	m.new_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vhandles[4]);
	face_vhandles.push_back(vhandles[7]);
	face_vhandles.push_back(vhandles[6]);
	face_vhandles.push_back(vhandles[5]);
	m.new_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vhandles[4]);
	face_vhandles.push_back(vhandles[5]);
	face_vhandles.push_back(vhandles[1]);
	face_vhandles.push_back(vhandles[0]);
	m.new_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vhandles[7]);
	face_vhandles.push_back(vhandles[4]);
	face_vhandles.push_back(vhandles[0]);
	face_vhandles.push_back(vhandles[3]);
	m.new_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vhandles[5]);
	face_vhandles.push_back(vhandles[6]);
	face_vhandles.push_back(vhandles[2]);
	face_vhandles.push_back(vhandles[1]);
	m.new_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vhandles[6]);
	face_vhandles.push_back(vhandles[7]);
	face_vhandles.push_back(vhandles[3]);
	face_vhandles.push_back(vhandles[2]);
	m.new_face(face_vhandles);

	m.complete();
	return m;
	
	//student end
}

halfedge_mesh create_tetrahedron(float a)
{
	
	
	halfedge_mesh m;
	
	std::vector<vertex_handle> vhandles = m.new_vertices(4);
		
	m.position(vhandles[0]).set(sqrt(3.0f)*a/3.0f,      0, 0);
	m.position(vhandles[1]).set(-sqrt(3.0f)*a/6.0f,-a/2.0f, 0);
	m.position(vhandles[2]).set(-sqrt(3.0f)*a/6.0f, a/2.0f, 0);
	m.position(vhandles[3]).set(     0,      0, sqrt(6.0f)*a/3.0f);
	
	std::vector<vertex_handle>  face_vhandles;
	face_vhandles.clear();
	face_vhandles.push_back(vhandles[0]);
	face_vhandles.push_back(vhandles[1]);
	face_vhandles.push_back(vhandles[2]);
	m.new_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vhandles[0]);
	face_vhandles.push_back(vhandles[2]);
	face_vhandles.push_back(vhandles[3]);	
	m.new_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vhandles[0]);
	face_vhandles.push_back(vhandles[3]);
	face_vhandles.push_back(vhandles[1]);
	m.new_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vhandles[3]);
	face_vhandles.push_back(vhandles[2]);
	face_vhandles.push_back(vhandles[1]);
	m.new_face(face_vhandles);
	m.complete();
	
	return m;
}

halfedge_mesh create_disk(float radius, int slices)
{
	halfedge_mesh m;
	std::vector<vertex_handle> vhandles = m.new_vertices(slices+1);
	m.position(vhandles[0]).set(0.0f,0.0f,0.0f);
	for(int i = 0; i < slices;i++)
	{
		float angle= -i*2*3.14159f/slices;
		m.position(vhandles[i+1]).set(cos(angle)*radius, 0.0f, sin(angle)*radius);
	}
	for(int i = 0; i < slices;i++)
	{
		m.new_triangle(vhandles[0],vhandles[1+i%slices],vhandles[1+(1+i)%slices]);
	}
	m.complete();
	return m;	
}

//create a cylinder mesh 
halfedge_mesh create_cylinder(float radius, float height,int stacks, int slices)
{
	
	assert(slices >= 3 && stacks >= 1);

	halfedge_mesh m;
	
	int n = 2+slices*(stacks+1);
	std::vector<vertex_handle> vhandles = m.new_vertices(n);
	
	m.position(vhandles[0]).set(0.0f,height,0.0f);

	int k=1;
	for(int i = 0; i < stacks+1; i++)
	{			
		float h = (stacks-i)*height/(stacks);

		for(int j = 0; j < slices; j++)
		{
			float angle2 = j*2.0f*3.14159f/(float)(slices);
			m.position(vhandles[k]).set(cos(angle2)*radius,h,sin(angle2)*radius);
			
			k++;
		}
	}

	m.position(vhandles[k]).set(0.0f,0.0f,0.0f);

	for(int i = 0; i < slices; i++)
	{	
		m.new_triangle(vhandles[0],vhandles[1+(1+i)%slices],vhandles[1+i%slices]);
		
		for(int j = 0; j < stacks;j++)
		{
			int a,b,c,d;
			a = 1+j*slices+(i)%slices;
			b = 1+j*slices+(1+i)%slices;
			c = 1+(j+1)*slices+(1+i)%slices;
			d = 1+(j+1)*slices+(i)%slices;
			m.new_quad(vhandles[a],vhandles[b],vhandles[c],vhandles[d]);
		}
		m.new_triangle(vhandles[vhandles.size()-1],
			vhandles[1+(stacks)*slices+(i)%slices],
			vhandles[1+(stacks)*slices+(1+i)%slices]);			
	}
	m.complete();
	return m;	
}

//create a sphere mesh
halfedge_mesh create_sphere(float radius, int slices, int stacks)
{
	assert(slices >= 3 && stacks >= 3);
	
	halfedge_mesh m;
		
	
	int n = slices*(stacks-1) + 2;
	std::vector<vertex_handle> vhandles = m.new_vertices(n);

	m.position(vhandles[0]).set(0.0f,radius,0.0f);
	
	int k = 1;
	for(int i = 1; i < stacks; i++)
	{
		float angle1 = 3.14159f/2.0f-i*3.14159f/(float)stacks;
		float r = cos(angle1)*radius;
		float height =sin(angle1)*radius;

		for(int j = 0; j < slices; j++)
		{
			float angle2 = j*2.0f*3.14159f/(float)(slices);
			m.position(vhandles[k]).set(cos(angle2)*r,height,sin(angle2)*r);
			k++;
		}
	}
		
	m.position(vhandles[k]).set(0.0f,-radius,0.0f);
	
	for(int i = 0; i < slices; i++)
	{	
		m.new_triangle(vhandles[0],vhandles[1+(1+i)%slices],vhandles[1+i%slices]);
		
		for(int j = 0; j < stacks-2;j++)
		{
			int a,b,c,d;
			a = 1+j*slices+(i)%slices;
			b = 1+j*slices+(1+i)%slices;
			c = 1+(j+1)*slices+(1+i)%slices;
			d = 1+(j+1)*slices+(i)%slices;
			m.new_quad(vhandles[a],vhandles[b],vhandles[c],vhandles[d]);
		}
		m.new_triangle(vhandles[1+slices*(stacks-1)],
				vhandles[1+(stacks-2)*slices+(i)%slices],
				vhandles[1+(stacks-2)*slices+(1+i)%slices]);			
	}
	m.complete();
	return m;	
}

//create a torus mesh
halfedge_mesh create_torus(float r,float R,int nsides,int rings)
{
	assert(nsides >= 3 && rings >= 3);	
	halfedge_mesh m;

	int n = rings*nsides;
	std::vector<vertex_handle> vhandles = m.new_vertices(n);
	int k = 0;
	for(int i = 0; i < rings; i++)
	{
		float angle1=(float)(i*2.0*3.14159/(rings));
		vec3 center(cos(angle1)*R,0.0f,sin(angle1)*R);
		vec3 t1(cos(angle1),0.0,sin(angle1));
		vec3 t2(0.0f,1.0f,0.0f);

		for(int j = 0; j < nsides; j++)
		{
			float angle2=(float)(j*2.0*3.14159/(nsides));
			m.position(vhandles[k])=center+(float)(sin(angle2)*r)*t1+(float)(cos(angle2)*r)*t2 ;
			k++;
		}	
	}

	for(int i = 0; i < rings; i++)
	{
		for(int j = 0; j < nsides; j++)
		{
			int a,b,c,d;
			a = (i+1)%(rings)*(nsides)+j;
			b = (i+1)%(rings)*(nsides)+(j+1)%(nsides);
			c = i*(nsides)+(j+1)%(nsides);
			d = i*(nsides)+j;
			m.new_quad(
				vhandles[a], vhandles[b],
				vhandles[c], vhandles[d]);
				
				
			
		}
	}
	m.complete();
	return m;	
}


//creates an icosaeder mesh in m 
// radius is the radius of the circum sphere

halfedge_mesh create_icosaeder(float radius)
{
	
	halfedge_mesh m;
	
	
	
	float a  = (float)(radius*4.0/sqrt(10.0+2.0*sqrt(5.0)));
	float h = (float)cos(2.0*asin(a/(2.0*radius)))*radius;
	float r2 = (float)sqrt(radius*radius-h*h);

	std::vector<vertex_handle> vhandles = m.new_vertices(12);
	int k = 0;
	m.position(vhandles[k++]).set(0,radius,0);

	for(int i = 0; i < 5;i++)
		m.position(vhandles[k++]).set((float)cos(i*72.0*3.14159/180.0)*r2,h,-(float)sin(i*72.0*3.14159/180.0)*r2);
	
	for(int i = 0; i < 5;i++)
		m.position(vhandles[k++]).set((float)cos(36.0*3.14159/180.0+i*72.0*3.14159/180.0)*r2,-h,-(float)sin(36.0*3.14159/180.0+i*72.0*3.14159/180.0)*r2);
		
	m.position(vhandles[k]).set(0,-radius,0);
	
	for(int i = 0;i < 5;i++)
	{
		m.new_triangle(vhandles[0],vhandles[i+1],vhandles[(i+1)%5+1]);
		m.new_triangle(vhandles[11],vhandles[(i+1)%5+6],vhandles[i+6]);
		m.new_triangle(vhandles[i+1],vhandles[i+6],vhandles[(i+1)%5+1]);
		m.new_triangle(vhandles[(i+1)%5+1],vhandles[i+6],vhandles[(i+1)%5+6]);	
	}
	m.complete();
	return m;
}


//creates an octaeder mesh
// radius is the radius of the circum sphere
halfedge_mesh create_octaeder(float radius)
{
	halfedge_mesh m;
		
	std::vector<vertex_handle> vhandles = m.new_vertices(6);
	int k = 0;
	m.position(vhandles[k++]).set(0,radius,0);	
	
		
	for(int i = 0; i < 4; i++)
		m.position(vhandles[k++]).set((float)cos(i*3.14159/2.0)*radius,0,-(float)sin(i*3.14159/2.0)*radius);


	m.position(vhandles[k++]).set(0,-radius,0);

	

	for(int i = 0; i < 4; i++)
	{
		m.new_triangle(vhandles[0],vhandles[i+1],vhandles[(i+1)%4+1]);
		m.new_triangle(vhandles[5],vhandles[(i+1)%4+1],vhandles[i+1]);	
	}
	m.complete();
	return m;	

}

//create a unit arrow

halfedge_mesh create_unit_arrow(float stem_radius,float head_radius,float stem_height, int slices, int stem_stacks)
{
	
	assert(slices >= 3 && stem_stacks >= 1&&stem_height <= 1 && stem_height >= 0);

	float head_height=(float)1-stem_height;
	halfedge_mesh m;
	
	int n  = 2+slices*(stem_stacks+2);
	std::vector<vertex_handle> vhandles = m.new_vertices(n);
	
	float height = stem_height+ head_height;
	m.position(vhandles[0]).set(0.0f,height,0.0f);
	
	int k=1;
	for(int j = 0; j < slices; j++)
	{
		float angle2 = j*2.0f*3.14159f/(float)(slices);
		m.position(vhandles[k]).set(cos(angle2)*head_radius,stem_height,sin(angle2)*head_radius);
		k++;
	}

	for(int i = 0; i < stem_stacks+1; i++)
	{			
		float h = (stem_stacks-i)*stem_height/(stem_stacks);

		for(int j = 0; j < slices; j++)
		{
			float angle2 = j*2.0f*3.14159f/(float)(slices);
			m.position(vhandles[k]).set(cos(angle2)*stem_radius,h,sin(angle2)*stem_radius);
			k++;
		}
	}
	m.position(vhandles[k]).set(0.0f,0.0f,0.0f);
	
	for(int i = 0; i < slices; i++)
	{	
		m.new_triangle(vhandles[0],vhandles[1+(1+i)%slices],vhandles[1+i%slices]);
		
		for(int j = 0; j < stem_stacks+1;j++)
		{
			int a,b,c,d;
			a = 1+j*slices+(i)%slices;
			b = 1+j*slices+(1+i)%slices;
			c = 1+(j+1)*slices+(1+i)%slices;
			d = 1+(j+1)*slices+(i)%slices;
			m.new_quad(vhandles[a],vhandles[b],vhandles[c],vhandles[d]);
		}
		m.new_triangle(vhandles[vhandles.size()-1],
			vhandles[1+(stem_stacks+1)*slices+(i)%slices],
			vhandles[1+(stem_stacks+1)*slices+(1+i)%slices]);			
	}
	m.complete();
	return m;	
}
