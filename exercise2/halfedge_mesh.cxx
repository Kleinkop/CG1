//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include <cassert>
#include "halfedge_mesh.h"



halfedge_mesh::halfedge_mesh():completed(true){}


vec3& halfedge_mesh::position(const vertex_handle& v)
{
	return vertices[v].position;
}

const vec3& halfedge_mesh::position(const vertex_handle& v) const
{
	return vertices[v].position;
}

vec3& halfedge_mesh::color(const vertex_handle& v)
{
	return vertices[v].color;
}

const vec3& halfedge_mesh::color(const vertex_handle& v) const
{
	return vertices[v].color;
}


vec3& halfedge_mesh::normal(const vertex_handle& v)
{
	return vertices[v].normal;
}
	
const vec3& halfedge_mesh::normal(const vertex_handle& v) const
{
	return vertices[v].normal;
}

vec3& halfedge_mesh::normal(const halfedge_handle& he)
{
	return halfedges[he].normal;
}
	
const vec3& halfedge_mesh::normal(const halfedge_handle& he) const
{
	return halfedges[he].normal;
}

vec3& halfedge_mesh::normal(const face_handle& f)
{
	return faces[f].normal;
}
	
const vec3& halfedge_mesh::normal(const face_handle& f) const
{
	return faces[f].normal;
}

vec3& halfedge_mesh::color(const face_handle& f)
{
	return faces[f].color;
}
	
const vec3& halfedge_mesh::color(const face_handle& f) const
{
	return faces[f].color;
}


vec2& halfedge_mesh::texcoord(const halfedge_handle& he)
{
	return halfedges[he].texcoord;
}
	
const vec2& halfedge_mesh::texcoord(const halfedge_handle& he) const
{
	return halfedges[he].texcoord;
}


halfedge_handle& halfedge_mesh::next(const halfedge_handle& h) 
{
	return halfedges[h].next;
}

const halfedge_handle& halfedge_mesh::next(const halfedge_handle& h) const
{
	return halfedges[h].next;
}

halfedge_handle& halfedge_mesh::prev(const halfedge_handle& h) 
{
	return halfedges[h].prev;
}

const halfedge_handle& halfedge_mesh::prev(const halfedge_handle& h) const
{
	return halfedges[h].prev;
}
	
halfedge_handle& halfedge_mesh::inverse(const halfedge_handle& h) 
{
	return halfedges[h].inverse;
}

const halfedge_handle& halfedge_mesh::inverse(const halfedge_handle& h) const
{
	return halfedges[h].inverse;
}
	
vertex_handle& halfedge_mesh::origin(const halfedge_handle& h) 
{
	return halfedges[h].origin;
}

const vertex_handle& halfedge_mesh::origin(const halfedge_handle& h) const
{
	return halfedges[h].origin;
}
	
vertex_handle& halfedge_mesh::target(const halfedge_handle& h) 
{
	return origin(next(h));
}

const vertex_handle& halfedge_mesh::target(const halfedge_handle& h)  const
{
	return origin(next(h));
}

vertex_handle& halfedge_mesh::origin(const edge_handle& e) 
{
	return origin(halfedge(e));
}

const vertex_handle& halfedge_mesh::origin(const edge_handle& e) const
{
	return origin(halfedge(e));
}
	
vertex_handle& halfedge_mesh::target(const edge_handle& e) 
{
	return target(halfedge(e));
}

const vertex_handle& halfedge_mesh::target(const edge_handle& e)  const
{
	return target(halfedge(e));
}

face_handle& halfedge_mesh::face(const halfedge_handle& h) 
{
	return halfedges[h].face;
}

const face_handle& halfedge_mesh::face(const halfedge_handle& h) const
{
	return halfedges[h].face;
}

edge_handle& halfedge_mesh::edge(const halfedge_handle& h) 
{
	return halfedges[h].edge;
}

const edge_handle& halfedge_mesh::edge(const halfedge_handle& h) const
{
	return halfedges[h].edge;
}
	
halfedge_handle& halfedge_mesh::halfedge(const vertex_handle& v)
{
	return vertices[v].halfedge;
}

const halfedge_handle& halfedge_mesh::halfedge(const vertex_handle& v) const
{
	return vertices[v].halfedge;
}

halfedge_handle& halfedge_mesh::halfedge(const face_handle& f)
{
	return faces[f].halfedge;
}

const halfedge_handle& halfedge_mesh::halfedge(const face_handle& f) const
{
	return faces[f].halfedge;
}

halfedge_handle& halfedge_mesh::halfedge(const boundary_handle& b)
{
	return boundaries[b].halfedge;
}

const halfedge_handle& halfedge_mesh::halfedge(const boundary_handle& b) const
{
	return boundaries[b].halfedge;
}

halfedge_handle& halfedge_mesh::halfedge(const edge_handle& e)
{
	return edges[e].halfedge;
}

const halfedge_handle& halfedge_mesh::halfedge(const edge_handle& e) const
{
	return edges[e].halfedge;
}

