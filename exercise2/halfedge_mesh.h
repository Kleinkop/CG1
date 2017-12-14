//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once

#include <vector>
#include <stack>
#include <random>
#include "halfedge_mesh_handles.h"
#include "halfedge_mesh_iterators.h"


#include <cgv/math/fvec.h>
//a 3d vector
typedef cgv::math::fvec<float, 3> vec3;
//a 2d vector
typedef cgv::math::fvec<float, 3> vec2;




class halfedge_mesh 
{
	

public:	
	struct halfedge_data
	{
		//origin vertex of halfedge
		vertex_handle origin;
		//next halfedge in boundary/face loop
		halfedge_handle next;
		//prev halfedge in boundary/face loop
		halfedge_handle prev;
		//opposite halfedge 
		halfedge_handle inverse;
		//handle to incident face or -1 if incident to boundary 
		face_handle face;
		//handle to boundary loop or -1 if incident to face
		boundary_handle boundary;
		//handle to incident edge handle
		edge_handle edge;
		
		//2d texcoord of origin vertex (assosiated within incident face of halfedge)
		vec2 texcoord;
		//normal of origin vertex (assosiated within incident face of halfedge)
		vec3 normal;
		//default constructor
		halfedge_data():origin(-1),next(-1),prev(-1),inverse(-1),face(-1),boundary(-1),edge(-1),normal(0,0,0),texcoord(0,0){}
	};

	struct vertex_data
	{
		//a halfedge handle to an outgoing halfedge
		halfedge_handle halfedge;
		//vertex position
		vec3 position;
		//vertex color
		vec3 color;
		//vertex normal
		vec3 normal;
		//default constructor
		vertex_data():halfedge(-1),position(0,0,0),color(1,1,1),normal(0,0,0){}
	};

	struct face_data
	{
		//an inner halfedge of face
		halfedge_handle halfedge;
		//face normal
		vec3 normal;
		//face color
		vec3 color;
		//default constructor
		face_data():halfedge(-1),color(1.0f,1.0f,1.0f),normal(0,0,0){}	
	};

	struct boundary_data
	{
		//a halfedge incident with boundary
		halfedge_handle halfedge;
		//default constructor
		boundary_data():halfedge(-1){}	
	};

	
	struct edge_data
	{
		//a halfedge incident with edge
		halfedge_handle halfedge;	
		//default constructor
		edge_data():halfedge(-1){}	
	};

	


private:
	///////////////////////////////////////////////////////////////
	//// INTERNAL DATA OF HALFEDGE MESH
	///////////////////////////////////////////////////////////////


	//internal vector of all vertices
	std::vector<vertex_data> vertices;
	//internal vector of all halfedges
	std::vector<halfedge_data> halfedges;
	//internal vector of all polygonal faces
	std::vector<face_data> faces;
	//internal vector of all boundary loops
	std::vector<boundary_data> boundaries;
	//internal vector of all edges
	std::vector<edge_data> edges;
	//internal flag indicating if halfedge mesh is completed (see method void complete() )
	bool completed;

	//adds a new face f to the vector of all faces and returns face handle of f
	face_handle new_face();
	//adds a new boundary loop b to the vector of all boundaries and returns a boundary handle of b
	boundary_handle new_boundary();
	//adds a new halfedge h to the vector of all halfedges and returns a halfedge handle of h 
	halfedge_handle new_halfedge();
	//adds a new edge e to the vector of all edges and returns an edge handle of h 
	edge_handle new_edge();
	//adds n new halfedges and returns a vector of halfedge handles
	std::vector<halfedge_handle> new_halfedges(int n);

	void swap(const vertex_handle& v1, const vertex_handle& v2);

	void swap(const edge_handle& e1, const edge_handle& e2);

	void swap(const halfedge_handle& h1, const halfedge_handle& h2);

	void swap(const face_handle& f1, const face_handle& f2);

	void swap(const boundary_handle& b1, const boundary_handle& b2);
	
	
	
public:
	
	//default constructor creates empty mesh
	halfedge_mesh();

	////////////////////////////////////////////////////////////////
	//	READ/WRITE ACCESSORS TO INTERNAL MESH PROPERTIES
	////////////////////////////////////////////////////////////////

