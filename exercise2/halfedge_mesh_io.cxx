//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh_io.h"
#include "obj_reader.h"
#include <iostream>
#include <fstream>

#include <cgv/utils/convert.h>


bool load_obj(halfedge_mesh& m,const std::string& filename)
{
	m.clear();
	std::cout << "loading obj file: "<<filename <<"...";
	obj_reader obj(filename);
	if(obj.get_vertices().size() == 0) 
	{
		return false;
	}
	std::cout << "complete"<<std::endl;
		
	auto& obj_positions = obj.get_vertices();
	auto& obj_normals = obj.get_normals();
	auto& obj_texcoords = obj.get_texcoords();
	auto& obj_faces = obj.get_faces();
	std::cout << "building halfedge mesh...";	
	//for each vertex position in obj create a new vertex in halfedge_mesh 
	int npos = obj_positions.size();
	std::vector<vertex_handle> vhandles = m.new_vertices(npos);
		
	for(int i = 0; i < npos; ++i)
		m.position(vhandles[i]) = obj_positions[i];
	
	//for each face in obj create a new face in halfedge_mesh
	//faces.reserve(obj_faces.size());
	auto fend = obj_faces.end();
	int c = 0;
	for(auto fit = obj_faces.begin(); fit != fend; ++fit)
	{
	//	std::cout << c++<<std::endl;
		auto&  obj_vertices = fit->corners;
		std::vector<vertex_handle> vertex_handles(obj_vertices.size());
		//prepare vector of vertex handles
		int n = (int)obj_vertices.size();
		for(int i = 0; i < n; ++i)
			vertex_handles[i] = vhandles[obj_vertices[i].index_vertex-1];
		//create face with given vertex handles
		face_handle f = m.new_face(vertex_handles);
			
		//assign halfedge normals and texcoords if available
		halfedge_handle he = m.halfedge(f);
		
			
		if(obj_normals.size() == 0) 
		{
			if(obj_texcoords.size() != 0)//texcoords but no normals
			{
				auto vend = obj_vertices.end();
				for(auto vit = obj_vertices.begin(); vit != vend; ++vit)
				{
					m.texcoord(he) = obj_texcoords[vit->index_texcoord-1];
					he = m.next(he);
				}
			}
		}
		else
		{
			if(obj_texcoords.size() != 0)//texcoords and normals
			{
				auto vend = obj_vertices.end();
				for(auto vit = obj_vertices.begin(); vit != vend; ++vit)
				{
					m.normal(he) = obj_normals[vit->index_normal-1];
					m.texcoord(he) = obj_texcoords[vit->index_texcoord-1];
					he = m.next(he);
				}
			}
			else // normals but no texcoords
			{
				auto vend = obj_vertices.end();
				for(auto vit = obj_vertices.begin(); vit != vend; ++vit)
				{
					m.normal(he) = obj_normals[vit->index_normal-1];
					he = m.next(he);
				}
			}
		}
	}
		
	m.complete();
	std::cout << "complete"<<std::endl;
	return true;
}



bool store_obj(halfedge_mesh& m,const std::string& filename)
{
	std::ofstream file; 

	// At least in windows we can handle non-ascii characters
	// by using wide chars to open the file
#ifdef _WIN32
	std::wstring ws = cgv::utils::str2wstr(filename);
	file.open(ws.c_str());
#else
	file.open(filename.c_str());
#endif
	if(!file.is_open())
		return false;

	auto vend = m.vertices_end();
	for(auto vit = m.vertices_begin(); vit != vend; ++vit)
		file << "v "<<m.position(*vit)[0] << " "<<m.position(*vit)[1] << " "<<m.position(*vit)[2] <<"\n";
	
	auto hend = m.halfedges_end();
	for(auto hit = m.halfedges_begin(); hit != hend; ++hit)
		file << "vn "<<m.normal(*hit)[0] << " "<<m.normal(*hit)[1] << " "<<m.normal(*hit)[2] <<"\n";
	
	for(auto hit = m.halfedges_begin(); hit != hend; ++hit)
		file << "vt "<<m.texcoord(*hit)[0] << " "<<m.texcoord(*hit)[1] <<"\n";

	auto fend = m.faces_end();
	for(auto fit = m.faces_begin(); fit != fend; ++fit)
	{
		file << "f ";
		auto fhend = m.halfedges_end(*fit);
		for(auto fhit = m.halfedges_begin(*fit); fhit != fhend; ++fhit)
		{
			file << (int)m.origin(*fhit)+1<<"/"<<(int)*fhit+1<<"/"<<(int)*fhit+1<<" ";
		}
		file <<"\n";
	}
	return true;

}