const vertex_iterator halfedge_mesh::vertices_begin() const
{
	return vertex_iterator(this,vertex_handle(0));
}

const vertex_iterator halfedge_mesh::vertices_end() const
{
	return vertex_iterator(this,vertex_handle(num_vertices()));
}

const vertex_face_iterator halfedge_mesh::faces_begin(const vertex_handle& v) const
{
	assert(is_completed());
	return vertex_face_iterator(this,v,false);
}
const vertex_face_iterator halfedge_mesh::faces_end(const vertex_handle& v) const
{
	assert(is_completed());
	return vertex_face_iterator(this,v,true);
}

const halfedge_iterator halfedge_mesh::halfedges_begin() const
{
	return halfedge_iterator(this,halfedge_handle(0));
}

const halfedge_iterator halfedge_mesh::halfedges_end() const
{
	return halfedge_iterator(this,halfedge_handle(num_halfedges()));
}

const edge_iterator halfedge_mesh::edges_begin() const
{
	assert(is_completed());
	return edge_iterator(this,edge_handle(0));
}

const edge_iterator halfedge_mesh::edges_end() const
{
	assert(is_completed());
	return edge_iterator(this,edge_handle(num_edges()));
}

const face_iterator halfedge_mesh::faces_begin() const
{
	return face_iterator(this,face_handle(0));
}

const face_iterator halfedge_mesh::faces_end() const
{
	return face_iterator(this,face_handle(num_faces()));
}
	
const boundary_iterator halfedge_mesh::boundaries_begin() const
{
	assert(is_completed());
	return boundary_iterator(this,boundary_handle(0));
}

const boundary_iterator halfedge_mesh::boundaries_end() const
{
	assert(is_completed());
	return boundary_iterator(this,boundary_handle(num_boundaries()));
}

const face_vertex_iterator halfedge_mesh::vertices_begin(const face_handle& f) const
{
	return face_vertex_iterator(this,f,false);
}

const face_vertex_iterator halfedge_mesh::vertices_end(const face_handle& f) const
{
	return face_vertex_iterator(this,f,true);
}

const face_halfedge_iterator halfedge_mesh::halfedges_begin(const face_handle& f) const
{
	return face_halfedge_iterator(this,f,false);
}

const face_halfedge_iterator halfedge_mesh::halfedges_end(const face_handle& f) const
{
	return face_halfedge_iterator(this,f,true);
}

//returns an iterator pointing at the first outer halfedge of face f 
const face_outer_halfedge_iterator halfedge_mesh::outer_halfedges_begin(const face_handle& f) const
{
	assert(is_completed());
	return face_outer_halfedge_iterator(this,f,false);
}
//returns an iterator pointing after the last outer halfedge of face f 
const face_outer_halfedge_iterator halfedge_mesh::outer_halfedges_end(const face_handle& f) const
{
	assert(is_completed());
	return face_outer_halfedge_iterator(this,f,true);
}

//returns an iterator pointing at the first edge-adjacent face of face f 
const face_face_iterator halfedge_mesh::faces_begin(const face_handle& f) const
{
	assert(is_completed());
	return face_face_iterator(this,f,false);
}
//returns an iterator pointing after the last edge-adjacent face of face f 
const face_face_iterator halfedge_mesh::faces_end(const face_handle& f) const
{
	assert(is_completed());
	return face_face_iterator(this,f,true);
}

//returns an iterator pointing at the first edge of the face f 
const face_edge_iterator halfedge_mesh::edges_begin(const face_handle& f) const
{
	assert(is_completed());
	return face_edge_iterator(this,f,false);
}
//returns an iterator pointing after the last edge of the face f 
const face_edge_iterator halfedge_mesh::edges_end(const face_handle& f) const
{
	assert(is_completed());
	return face_edge_iterator(this,f,true);
}

//returns an iterator pointing at the first vertex of the boundary loop b
const boundary_vertex_iterator halfedge_mesh::vertices_begin(const boundary_handle& b) const
{
	assert(is_completed());
	return boundary_vertex_iterator(this,b,false);
}
//returns an iterator pointing after the last vertex of the boundary loop b
const boundary_vertex_iterator halfedge_mesh::vertices_end(const boundary_handle& b) const
{
	assert(is_completed());
	return boundary_vertex_iterator(this,b,true);
}

//returns an iterator pointing at the first halfedge of the boundary loop b
const boundary_halfedge_iterator halfedge_mesh::halfedges_begin(const boundary_handle& b) const
{
	assert(is_completed());
	return boundary_halfedge_iterator(this,b,false);
}
//returns an iterator pointing after thr last halfedge of the boundary loop b
const boundary_halfedge_iterator halfedge_mesh::halfedges_end(const boundary_handle& b) const
{
	assert(is_completed());
	return boundary_halfedge_iterator(this,b,true);
}