	//returns a reference to the positions of vertex v
	vec3& position(const vertex_handle& v);
	//returns a const reference to the positions of vertex v
	const vec3& position(const vertex_handle& v) const;

	//returns a reference to the color of vertex v
	vec3& color(const vertex_handle& v);
	//returns a const reference to the color of vertex v
	const vec3& color(const vertex_handle& v) const;

	//returns a reference to the normal of vertex v
	vec3& normal(const vertex_handle& v);
	//returns a const reference to the normal of vertex v
	const vec3& normal(const vertex_handle& v) const;

	//returns a reference to the normal of halfedge he (assosiated with vertex origin(he))
	vec3& normal(const halfedge_handle& h);
	//returns a const reference to the normal of halfedge he (assosiated with vertex origin(he))
	const vec3& normal(const halfedge_handle& h) const;

	//returns a reference to the normal of face f
	vec3& normal(const face_handle& f);
	//returns a const reference to the normal of face f
	const vec3& normal(const face_handle& f) const;

	//returns a reference to the color of face f
	vec3& color(const face_handle& f);
	//returns a const reference to the color of face f
	const vec3& color(const face_handle& f) const;

	//returns a reference to the 2d texcoord of halfedge he (assosiated with vertex origin(he))
	vec2& texcoord(const halfedge_handle& h);
	//returns a const reference to the 2d texcoord of halfedge he (assosiated with vertex origin(he))
	const vec2& texcoord(const halfedge_handle& h) const;

	//////////////////////////////////////////////////////////////////
	//	READ/WRITE ACCESSORS TO INTERNAL MESH CONNECTIVITY PROPERTIES
	//////////////////////////////////////////////////////////////////

	//returns a reference to the next halfedge of halfedge h
	halfedge_handle& next(const halfedge_handle& h);
	//returns a const reference to the next halfedge of halfedge h
	const halfedge_handle& next(const halfedge_handle& h) const;

	//returns a reference to the prev halfedge of halfedge h
	halfedge_handle& prev(const halfedge_handle& h);
	//returns a const reference to the prev halfedge of halfedge h
	const halfedge_handle& prev(const halfedge_handle& h) const;
	
	//returns a reference to the inverse halfedge of halfedge h
	halfedge_handle& inverse(const halfedge_handle& h);
	//returns a const reference to the inverse halfedge of halfedge h
	const halfedge_handle& inverse(const halfedge_handle& h) const;

	//returns a reference to the origin vertex of halfedge h
	vertex_handle& origin(const halfedge_handle& h);
	//returns a const reference to the origin vertex of halfedge h
	const vertex_handle& origin(const halfedge_handle& h) const;
	
	//returns a reference to the target of halfedge h (which internally is the origin of next(h))	
	vertex_handle& target(const halfedge_handle& h);
	//returns a const reference to the target vertex of halfedge h (which internally is the origin of next(h))
	const vertex_handle& target(const halfedge_handle& h)  const;
	
	//returns a reference to the target vertex of halfedge h (which internally is the origin of halfedge(e))
	vertex_handle& origin(const edge_handle& e);
	//returns a const reference to the target of halfedge h (which internally is the origin of halfedge(e))
	const vertex_handle& origin(const edge_handle& e) const;
	
	//returns a reference to the target vertex of edge e (which internally is the target of halfedge(e))
	vertex_handle& target(const edge_handle& e);
	//returns a const reference to the target vertex of edge e (which internally is the target of halfedge(e))
	const vertex_handle& target(const edge_handle& e)  const;
	
	//returns a reference to the incident face of halfedge h	
	face_handle& face(const halfedge_handle& h);
	//returns a const reference to the incident face of halfedge h
	const face_handle& face(const halfedge_handle& h) const;
	
	//returns a reference to the incident edge of halfedge h
	edge_handle& edge(const halfedge_handle& h);
	//returns a const reference to the incident edge of halfedge h
	const edge_handle& edge(const halfedge_handle& h) const;
	
	//returns a reference to an outgoing halfedge of vertex v
	halfedge_handle& halfedge(const vertex_handle& v);
	//returns a const reference to an outgoing halfedge of vertex v
	const halfedge_handle& halfedge(const vertex_handle& v) const;

