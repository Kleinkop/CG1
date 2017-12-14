//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"

class halfedge_mesh;

struct face_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	face_handle h;

	face_iterator(const halfedge_mesh* mesh_ptr,const face_handle h);
	
public:
	face_iterator();

	face_iterator& operator++();

	face_iterator& operator--();
	
	face_iterator operator++(int);
    
	face_iterator operator--(int);

	bool operator==(const face_iterator& it) const;
			
    bool operator!=(const face_iterator& it) const;

	const face_handle operator*() const;

};

struct vertex_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	vertex_handle h;

	vertex_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle h);
	
public:
	vertex_iterator();

	vertex_iterator& operator++();

	vertex_iterator& operator--();
	
	vertex_iterator operator++(int);
    
	vertex_iterator operator--(int);

	bool operator==(const vertex_iterator& it) const;
			
    bool operator!=(const vertex_iterator& it) const;

	const vertex_handle operator*() const;

};

struct edge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	edge_handle h;

	edge_iterator(const halfedge_mesh* mesh_ptr,const edge_handle h);
	
public:
	edge_iterator();

	edge_iterator& operator++();

	edge_iterator& operator--();
	
	edge_iterator operator++(int);
    
	edge_iterator operator--(int);

	bool operator==(const edge_iterator& it) const;
			
    bool operator!=(const edge_iterator& it) const;

	const edge_handle operator*() const;

};

struct halfedge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	halfedge_iterator(const halfedge_mesh* mesh_ptr,const halfedge_handle h);
	
public:
	halfedge_iterator();

	halfedge_iterator& operator++();

	halfedge_iterator& operator--();
	
	halfedge_iterator operator++(int);
    
	halfedge_iterator operator--(int);

	bool operator==(const halfedge_iterator& it) const;
				
    bool operator!=(const halfedge_iterator& it) const;
		
	const halfedge_handle operator*() const;

};
	
struct boundary_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	boundary_handle h;

	boundary_iterator(const halfedge_mesh* mesh_ptr,const boundary_handle h);
	
public:
	boundary_iterator();

	boundary_iterator& operator++();

	boundary_iterator& operator--();
	
	boundary_iterator operator++(int);
    
	boundary_iterator operator--(int);

	bool operator==(const boundary_iterator& it) const;
			
    bool operator!=(const boundary_iterator& it) const;
		
	const boundary_handle operator*() const;

};

struct face_halfedge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	face_halfedge_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active);
	
public:
	face_halfedge_iterator() ;

	face_halfedge_iterator& operator++();
		
	face_halfedge_iterator& operator--();
		
	face_halfedge_iterator operator++(int);
	    
	face_halfedge_iterator operator--(int);
		
	bool operator==(const face_halfedge_iterator& it) const;
					
    bool operator!=(const face_halfedge_iterator& it) const;

	const halfedge_handle operator*() const;
	
};

struct face_outer_halfedge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	face_outer_halfedge_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active);
	
public:
	face_outer_halfedge_iterator() ;

	face_outer_halfedge_iterator& operator++();
		
	face_outer_halfedge_iterator& operator--();
		
	face_outer_halfedge_iterator operator++(int);
	    
	face_outer_halfedge_iterator operator--(int);
		
	bool operator==(const face_outer_halfedge_iterator& it) const;
					
    bool operator!=(const face_outer_halfedge_iterator& it) const;

	const halfedge_handle operator*() const;
	

};

struct face_face_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	face_face_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active);
	
public:
	face_face_iterator();

	face_face_iterator& operator++();
		
	face_face_iterator& operator--();
		
	face_face_iterator operator++(int);
	    
	face_face_iterator operator--(int);
		
	bool operator==(const face_face_iterator& it) const;
					
    bool operator!=(const face_face_iterator& it) const;

	const face_handle operator*() const;
	

};

struct face_edge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	face_edge_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active);
	
public:
	face_edge_iterator();

	face_edge_iterator& operator++();
		
	face_edge_iterator& operator--();
	
	face_edge_iterator operator++(int);		
    
	face_edge_iterator operator--(int);

	bool operator==(const face_edge_iterator& it) const;
			
    bool operator!=(const face_edge_iterator& it) const;
		
	const edge_handle operator*() const;
	

};

struct face_vertex_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	face_vertex_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active);
	
public:
	face_vertex_iterator();

	face_vertex_iterator& operator++();
	
	face_vertex_iterator& operator--();
	
	face_vertex_iterator operator++(int);
    
	face_vertex_iterator operator--(int);

	bool operator==(const face_vertex_iterator& it) const;
			
    bool operator!=(const face_vertex_iterator& it) const;

	const vertex_handle operator*() const;

};