//returns an iterator pointing at the first edge of the boundary loop b
const boundary_edge_iterator halfedge_mesh::edges_begin(const boundary_handle& b) const
{
	assert(is_completed());
	return boundary_edge_iterator(this,b,false);
}
//returns an iterator pointing after the last edge of the boundary loop b
const boundary_edge_iterator halfedge_mesh::edges_end(const boundary_handle& b) const
{
	assert(is_completed());
	return boundary_edge_iterator(this,b,true);
}

//returns an iterator pointing at the first outgoing halfedge of v
const vertex_outgoing_halfedge_iterator halfedge_mesh::outgoing_halfedges_begin(const vertex_handle& v) const
{
	assert(is_completed());
	return vertex_outgoing_halfedge_iterator(this,v,false);
}
//returns an iterator pointing after the last outgoing halfedge of v
const vertex_outgoing_halfedge_iterator halfedge_mesh::outgoing_halfedges_end(const vertex_handle& v) const
{
	assert(is_completed());
	return vertex_outgoing_halfedge_iterator(this,v,true);
}

//returns an iterator pointing at the first incoming halfedge of v
const vertex_incoming_halfedge_iterator halfedge_mesh::incoming_halfedges_begin(const vertex_handle& v) const
{
	assert(is_completed());
	return vertex_incoming_halfedge_iterator(this,v,false);
}
//returns an iterator pointing after the last incoming halfedge of v 
const vertex_incoming_halfedge_iterator halfedge_mesh::incoming_halfedges_end(const vertex_handle& v) const
{
	assert(is_completed());
	return vertex_incoming_halfedge_iterator(this,v,true);
}

//returns an iterator pointing at the first one ring vertex of v 
const vertex_vertex_iterator halfedge_mesh::vertices_begin(const vertex_handle& v) const
{
	assert(is_completed());
	return vertex_vertex_iterator(this,v,false);
}
//returns an iterator pointing after the last one ring vertex of v 
const vertex_vertex_iterator halfedge_mesh::vertices_end(const vertex_handle& v) const
{
	assert(is_completed());
	return vertex_vertex_iterator(this,v,true);
}



void halfedge_mesh::clear()
{
	vertices.clear();
	edges.clear();
	faces.clear();
	halfedges.clear();
	completed = true;
}

vertex_handle halfedge_mesh::new_vertex()
{
	completed=false;
	vertices.push_back(vertex_data());
	return vertex_handle(vertices.size()-1);
}

std::vector<vertex_handle> halfedge_mesh::new_vertices(int n)
{
	
	std::vector<vertex_handle> vertex_handles(n);
		
	for(int i = 0; i < n; ++i)
		vertex_handles[i] = new_vertex();
	return vertex_handles;
}
	
face_handle halfedge_mesh::new_face()
{
	completed=false;
	face_data f;
	faces.push_back(f);
	return face_handle((int)faces.size()-1);
}

boundary_handle halfedge_mesh::new_boundary()
{
	boundary_data b;
	boundaries.push_back(b);
	return boundary_handle((int)boundaries.size()-1);
}


halfedge_handle halfedge_mesh::new_halfedge()
{
	halfedges.push_back(halfedge_data());
	return halfedge_handle(halfedges.size()-1);
}

edge_handle halfedge_mesh::new_edge()
{
	edges.push_back(edge_data());
	return edge_handle(edges.size()-1);
}

std::vector<halfedge_handle> halfedge_mesh::new_halfedges(int n)
{
	std::vector<halfedge_handle> halfedge_handles(n);
		
	for(int i = 0; i < n; ++i)
		halfedge_handles[i] = new_halfedge();
	return halfedge_handles;
}

face_handle halfedge_mesh::new_face(const std::vector<vertex_handle>& vertex_handles)
{
	face_handle f = new_face();
		
	std::vector<halfedge_handle> halfedge_handles = new_halfedges(vertex_handles.size());
	int n = (int)halfedge_handles.size();
	for(int i = 0; i < n; ++i)
	{
		halfedge_handle hi = halfedge_handles[i];
		halfedge_handle hi_next = halfedge_handles[(i+1)%n];
		vertex_handle vi = vertex_handles[i];
			
		halfedges[hi].next = hi_next;
		halfedges[hi_next].prev = hi;
		halfedges[hi].face = f;
		halfedges[hi].origin = vi;
			
		vertices[vi].halfedge = hi;
				
	}
		
	faces[f].halfedge = halfedge_handles[0];
	return f;
}


face_handle halfedge_mesh::new_triangle(const vertex_handle& v1, const vertex_handle& v2, const vertex_handle& v3)
{
	std::vector<vertex_handle> vertex_handles(3);
	vertex_handles[0] = v1;
	vertex_handles[1] = v2;
	vertex_handles[2] = v3;
	return new_face(vertex_handles);
}

face_handle halfedge_mesh::new_quad(const vertex_handle& v1, const vertex_handle& v2, const vertex_handle& v3, const vertex_handle& v4)
{
	std::vector<vertex_handle> vertex_handles(4);
	vertex_handles[0] = v1;
	vertex_handles[1] = v2;
	vertex_handles[2] = v3;
	vertex_handles[3] = v4;
	return new_face(vertex_handles);
}
	