	//returns a reference to an inner halfedge of face f 
	halfedge_handle& halfedge(const face_handle& f);	
	//returns a const reference to an inner halfedge of face f 
	const halfedge_handle& halfedge(const face_handle& f) const;

	//returns a reference to a halfedge of boundary loop b 
	halfedge_handle& halfedge(const boundary_handle& b);	
	//returns a const reference to a halfedge of boundary loop b 
	const halfedge_handle& halfedge(const boundary_handle& b) const;

	//returns a reference to an incident halfedge of edge e
	halfedge_handle& halfedge(const edge_handle& e);
	//returns a const reference to an incident halfedge of edge e 
	const halfedge_handle& halfedge(const edge_handle& e) const;

	//returns a reference to a boundary of halfedge h
	boundary_handle& boundary(const halfedge_handle& h);
	//returns a const reference to a boundary of halfedge h
	const boundary_handle& boundary(const halfedge_handle& h) const;


	////////////////////////////////////////////////////////////////
	//	ACCESSORS TO MESH ITERATORS
	////////////////////////////////////////////////////////////////


	//returns an iterator pointing at the first vertex of the mesh 
	const vertex_iterator vertices_begin() const;
	//returns an iterator pointing after the last vertex of the mesh 
	const vertex_iterator vertices_end() const;

	//returns an iterator pointing at the first face of the mesh 
	const vertex_face_iterator faces_begin(const vertex_handle& v) const;
	//returns an iterator pointing after the last face of the mesh 
	const vertex_face_iterator faces_end(const vertex_handle& v) const;

	//returns an iterator pointing at the halfedge of the mesh 
	const halfedge_iterator halfedges_begin() const;
	//returns an iterator pointing after the last halfedge of the mesh 
	const halfedge_iterator halfedges_end() const;

	//returns an iterator pointing at the first edge of the mesh 
	const edge_iterator edges_begin() const;
	//returns an iterator pointing after the last edge of the mesh 
	const edge_iterator edges_end() const;

	//returns an iterator pointing at the first face of the mesh 
	const face_iterator faces_begin() const;
	//returns an iterator pointing after the last face of the mesh 
	const face_iterator faces_end() const;
	
	//returns an iterator pointing at the first boundary loop of the mesh 
	const boundary_iterator boundaries_begin() const;
	//returns an iterator pointing after the last boundary loop of the mesh 
	const boundary_iterator boundaries_end() const;
	
	//returns an iterator pointing at the first vertex of face f 
	const face_vertex_iterator vertices_begin(const face_handle& f) const;
	//returns an iterator pointing after the last vertex of face f 
	const face_vertex_iterator vertices_end(const face_handle& f) const;
	
	//returns an iterator pointing at the first (inner) halfedge of face f 
	const face_halfedge_iterator halfedges_begin(const face_handle& f) const;
	//returns an iterator pointing after the last (inner) halfedge of face f
	const face_halfedge_iterator halfedges_end(const face_handle& f) const;
	

	//returns an iterator pointing at the first outer halfedge of face f 
	const face_outer_halfedge_iterator outer_halfedges_begin(const face_handle& f) const;
	//returns an iterator pointing after the last outer halfedge of face f 
	const face_outer_halfedge_iterator outer_halfedges_end(const face_handle& f) const;

	//returns an iterator pointing at the first edge-adjacent face of face f 
	const face_face_iterator faces_begin(const face_handle& f) const;
	//returns an iterator pointing after the last edge-adjacent face of face f 
	const face_face_iterator faces_end(const face_handle& f) const;

	//returns an iterator pointing at the first edge of the face f 
	const face_edge_iterator edges_begin(const face_handle& f) const;
	//returns an iterator pointing after the last edge of the face f 
	const face_edge_iterator edges_end(const face_handle& f) const;

	//returns an iterator pointing at the first vertex of the boundary loop b
	const boundary_vertex_iterator vertices_begin(const boundary_handle& b) const;
	//returns an iterator pointing after the last vertex of the boundary loop b
	const boundary_vertex_iterator vertices_end(const boundary_handle& b) const;