struct boundary_halfedge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	boundary_halfedge_iterator(const halfedge_mesh* mesh_ptr,const boundary_handle f,bool active);
	
public:
	boundary_halfedge_iterator() ;

	boundary_halfedge_iterator& operator++();
		
	boundary_halfedge_iterator& operator--();
		
	boundary_halfedge_iterator operator++(int);
	    
	boundary_halfedge_iterator operator--(int);
		
	bool operator==(const boundary_halfedge_iterator& it) const;
					
    bool operator!=(const boundary_halfedge_iterator& it) const;

	const halfedge_handle operator*() const;
	

};

struct boundary_edge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	boundary_edge_iterator(const halfedge_mesh* mesh_ptr,const boundary_handle f,bool active);
	
public:
	boundary_edge_iterator();

	boundary_edge_iterator& operator++();
		
	boundary_edge_iterator& operator--();
	
	boundary_edge_iterator operator++(int);		
    
	boundary_edge_iterator operator--(int);

	bool operator==(const boundary_edge_iterator& it) const;
			
    bool operator!=(const boundary_edge_iterator& it) const;
		
	const edge_handle operator*() const;
	

};

struct boundary_vertex_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	boundary_vertex_iterator(const halfedge_mesh* mesh_ptr,const boundary_handle h,bool active);
	
public:
	boundary_vertex_iterator();

	boundary_vertex_iterator& operator++();
	
	boundary_vertex_iterator& operator--();
	
	boundary_vertex_iterator operator++(int);
    
	boundary_vertex_iterator operator--(int);

	bool operator==(const boundary_vertex_iterator& it) const;
			
    bool operator!=(const boundary_vertex_iterator& it) const;

	const vertex_handle operator*() const;

};

struct vertex_outgoing_halfedge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	vertex_outgoing_halfedge_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle v,bool active);
	
public:
	vertex_outgoing_halfedge_iterator();

	vertex_outgoing_halfedge_iterator& operator++();
	
	vertex_outgoing_halfedge_iterator& operator--();
	
	vertex_outgoing_halfedge_iterator operator++(int);
    
	vertex_outgoing_halfedge_iterator operator--(int);

	bool operator==(const vertex_outgoing_halfedge_iterator& it) const;
			
    bool operator!=(const vertex_outgoing_halfedge_iterator& it) const;

	const halfedge_handle operator*() const;

};

struct vertex_incoming_halfedge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	vertex_incoming_halfedge_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle h,bool active);
	
public:
	vertex_incoming_halfedge_iterator();

	vertex_incoming_halfedge_iterator& operator++();
	
	vertex_incoming_halfedge_iterator& operator--();
	
	vertex_incoming_halfedge_iterator operator++(int);
    
	vertex_incoming_halfedge_iterator operator--(int);

	bool operator==(const vertex_incoming_halfedge_iterator& it) const;
			
    bool operator!=(const vertex_incoming_halfedge_iterator& it) const;

	const halfedge_handle operator*() const;

};

struct vertex_face_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	vertex_face_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle v,bool active);
	
public:
	vertex_face_iterator();

	vertex_face_iterator& operator++();
	
	vertex_face_iterator& operator--();
	
	vertex_face_iterator operator++(int);
    
	vertex_face_iterator operator--(int);

	bool operator==(const vertex_face_iterator& it) const;
			
    bool operator!=(const vertex_face_iterator& it) const;

	const face_handle operator*() const;

};

struct vertex_vertex_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	vertex_vertex_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle v,bool active);
	
public:
	vertex_vertex_iterator();

	vertex_vertex_iterator& operator++();
	
	vertex_vertex_iterator& operator--();
	
	vertex_vertex_iterator operator++(int);
    
	vertex_vertex_iterator operator--(int);

	bool operator==(const vertex_vertex_iterator& it) const;
			
    bool operator!=(const vertex_vertex_iterator& it) const;

	const vertex_handle operator*() const;

};

struct vertex_edge_iterator
{
private:

	friend class halfedge_mesh;

	const halfedge_mesh* mesh_ptr;
	
	halfedge_handle h;

	bool active;

	vertex_edge_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle h,bool active);
	
public:
	vertex_edge_iterator();

	vertex_edge_iterator& operator++();
	
	vertex_edge_iterator& operator--();
	
	vertex_edge_iterator operator++(int);
    
	vertex_edge_iterator operator--(int);

	bool operator==(const vertex_edge_iterator& it) const;
			
    bool operator!=(const vertex_edge_iterator& it) const;

	const edge_handle operator*() const;

};