boundary_handle& halfedge_mesh::boundary(const halfedge_handle& he) 
{
	return halfedges[he].boundary;
}

const boundary_handle& halfedge_mesh::boundary(const halfedge_handle& he) const
{
	return halfedges[he].boundary;
}

bool halfedge_mesh::is_boundary(const halfedge_handle& he) const
{
	return is_valid(boundary(he));
}
	
bool halfedge_mesh::is_boundary(const edge_handle& e) const
{
	halfedge_handle he = halfedge(e);
	return is_boundary(he)||is_boundary(inverse(he));
}

bool halfedge_mesh::is_boundary(const vertex_handle& v) const
{
	halfedge_handle he = halfedge(v);
	halfedge_handle he_end = halfedge(v);
	do
	{
		if(is_boundary(he))
			return true;
		he = next(inverse(he));
	}
	while(he != he_end);
		
	return false;
}

bool halfedge_mesh::is_valid(const vertex_handle& v) const
{
	return v >= 0 && v < num_vertices();
}

bool halfedge_mesh::is_valid(const face_handle& f) const
{
	return f >= 0 && f < num_faces();
}
	
bool halfedge_mesh::is_valid(const boundary_handle& b) const
{
	return b >= 0 && b < num_boundaries();
}

bool halfedge_mesh::is_valid(const edge_handle& e) const
{
	return e >= 0 && e < num_edges();
}

bool halfedge_mesh::is_valid(const halfedge_handle& he) const
{
	return he >= 0 && he < num_halfedges();
}

int halfedge_mesh::num_vertices() const
{
	return vertices.size();
}

int halfedge_mesh::num_halfedges() const
{
	return (int)halfedges.size();
}
	
int halfedge_mesh::num_faces() const
{
	return (int)faces.size();
}

int halfedge_mesh::num_boundaries() const
{
	return (int)boundaries.size();
}

int halfedge_mesh::num_edges() const
{
	return (int)edges.size();
}

void halfedge_mesh::complete(bool recompute_missing_normals,float max_angle_deg)
{
	int n = num_halfedges();
	std::vector<halfedge_handle> halfedge_handles(n);
	for(int i = 0; i < n; ++i)
		halfedge_handles[i] = i;

	//sort halfedge handles
	std::sort(halfedge_handles.begin(),halfedge_handles.end(),
		[&](const halfedge_handle& hi,const halfedge_handle& hj)->bool
	{
		auto vis = std::minmax(origin(hi),target(hi));
		auto vjs = std::minmax(origin(hj),target(hj));		
		return vis.second < vjs.second || ( (vis.second == vjs.second) && (vis.first < vjs.first)); 
	});
		
	//match inverse
	std::vector<halfedge_handle> boundary_halfedge_handles;
		
	int i = 0;
	while(true)
	{
		if(i == n)
			break;
		if(i+1 == n)
		{
			halfedge_handle he = halfedge_handles[i];
			halfedge_handle he_inv = new_halfedge();
			inverse(he) = he_inv;
			inverse(he_inv) = he;
			boundary_halfedge_handles.push_back(he_inv);
			break;
		}

		halfedge_handle he = halfedge_handles[i];
		halfedge_handle	he_inv = halfedge_handles[i+1];
		
		if( std::minmax(origin(he),target(he))  != std::minmax(origin(he_inv),target(he_inv)))
		{

			//create inverse
			he_inv = new_halfedge();
			inverse(he) = he_inv;
			inverse(he_inv) = he;
			boundary_halfedge_handles.push_back(he_inv);
			++i;
		}
		else
		{
			//match inverse
			inverse(he) = he_inv;
			inverse(he_inv) = he;
			i += 2;
		}
	}
	halfedge_handles.clear();

	//complete origin, next and prev of new inverse halfedges
	int nb = boundary_halfedge_handles.size();
		
	if(nb != 0)
	{

		for(int i=0; i < nb; ++i)
		{
			halfedge_handle he = boundary_halfedge_handles[i];
			origin(he) = target(inverse(he));

			halfedge_handle he_next = inverse(he);
			while(is_valid(face(he_next)))
				he_next = inverse(prev(he_next));

			next(he) = he_next;
			prev(he_next) = he;			
		}
	

		//create boundary loops
		for(int i =0; i < nb; ++i )
		{
			halfedge_handle he = boundary_halfedge_handles[i];
		
			if(is_valid(boundary(he)))
				continue;
			
			halfedge_handle h = he;
			boundary_handle b = new_boundary();
			halfedge(b) = he;
			while(boundary(h) == -1)
			{
				boundary(h) = b;
				h = next(h);
			}	
		}
	}

	//create edges
	edges.reserve(num_halfedges()*2);
	
	
	for(int i=0; i < n; ++i)
	{
		halfedge_handle he(i);
		if(!is_valid(edge(he)))
		{
			edge_handle e = new_edge();
			halfedge(e) = he;
			edge(he) = e;
			edge(inverse(he)) = e;
		}	
	}

	shrink_to_fit();
	completed = true;
	if(recompute_missing_normals)
	{
		if(faces.size() > 0 && faces[0].normal.length() == 0)
			compute_face_normals();
	
		if(vertices.size() > 0 && vertices[0].normal.length() == 0)	
			compute_vertex_normals();	
	
		if(halfedges.size() > 0 && halfedges[0].normal.length() == 0)
			compute_halfedge_normals(max_angle_deg);	
	}
}