	//returns an iterator pointing at the first halfedge of the boundary loop b
	const boundary_halfedge_iterator halfedges_begin(const boundary_handle& b) const;
	//returns an iterator pointing after thr last halfedge of the boundary loop b
	const boundary_halfedge_iterator halfedges_end(const boundary_handle& b) const;

	//returns an iterator pointing at the first edge of the boundary loop b
	const boundary_edge_iterator edges_begin(const boundary_handle& b) const;
	//returns an iterator pointing after the last edge of the boundary loop b
	const boundary_edge_iterator edges_end(const boundary_handle& b) const;

	//returns an iterator pointing at the first outgoing halfedge of v
	const vertex_outgoing_halfedge_iterator outgoing_halfedges_begin(const vertex_handle& v) const;
	//returns an iterator pointing after the last outgoing halfedge of v
	const vertex_outgoing_halfedge_iterator outgoing_halfedges_end(const vertex_handle& v) const;

	//returns an iterator pointing at the first incoming halfedge of v
	const vertex_incoming_halfedge_iterator incoming_halfedges_begin(const vertex_handle& v) const;
	//returns an iterator pointing after the last incoming halfedge of v 
	const vertex_incoming_halfedge_iterator incoming_halfedges_end(const vertex_handle& v) const;

	//returns an iterator pointing at the first one ring vertex of v 
	const vertex_vertex_iterator vertices_begin(const vertex_handle& v) const;
	//returns an iterator pointing after the last one ring vertex of v 
	const vertex_vertex_iterator vertices_end(const vertex_handle& v) const;


	//remove all vertices, edges, halfedges, faces and boundaries from mesh
	void clear();

	// return a vertex handle of a newly created vertex 
	vertex_handle new_vertex();

	//return a std:vector of n vertex handles of  newly created vertices 
	std::vector<vertex_handle> new_vertices(int n);
	
	//add a new face defined by the given vertex handles
	face_handle new_face(const std::vector<vertex_handle>& vertex_handles);

	//add a new triangle and return face handle
	face_handle new_triangle(const vertex_handle& v1, const vertex_handle& v2, const vertex_handle& v3);
	
	//add a new triangle and return face handle
	face_handle new_quad(const vertex_handle& v1, const vertex_handle& v2, const vertex_handle& v3, const vertex_handle& v4);
	
	//returns true if halfedge he belong to a boundary loop
	bool is_boundary(const halfedge_handle& h) const;
	
	//returns true if edge e is on a surface boundary
	bool is_boundary(const edge_handle& e) const;

	//returns true if vertex v is on a surface boundary
	bool is_boundary(const vertex_handle& v) const;

	//returns true if v is a valid vertex handle
	bool is_valid(const vertex_handle& v) const;

	//returns true if f is a valid face handle
	bool is_valid(const face_handle& f) const;
	
	//returns true if b is a valid boundary handle
	bool is_valid(const boundary_handle& b) const;
	
	//returns true if e is a valid edge handle
	bool is_valid(const edge_handle& e) const;
	
	//returns true if he is a valid halfedge handle
	bool is_valid(const halfedge_handle& he) const;

	
	//return number of vertices
	int num_vertices() const;

	//return number of halfedges
	int num_halfedges() const;
	
	//return number of faces
	int num_faces() const;

	//return number of boundary loops (assumes mesh is completed)
	int num_boundaries() const;
	
	//return number of edges (assumes mesh is completed)
	int num_edges() const;
	
	//the mesh is considered complete if all internal handles are completed
	//each halfedge has a valid inverse
	//each halfedge has an edge
	//each halfedge which is on a boundary loop has valid next, prev and boundary handles
	
	void complete(bool recompute_missing_normals=true,float max_angle_deg=45);

	//returns true if mesh is completed
	bool is_completed() const;
	
	//shrink all internal vectors containing vertex-, face-, halfedge- ,edge- and boundary data to save memory
	void shrink_to_fit();

	//print number of vertices, faces, edges, halfedges and boundaries 
	void print_statistics() const;
	
	//returns a computed face normal of face f by using vertex position information
	vec3 compute_face_normal(const face_handle& f) const;
	
	//returns a vertex normal by averaging adjacent face normals
	vec3 compute_vertex_normal(const vertex_handle& v) const;
	
	//returns a  normal for the origin vertex of the halfedge similar to compute_vertex_normal 
	//but respecting sharp edges
	//edges are classified as sharp by thresholding the angle between adjacent face normals
	vec3 compute_halfedge_normal(const halfedge_handle& h, float max_angle_deg) const;
	
	//compute face normals for each face
	void compute_face_normals();

	//compute average normal for each vertex
	void compute_vertex_normals();

	//compute halfedge normals for each halfedge respecting sharp edges 
	//an edge is considered as sharp if the absolute angle between normals of its two adjacent faces is larger than max_angle_deg 
	void compute_halfedge_normals(float max_angle_deg=45);

	//compute face-, vertex- and halfedge normals
	void compute_normals(float max_angle_deg=45);

	//inverts the orientation of all halfedges to turn face orientation around
	//all normals are flipped
	void flip_face_orientations();
	
	//returns number of one-ring vertices
	int valence(const vertex_handle& v) const;
	
	//returns number of vertices of face f
	int valence(const face_handle& f) const;
	
	//returns number of vertices of boundary loop b
	int valence(const boundary_handle& b) const;

	//returns true if f is a triangle
	bool is_triangle(const face_handle& f) const;

	//returns true if f is a quadrangle
	bool is_quad(const face_handle& f) const;
	
	//returns true if all faces are triangles
	bool is_triangle_mesh() const;
	
	//returns true if all faces are quadrangles
	bool is_quad_mesh() const;
	
	//triangulate face f (assumes convex polygonal faces)
	void triangulate(const face_handle& f);

	//triangulate mesh (assumes convex polygonal faces)
	void triangulate();

	//returns the square length of halfedge he
	float sqr_length(const halfedge_handle& h) const;

	//return square length of edge e
	float sqr_length(const edge_handle& e) const;

	//returns length of halfedge he
	float length(const halfedge_handle& he) const;

	//return length of edge e
	float length(const edge_handle& e) const;

	//returns square length of boundary loop b
	float sqr_length(const boundary_handle& b) const;

	//returns length of boundary loop b
	float length(const boundary_handle& b) const;

	//returns sector angle in radians at origin of halfedge
	float sector_angle_rad(const halfedge_handle& he) const;

	//returns sector angle in degrees at origin of halfedge
	float sector_angle_deg(const halfedge_handle& he) const;

	//returns the angle in radians between the normals of the two incident faces of edge e
	//if edge is on border 0 is returned
	float dihedral_angle_rad(const halfedge_handle& e) const;
	
	//returns the angle in degrees between the normals of the two incident faces of edge e
	//if edge is on border 0 is returned
	float dihedral_angle_deg(const halfedge_handle& e) const;

	//returns the angle in radians between the normals of the two incident faces of edge e
	//if edge is on border 0 is returned
	float dihedral_angle_rad(const edge_handle& e) const;
	
	//returns the angle in degrees between the normals of the two incident faces of edge e
	//if edge is on border 0 is returned
	float dihedral_angle_deg(const edge_handle& e) const;

	//returns true if the absolute value of the dihedral angle of edge e is larger than max_angle_deg
	bool is_sharp(const edge_handle& e,float max_angle_deg=45) const;
	
	//returns true if the absolute value of the dihedral angle of halfedge he is larger than max_angle_deg
	bool is_sharp(const halfedge_handle& he,float max_angle_deg=45) const;

	//returns point in the middle of halfedge he
	vec3 centroid(const halfedge_handle& he) const;
	
	//returns point in the middle of edge e
	vec3 centroid(const edge_handle& e) const;

	//returns mean point of face vertex positions of face f
	vec3 centroid(const face_handle& f) const;

	//returns mean point of one ring vertex positions
	vec3 centroid(const vertex_handle& v) const;

	//returns true if surface of mesh is closed (has no boundaries)
	bool is_closed() const;

	//returns true if vertex is isolated (does not belong to face)
	bool is_isolated(const vertex_handle& v) const;

	//returns true if mesh contains vertices which have no outgoing halfedges 
	bool has_isolated_vertices() const;

	//remove isolated vertices from mesh
	void remove_isolated_vertices();

	
};