void halfedge_mesh::compute_normals(float max_angle_deg)
{
	assert(is_completed());
	
	compute_face_normals();
	compute_vertex_normals();	
	compute_halfedge_normals(max_angle_deg);
	
}


void halfedge_mesh::print_statistics() const
{
	std::cout << "vertices: "<<num_vertices()<<std::endl;
	std::cout << "edges: "<<num_edges()<<std::endl;
	std::cout << "halfedges: "<<num_halfedges()<<std::endl;
	std::cout << "faces: "<<num_faces()<<std::endl;
	std::cout << "boundaries: "<<num_boundaries()<<std::endl;
}

void halfedge_mesh::shrink_to_fit()
{
	vertices.shrink_to_fit();
	faces.shrink_to_fit();
	halfedges.shrink_to_fit();
	edges.shrink_to_fit();
	boundaries.shrink_to_fit();
}


vec3 halfedge_mesh::compute_face_normal(const face_handle& f) const
{
	vec3 nml(0,0,0);
	face_halfedge_iterator hend = halfedges_end(f);
	for(face_halfedge_iterator hit=halfedges_begin(f);hit != hend; ++hit)
	{
		vec3 vn = position(origin(next(*hit)));
		vec3 v = position(origin(*hit));
		vec3 vp = position(origin(prev(*hit)));
		nml += cross(vn-v,vp-v);
	}
	nml.normalize();
	return nml;
}


vec3 halfedge_mesh::compute_vertex_normal(const vertex_handle& v) const
{
	vec3 nml(0,0,0);
	if(is_isolated(v))
		return nml;
	
	vertex_face_iterator fend = faces_end(v);
	for(vertex_face_iterator fit = faces_begin(v); fit != fend; ++fit)
	{
		if(is_valid(*fit))
			nml += compute_face_normal(*fit);
	}
	nml.normalize();
	return nml;
}



vec3 halfedge_mesh::compute_halfedge_normal(const halfedge_handle& hstart, float max_angle_deg) const
{
	
	vec3 nml(0,0,0); 
	
	halfedge_handle he = hstart;
	bool first=true;
	
	do{
		if(!is_valid(face(he)))
			break;
		nml += compute_face_normal(face(he));
		
		if(is_sharp(he,max_angle_deg))
			break;
		he = next(inverse(he));
		first = false;
	}while(he != hstart);

	if(first || he != hstart)
	{
		he = inverse(prev(hstart));
		do
		{
			if(!is_valid(face(he)))
				break;
			if(is_sharp(he,max_angle_deg))
				break;
			nml += compute_face_normal(face(he));
			
			he = inverse(prev(he));
		
		}while(he != hstart);

	}
	
	
		
	nml.normalize();
	return nml;
}


void halfedge_mesh::compute_face_normals()
{
	std::cout << "computing face normals...";
	
	face_iterator fend = faces_end();
	for(face_iterator fit = faces_begin(); fit != fend; ++fit)
		normal(*fit) = compute_face_normal(*fit);
	
	std::cout << "complete"<<std::endl;
}

void halfedge_mesh::compute_halfedge_normals(float max_angle_deg)
{
	
	std::cout << "computing halfedge normals...";
	
	halfedge_iterator hend = halfedges_end();
	for(halfedge_iterator hit = halfedges_begin(); hit != hend; ++hit)
		normal(*hit) = compute_halfedge_normal(*hit,max_angle_deg);
	
	std::cout << "complete"<<std::endl;
}

void halfedge_mesh::compute_vertex_normals()
{
	std::cout << "computing vertex normals...";
	
	vertex_iterator vend = vertices_end();
	for(vertex_iterator vit = vertices_begin(); vit != vend; ++vit)
		normal(*vit) = compute_vertex_normal(*vit);
	
	std::cout << "complete"<<std::endl;
}

void halfedge_mesh::flip_face_orientations()
{
	face_iterator fend = faces_end();
	for(face_iterator fit = faces_begin(); fit != fend; ++fit)
	{
		face_halfedge_iterator hend = halfedges_end(*fit);
		int n = valence(*fit);
		std::vector<halfedge_handle> hes(n);
		std::vector<vertex_handle> origs(n);
		std::vector<halfedge_handle> nexts(n);
		std::vector<halfedge_handle> prevs(n);
		std::vector<vec3> nmls(n);
		std::vector<vec2> texcoords(n);
		int i = 0;
		for(face_halfedge_iterator hit = halfedges_begin(*fit); hit != hend;++hit,++i)
		{
			hes[i] = *hit;
			prevs[i] = next(*hit);
			nexts[i] = prev(*hit);
			origs[i] = origin(prevs[i]);
			nmls[i] = normal(prevs[i]);
			texcoords[i] = texcoord(prevs[i]);
						
		}

		for(i = 0; i < n;++i)
		{
			halfedge_handle he = hes[i];
			prev(he) = prevs[i];
			next(he) = nexts[i];
			origin(he) = origs[i]; 
			halfedge(origin(he)) =he;
			normal(he) = nmls[i];
			texcoord(he) = texcoords[i];
					
		}

					
		
		normal(*fit) = -normal(*fit);
	}

	halfedge_iterator hend =halfedges_end();
	for(halfedge_iterator hit = halfedges_begin(); hit != hend; ++hit)
		normal(*hit) = -normal(*hit);
	
	vertex_iterator vend =vertices_end();
	for(vertex_iterator vit = vertices_begin(); vit != vend; ++vit)
		normal(*vit) = -normal(*vit);
	

}
	
//returns number of vertices adjacent vertices (one-ring)
int halfedge_mesh::valence(const vertex_handle& v) const
{
	halfedge_handle he = halfedge(v);
	halfedge_handle he_end=he;
	int count = 0;
	do
	{
		++count;
		he = next(inverse(he));
	}
	while(he != he_end);
	return count;
}

//returns number of vertices of face f
int halfedge_mesh::valence(const face_handle& f) const
{
	halfedge_handle he = halfedge(f);
	halfedge_handle he_end=he;
	int count = 0;
	do
	{
		++count;
		he = next(he);
	}
	while(he != he_end);
	return count;
}

int halfedge_mesh::valence(const boundary_handle& b) const
{
	halfedge_handle he = halfedge(b);
	halfedge_handle he_end=he;
	int count = 0;
	do
	{
		++count;
		he = next(he);
	}
	while(he != he_end);
	return count;
}

bool halfedge_mesh::is_triangle(const face_handle& f) const
{
	halfedge_handle he = halfedge(f);
	return next(next(next(he))) == he;
}

//returns true if f is a quadrangle
bool halfedge_mesh::is_quad(const face_handle& f) const
{
	halfedge_handle he = halfedge(f);
	return next(next(next(next(he)))) == he;
}


bool halfedge_mesh::is_triangle_mesh() const
{
	face_iterator fend = faces_end();
	for(face_iterator fit = faces_begin(); fit != fend; ++fit)
	{
		if(!is_triangle(*fit))
			return false;
	}
	return true;
}
	
bool halfedge_mesh::is_quad_mesh() const
{
	face_iterator fend = faces_end();
	for(face_iterator fit = faces_begin(); fit != fend; ++fit)
	{
		if(!is_quad(*fit))
			return false;
	}
	return true;
}

void halfedge_mesh::triangulate(const face_handle& f)
{ 
	bool comp = completed;
	halfedge_handle he = halfedge(f);
	halfedge_handle he_next = next(he);
	halfedge_handle he_next_next = next(he_next);
	vertex_handle v_start = origin(he);
		
	halfedge(f) = prev(he);

	while(target(he_next_next) != v_start)
	{
		halfedge_handle he_new = new_halfedge();
		halfedge_handle he_new_inv = new_halfedge();
			
		edge_handle e_new = new_edge();
		halfedge(e_new) = he_new;

		face_handle f_new = new_face();
		halfedge(f_new) = he_new;
			
		face(he_new) = f_new;
		face(he) = f_new;
		face(he_next) = f_new;	
		face(he_new_inv) = f;
			
		inverse(he_new) = he_new_inv;
		inverse(he_new_inv) = he_new;
		origin(he_new) = origin(he_next_next);
		origin(he_new_inv) = origin(he);
		next(he_new) = he;
		prev(he_new) = he_next;
		next(he_new_inv) = next(he_next);
		prev(he_new_inv) = prev(he);
	
		next(prev(he)) = he_new_inv;
		prev(he) = he_new;
		prev(he_next_next) = he_new_inv;
		next(he_next) = he_new;
			
		he = he_new_inv;
		he_next = he_next_next;
		he_next_next = next(he_next);
		

	}
	completed = comp;
}

bool halfedge_mesh::is_completed() const
{
	return completed;
}



vec3 halfedge_mesh::centroid(const halfedge_handle& he) const
{

	return (position(origin(he)) + position(target(he)) )/2.0f;
}

vec3 halfedge_mesh::centroid(const edge_handle& e) const
{
	return centroid(halfedge(e));
}

vec3 halfedge_mesh::centroid(const face_handle& f) const
{
	vec3 c(0,0,0);
	face_vertex_iterator vend = vertices_end(f);
	int n = 0;
	for(face_vertex_iterator vit = vertices_begin(f); vit != vend; ++vit)
	{
		c += position(*vit);
		n++;
	}
	c/=(float)n;
	return c;
}

vec3 halfedge_mesh::centroid(const vertex_handle& v) const
{
	vec3 c(0,0,0);
	vertex_vertex_iterator vend = vertices_end(v);
	int n = 0;
	for(vertex_vertex_iterator vit = vertices_begin(v); vit != vend; ++vit)
	{
		c += position(*vit);
		n++;
	}
	c/=(float)n;
	return c;
}



float halfedge_mesh::sector_angle_rad(const halfedge_handle& he) const
{
	vertex_handle v0 = origin(prev(he));
	vertex_handle v1 = origin(he);
	vertex_handle v2 = origin(next(he));

	vec3 d0 = position(v2)-position(v1);
	vec3 d1 = position(v0)-position(v1);
	float denom = d0.length()*d1.length();
	
	if(std::abs(denom) == 0)
		return 0;

	float cos_a = dot(d0,d1) / denom;
	cos_a=(std::max)(-1.0f,cos_a);
	cos_a=(std::min)(1.0f,cos_a);
	float sin_a = cross(d0,d1).length()/denom;
	sin_a=(std::max)(-1.0f,sin_a);
	sin_a=(std::min)(1.0f,sin_a);
	
	float a = atan2(sin_a,cos_a);
	if(a < 0)
		a += 2*3.14159265358979323846f; 
	return a;
}

//returns sector angle in degrees at origin of halfedge
float halfedge_mesh::sector_angle_deg(const halfedge_handle& he) const
{ 
	return sector_angle_rad(he)*180.0f/3.14159265358979323846f;
}

//returns the angle in radians between the normals of the two incident faces of edge e
//if edge is on border 0 is returned
float halfedge_mesh::dihedral_angle_rad(const halfedge_handle& he) const
{
	face_handle f1 = face(he);
	face_handle f2 = face(inverse(he));

	if(is_valid(f1) && is_valid(f2))
	{
		float d = dot(compute_face_normal(f1),compute_face_normal(f2));
		d = (std::max)(-1.0f,d);
		d = (std::min)(1.0f,d);
		return acos(d);
	}
	return 0;
}


//returns the angle in radians between the normals of the two incident faces of edge e
//if edge is on border 0 is returned
float halfedge_mesh::dihedral_angle_rad(const edge_handle& e) const
{
	return dihedral_angle_rad(halfedge(e));
}
	
//returns the angle in degrees between the normals of the two incident faces of edge e
//if edge is on border 0 is returned
float halfedge_mesh::dihedral_angle_deg(const edge_handle& e) const
{
	return dihedral_angle_deg(halfedge(e));
}

float halfedge_mesh::dihedral_angle_deg(const halfedge_handle& he) const
{
	return dihedral_angle_rad(he)*180.0f/3.14159265358979323846f;
}

bool halfedge_mesh::is_sharp(const edge_handle& e,float max_angle_deg) const
{
	return is_sharp(halfedge(e),max_angle_deg);
}
	
bool halfedge_mesh::is_sharp(const halfedge_handle& he,float max_angle_deg) const
{
	float angle = std::abs(dihedral_angle_deg(he));
	return angle >= max_angle_deg;
}


//triangulate mesh (assumes convex polygonal faces)
void halfedge_mesh::triangulate()
{
	face_iterator fend = faces_end();
	for(face_iterator fit = faces_begin(); fit != fend; ++fit)
		triangulate(*fit);
		
}

//returns the square length of halfedge he
float halfedge_mesh::sqr_length(const halfedge_handle& he) const
{
	vec3 p1 = position(origin(he));
	vec3 p2 = position(target(he));
	vec3 d = p1-p2;
	return d.sqr_length();
}

//return square length of edge e
float halfedge_mesh::sqr_length(const edge_handle& e) const
{
	return sqr_length(halfedge(e));
}

//returns length of halfedge he
float halfedge_mesh::length(const halfedge_handle& he) const
{
	return sqrt(sqr_length(he));
}

//return length of edge e
float halfedge_mesh::length(const edge_handle& e) const
{
	return length(halfedge(e));
}

//returns square length of boundary loop b
float halfedge_mesh::sqr_length(const boundary_handle& b) const
{
	float l = 0;
		
	boundary_halfedge_iterator hend = halfedges_end(b);
	for(boundary_halfedge_iterator hit = halfedges_begin(b); hit != hend; ++hit)
		l+=sqr_length(*hit);

	return l;	
}

//returns length of boundary loop b
float halfedge_mesh::length(const boundary_handle& b) const
{
	return sqrt(sqr_length(b));	
}

bool halfedge_mesh::is_closed() const
{
	return num_boundaries() == 0;
}


void halfedge_mesh::swap(const vertex_handle& v1, const vertex_handle& v2)
{
		
	assert(is_valid(v1) && is_valid(v2));
	if(v1 == v2)
		return;
		
	if(is_valid(halfedge(v1)))
	{
		assert(is_completed());
		vertex_outgoing_halfedge_iterator hend =  outgoing_halfedges_end(v1);
		for(vertex_outgoing_halfedge_iterator hit = outgoing_halfedges_begin(v1); hit != hend; ++hit)
			origin(*hit)=v2;
	}
	if(is_valid(halfedge(v2)))
	{
		assert(is_completed());
		vertex_outgoing_halfedge_iterator hend =  outgoing_halfedges_end(v2);
		for(vertex_outgoing_halfedge_iterator hit = outgoing_halfedges_begin(v2); hit != hend; ++hit)
			origin(*hit)=v1;
	}

	std::swap(vertices[v1],vertices[v2]);

}

void halfedge_mesh::swap(const edge_handle& e1, const edge_handle& e2)
{
	
	assert(is_valid(e1) && is_valid(e2));
	if(e1 == e2)
		return;
			
	halfedge_handle he1 = halfedge(e1);
	if(is_valid(he1))
	{
		edge(he1) = e2;
		if(is_valid(inverse(he1)))
			edge(inverse(he1)) = e2;
	}
	
	halfedge_handle he2 = halfedge(e2);
	if(is_valid(he2))
	{
		edge(he2) = e1;
		if(is_valid(inverse(he2)))
			edge(inverse(he2)) = e1;
	}

	std::swap(edges[e1],edges[e2]);
}

void halfedge_mesh::swap(const halfedge_handle& h1, const halfedge_handle& h2)
{
		
	assert(is_valid(h1) && is_valid(h2));
	if(h1 == h2)
		return;
	if(is_valid(origin(h1)))
		if(halfedge(origin(h1)) == h1)
			halfedge(origin(h1)) = h2;
	
	if(is_valid(origin(h2)))
		if(halfedge(origin(h2)) == h2)
			halfedge(origin(h2)) = h1;
		
	if(is_valid(face(h1)))
		if(halfedge(face(h1)) == h1)
			halfedge(face(h1)) = h2;
	if(is_valid(face(h2)))
		if(halfedge(face(h2)) == h2)
			halfedge(face(h2)) = h1;

	if(is_valid(edge(h1)))
		if(halfedge(edge(h1)) == h1)
			halfedge(edge(h1)) = h2;
	if(is_valid(edge(h2)))	
		if(halfedge(edge(h2)) == h2)
			halfedge(edge(h2)) = h1;
	
	if(is_valid(boundary(h1)))
		if(halfedge(boundary(h1)) == h1)
			halfedge(boundary(h1)) = h2;
		
	if(is_valid(boundary(h2)))
		if(halfedge(boundary(h2)) == h2)
			halfedge(boundary(h2)) = h1;
	if(is_valid(next(h1)))
		prev(next(h1)) = h2;
	if(is_valid(prev(h1)))
		next(prev(h1)) = h2;
	if(is_valid(inverse(h1)))
		inverse(inverse(h1))=h2; 
	if(is_valid(next(h2)))
		prev(next(h2)) = h1;
	if(is_valid(prev(h2)))
		next(prev(h2)) = h1;
	if(is_valid(inverse(h2)))
		inverse(inverse(h2))=h1; 

	std::swap(halfedges[h1],halfedges[h2]);
}

void halfedge_mesh::swap(const face_handle& f1, const face_handle& f2)
{
		
	assert(is_valid(f1) && is_valid(f2));
	if(f1 == f2)
		return;
	
		
	face_halfedge_iterator hend = halfedges_end(f1);
	for(face_halfedge_iterator hit = halfedges_begin(f1); hit != hend; ++hit)
		face(*hit)=f2;

	hend = halfedges_end(f2);
	for(face_halfedge_iterator hit = halfedges_begin(f2); hit != hend; ++hit)
		face(*hit)=f1;
	
	std::swap(faces[f1],faces[f2]);
}

void halfedge_mesh::swap(const boundary_handle& b1, const boundary_handle& b2)
{
		
	assert(is_valid(b1) && is_valid(b2));
	if(b1 == b2)
		return;
		
	boundary_halfedge_iterator hend = halfedges_end(b1);
	for(boundary_halfedge_iterator hit = halfedges_begin(b1); hit != hend; ++hit)
		boundary(*hit)=b2;

	hend = halfedges_end(b2);
	for(boundary_halfedge_iterator hit = halfedges_begin(b2); hit != hend; ++hit)
		boundary(*hit)=b1;

	std::swap(boundaries[b1],boundaries[b2]);

}

bool halfedge_mesh::is_isolated(const vertex_handle& v) const
{
	return !is_valid(halfedge(v));
}

bool halfedge_mesh::has_isolated_vertices() const
{
	vertex_iterator vend = vertices_end();
	for(vertex_iterator vit = vertices_begin();vit != vend; ++vit)
		if(is_isolated(*vit))
			return true;
	return false;
}

void halfedge_mesh::remove_isolated_vertices()
{
	
	for(vertex_iterator vit = vertices_begin();vit != vertices_end();)
	{
		if(is_isolated(*vit))
		{
			vertex_iterator vlast = vertices_end();
			--vlast;
			if(vit != vlast)
				swap(*vit,*vlast);
			vertices.pop_back();
		}
		else
			++vit;
	}
}



