//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh.h"



face_iterator::face_iterator(const halfedge_mesh* mesh_ptr,const face_handle h):mesh_ptr(mesh_ptr),h(h){}
	

face_iterator::face_iterator() : mesh_ptr(nullptr){}

face_iterator& face_iterator::operator++()
{
	h++;
	return *this;
}

face_iterator& face_iterator::operator--()
{
	h--;
	return *this;
}
	
face_iterator face_iterator::operator++(int) 
{
	face_iterator tmp=*this;
	++*this;
	return tmp;
}
    
face_iterator face_iterator::operator--(int)
{
	face_iterator tmp=*this;
	--*this;
	return tmp;
}

bool face_iterator::operator==(const face_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h);
}
			
bool face_iterator::operator!=(const face_iterator& it) const
{
	return !(*this == it);
}

const face_handle face_iterator::operator*() const{ return h;}





vertex_iterator::vertex_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle h):mesh_ptr(mesh_ptr),h(h){}
	

vertex_iterator::vertex_iterator() : mesh_ptr(nullptr){}

vertex_iterator& vertex_iterator::operator++()
{
	h++;
	return *this;
}

vertex_iterator& vertex_iterator::operator--()
{
	h--;
	return *this;
}
	
vertex_iterator vertex_iterator::operator++(int) 
{
	vertex_iterator tmp=*this;
	++*this;
	return tmp;
}
    
vertex_iterator vertex_iterator::operator--(int)
{
	vertex_iterator tmp=*this;
	--*this;
	return tmp;
}

bool vertex_iterator::operator==(const vertex_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h);
}
			
bool vertex_iterator::operator!=(const vertex_iterator& it) const
{
	return !(*this == it);
}

const vertex_handle vertex_iterator::operator*() const{ return h;}



edge_iterator::edge_iterator(const halfedge_mesh* mesh_ptr,const edge_handle h):mesh_ptr(mesh_ptr),h(h){}
	

edge_iterator::edge_iterator() : mesh_ptr(nullptr){}

edge_iterator& edge_iterator::operator++()
{
	h++;
	return *this;
}

edge_iterator& edge_iterator::operator--()
{
	h--;
	return *this;
}
	
edge_iterator edge_iterator::operator++(int) 
{
	edge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
edge_iterator edge_iterator::operator--(int)
{
	edge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool edge_iterator::operator==(const edge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h);
}
			
bool edge_iterator::operator!=(const edge_iterator& it) const
{
	return !(*this == it);
}

const edge_handle edge_iterator::operator*() const
{
	return h;
}




halfedge_iterator::halfedge_iterator(const halfedge_mesh* mesh_ptr,const halfedge_handle h):mesh_ptr(mesh_ptr),h(h){}
	

halfedge_iterator::halfedge_iterator() : mesh_ptr(nullptr){}

halfedge_iterator& halfedge_iterator::operator++()
{
	h++;
	return *this;
}

halfedge_iterator& halfedge_iterator::operator--()
{
	h--;
	return *this;
}
	
halfedge_iterator halfedge_iterator::operator++(int) 
{
	halfedge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
halfedge_iterator halfedge_iterator::operator--(int)
{
	halfedge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool halfedge_iterator::operator==(const halfedge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h);
}
			
bool halfedge_iterator::operator!=(const halfedge_iterator& it) const
{
	return !(*this == it);
}

const halfedge_handle halfedge_iterator::operator*() const{ return h;}


boundary_iterator::boundary_iterator(const halfedge_mesh* mesh_ptr,const boundary_handle h):mesh_ptr(mesh_ptr),h(h){}
	
boundary_iterator::boundary_iterator() : mesh_ptr(nullptr){}

boundary_iterator& boundary_iterator::operator++()
{
	h++;
	return *this;
}

boundary_iterator& boundary_iterator::operator--()
{
	h--;
	return *this;
}
	
boundary_iterator boundary_iterator::operator++(int) 
{
	boundary_iterator tmp=*this;
	++*this;
	return tmp;
}
    
boundary_iterator boundary_iterator::operator--(int)
{
	boundary_iterator tmp=*this;
	--*this;
	return tmp;
}

bool boundary_iterator::operator==(const boundary_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h);
}
			
bool boundary_iterator::operator!=(const boundary_iterator& it) const
{
	return !(*this == it);
}

const boundary_handle boundary_iterator::operator*() const{ return h;}

face_halfedge_iterator::face_halfedge_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(f);
}
	

face_halfedge_iterator& face_halfedge_iterator::operator++()
{
	h=mesh_ptr->next(h);
	active=true;
	return *this;
}

face_halfedge_iterator& face_halfedge_iterator::operator--()
{
	h=mesh_ptr->prev(h);
	active=true;
	return *this;
}
	
face_halfedge_iterator face_halfedge_iterator::operator++(int) 
{
	face_halfedge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
face_halfedge_iterator face_halfedge_iterator::operator--(int)
{
	face_halfedge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool face_halfedge_iterator::operator==(const face_halfedge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool face_halfedge_iterator::operator!=(const face_halfedge_iterator& it) const
{
	return !(*this == it);
}

const halfedge_handle face_halfedge_iterator::operator*() const 
{ 
	return h;
}




face_outer_halfedge_iterator::face_outer_halfedge_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(f);
}
	

face_outer_halfedge_iterator& face_outer_halfedge_iterator::operator++()
{
	h=mesh_ptr->prev(h);
	active=true;
	return *this;
}

face_outer_halfedge_iterator& face_outer_halfedge_iterator::operator--()
{
	h=mesh_ptr->next(h);
	active=true;
	return *this;
}
	
face_outer_halfedge_iterator face_outer_halfedge_iterator::operator++(int) 
{
	face_outer_halfedge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
face_outer_halfedge_iterator face_outer_halfedge_iterator::operator--(int)
{
	face_outer_halfedge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool face_outer_halfedge_iterator::operator==(const face_outer_halfedge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool face_outer_halfedge_iterator::operator!=(const face_outer_halfedge_iterator& it) const
{
	return !(*this == it);
}

const halfedge_handle face_outer_halfedge_iterator::operator*() const 
{ 
	return mesh_ptr->inverse(h);
}






face_face_iterator::face_face_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(f);
}
	

face_face_iterator& face_face_iterator::operator++()
{
	h=mesh_ptr->prev(h);
	active=true;
	return *this;
}

face_face_iterator& face_face_iterator::operator--()
{
	h=mesh_ptr->next(h);
	active=true;
	return *this;
}
	
face_face_iterator face_face_iterator::operator++(int) 
{
	face_face_iterator tmp=*this;
	++*this;
	return tmp;
}
    
face_face_iterator face_face_iterator::operator--(int)
{
	face_face_iterator tmp=*this;
	--*this;
	return tmp;
}

bool face_face_iterator::operator==(const face_face_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool face_face_iterator::operator!=(const face_face_iterator& it) const
{
	return !(*this == it);
}

const face_handle face_face_iterator::operator*() const 
{ 
	return mesh_ptr->face(mesh_ptr->inverse(h));
}







face_edge_iterator::face_edge_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(f);
}
	

face_edge_iterator::face_edge_iterator() : mesh_ptr(nullptr),active(false){}

face_edge_iterator& face_edge_iterator::operator++()
{
	h=mesh_ptr->next(h);
	active=true;
	return *this;
}

face_edge_iterator& face_edge_iterator::operator--()
{
	h=mesh_ptr->prev(h);
	active=true;
	return *this;
}
	
face_edge_iterator face_edge_iterator::operator++(int) 
{
	face_edge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
face_edge_iterator face_edge_iterator::operator--(int)
{
	face_edge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool face_edge_iterator::operator==(const face_edge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool face_edge_iterator::operator!=(const face_edge_iterator& it) const
{
	return !(*this == it);
}

const edge_handle face_edge_iterator::operator*() const 
{ 
	return mesh_ptr->edge(h);
}


face_vertex_iterator::face_vertex_iterator(const halfedge_mesh* mesh_ptr,const face_handle f,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(f);
}
	
face_vertex_iterator::face_vertex_iterator() : mesh_ptr(nullptr),active(false){}

face_vertex_iterator& face_vertex_iterator::operator++()
{
	h=mesh_ptr->next(h);
	active=true;
	return *this;
}

face_vertex_iterator& face_vertex_iterator::operator--()
{
	h=mesh_ptr->prev(h);
	active=true;
	return *this;
}
	
face_vertex_iterator face_vertex_iterator::operator++(int) 
{
	face_vertex_iterator tmp=*this;
	++*this;
	return tmp;
}
    
face_vertex_iterator face_vertex_iterator::operator--(int)
{
	face_vertex_iterator tmp=*this;
	--*this;
	return tmp;
}

bool face_vertex_iterator::operator==(const face_vertex_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool face_vertex_iterator::operator!=(const face_vertex_iterator& it) const
{
	return !(*this == it);
}

const vertex_handle face_vertex_iterator::operator*() const 
{ 
	return mesh_ptr->origin(h);
}




boundary_halfedge_iterator::boundary_halfedge_iterator(const halfedge_mesh* mesh_ptr,const boundary_handle f,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(f);
}
	

boundary_halfedge_iterator& boundary_halfedge_iterator::operator++()
{
	h=mesh_ptr->next(h);
	active=true;
	return *this;
}

boundary_halfedge_iterator& boundary_halfedge_iterator::operator--()
{
	h=mesh_ptr->prev(h);
	active=true;
	return *this;
}
	
boundary_halfedge_iterator boundary_halfedge_iterator::operator++(int) 
{
	boundary_halfedge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
boundary_halfedge_iterator boundary_halfedge_iterator::operator--(int)
{
	boundary_halfedge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool boundary_halfedge_iterator::operator==(const boundary_halfedge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool boundary_halfedge_iterator::operator!=(const boundary_halfedge_iterator& it) const
{
	return !(*this == it);
}

const halfedge_handle boundary_halfedge_iterator::operator*() const 
{ 
	return h;
}



boundary_edge_iterator::boundary_edge_iterator(const halfedge_mesh* mesh_ptr,const boundary_handle f,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(f);
}
	

boundary_edge_iterator::boundary_edge_iterator() : mesh_ptr(nullptr),active(false){}

boundary_edge_iterator& boundary_edge_iterator::operator++()
{
	h=mesh_ptr->next(h);
	active=true;
	return *this;
}

boundary_edge_iterator& boundary_edge_iterator::operator--()
{
	h=mesh_ptr->prev(h);
	active=true;
	return *this;
}
	
boundary_edge_iterator boundary_edge_iterator::operator++(int) 
{
	boundary_edge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
boundary_edge_iterator boundary_edge_iterator::operator--(int)
{
	boundary_edge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool boundary_edge_iterator::operator==(const boundary_edge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool boundary_edge_iterator::operator!=(const boundary_edge_iterator& it) const
{
	return !(*this == it);
}

const edge_handle boundary_edge_iterator::operator*() const 
{ 
	return mesh_ptr->edge(h);
}


boundary_vertex_iterator::boundary_vertex_iterator(const halfedge_mesh* mesh_ptr,const boundary_handle f,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(f);
}
	
boundary_vertex_iterator::boundary_vertex_iterator() : mesh_ptr(nullptr),active(false){}

boundary_vertex_iterator& boundary_vertex_iterator::operator++()
{
	h=mesh_ptr->next(h);
	active=true;
	return *this;
}

boundary_vertex_iterator& boundary_vertex_iterator::operator--()
{
	h=mesh_ptr->prev(h);
	active=true;
	return *this;
}
	
boundary_vertex_iterator boundary_vertex_iterator::operator++(int) 
{
	boundary_vertex_iterator tmp=*this;
	++*this;
	return tmp;
}
    
boundary_vertex_iterator boundary_vertex_iterator::operator--(int)
{
	boundary_vertex_iterator tmp=*this;
	--*this;
	return tmp;
}

bool boundary_vertex_iterator::operator==(const boundary_vertex_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool boundary_vertex_iterator::operator!=(const boundary_vertex_iterator& it) const
{
	return !(*this == it);
}

const vertex_handle boundary_vertex_iterator::operator*() const 
{ 
	return mesh_ptr->origin(h);
}







vertex_outgoing_halfedge_iterator::vertex_outgoing_halfedge_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle v,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(v);
}
	
vertex_outgoing_halfedge_iterator::vertex_outgoing_halfedge_iterator() : mesh_ptr(nullptr),active(false){}

vertex_outgoing_halfedge_iterator& vertex_outgoing_halfedge_iterator::operator++()
{
	h=mesh_ptr->inverse(mesh_ptr->prev(h));
	active=true;
	return *this;
}

vertex_outgoing_halfedge_iterator& vertex_outgoing_halfedge_iterator::operator--()
{
	h=mesh_ptr->next(mesh_ptr->inverse(h));
	active=true;
	return *this;
}
	
vertex_outgoing_halfedge_iterator vertex_outgoing_halfedge_iterator::operator++(int) 
{
	vertex_outgoing_halfedge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
vertex_outgoing_halfedge_iterator vertex_outgoing_halfedge_iterator::operator--(int)
{
	vertex_outgoing_halfedge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool vertex_outgoing_halfedge_iterator::operator==(const vertex_outgoing_halfedge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool vertex_outgoing_halfedge_iterator::operator!=(const vertex_outgoing_halfedge_iterator& it) const
{
	return !(*this == it);
}

const halfedge_handle vertex_outgoing_halfedge_iterator::operator*() const 
{ 
	return h;
}







vertex_incoming_halfedge_iterator::vertex_incoming_halfedge_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle v,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->inverse(mesh_ptr->halfedge(v));
}
	
vertex_incoming_halfedge_iterator::vertex_incoming_halfedge_iterator() : mesh_ptr(nullptr),active(false){}

vertex_incoming_halfedge_iterator& vertex_incoming_halfedge_iterator::operator++()
{
	h=mesh_ptr->prev(mesh_ptr->inverse(h));
	active=true;
	return *this;
}

vertex_incoming_halfedge_iterator& vertex_incoming_halfedge_iterator::operator--()
{
	h=mesh_ptr->inverse(mesh_ptr->next(h));
	active=true;
	return *this;
}
	
vertex_incoming_halfedge_iterator vertex_incoming_halfedge_iterator::operator++(int) 
{
	vertex_incoming_halfedge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
vertex_incoming_halfedge_iterator vertex_incoming_halfedge_iterator::operator--(int)
{
	vertex_incoming_halfedge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool vertex_incoming_halfedge_iterator::operator==(const vertex_incoming_halfedge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool vertex_incoming_halfedge_iterator::operator!=(const vertex_incoming_halfedge_iterator& it) const
{
	return !(*this == it);
}

const halfedge_handle vertex_incoming_halfedge_iterator::operator*() const 
{ 
	return h;
}











vertex_face_iterator::vertex_face_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle v,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(v);
}
	
vertex_face_iterator::vertex_face_iterator() : mesh_ptr(nullptr),active(false){}

vertex_face_iterator& vertex_face_iterator::operator++()
{
	h=mesh_ptr->inverse(mesh_ptr->prev(h));
	active=true;
	return *this;
}

vertex_face_iterator& vertex_face_iterator::operator--()
{
	h=mesh_ptr->next(mesh_ptr->inverse(h));
	active=true;
	return *this;
}
	
vertex_face_iterator vertex_face_iterator::operator++(int) 
{
	vertex_face_iterator tmp=*this;
	++*this;
	return tmp;
}
    
vertex_face_iterator vertex_face_iterator::operator--(int)
{
	vertex_face_iterator tmp=*this;
	--*this;
	return tmp;
}

bool vertex_face_iterator::operator==(const vertex_face_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool vertex_face_iterator::operator!=(const vertex_face_iterator& it) const
{
	return !(*this == it);
}

const face_handle vertex_face_iterator::operator*() const 
{ 
	return mesh_ptr->face(h);
}
















vertex_vertex_iterator::vertex_vertex_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle v,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->inverse(mesh_ptr->halfedge(v));
}
	
vertex_vertex_iterator::vertex_vertex_iterator() : mesh_ptr(nullptr),active(false){}

vertex_vertex_iterator& vertex_vertex_iterator::operator++()
{
	h=mesh_ptr->prev(mesh_ptr->inverse(h));
	active=true;
	return *this;
}

vertex_vertex_iterator& vertex_vertex_iterator::operator--()
{
	h=mesh_ptr->inverse(mesh_ptr->next(h));
	active=true;
	return *this;
}
	
vertex_vertex_iterator vertex_vertex_iterator::operator++(int) 
{
	vertex_vertex_iterator tmp=*this;
	++*this;
	return tmp;
}
    
vertex_vertex_iterator vertex_vertex_iterator::operator--(int)
{
	vertex_vertex_iterator tmp=*this;
	--*this;
	return tmp;
}

bool vertex_vertex_iterator::operator==(const vertex_vertex_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool vertex_vertex_iterator::operator!=(const vertex_vertex_iterator& it) const
{
	return !(*this == it);
}

const vertex_handle vertex_vertex_iterator::operator*() const 
{ 
	return mesh_ptr->origin(h);
}





vertex_edge_iterator::vertex_edge_iterator(const halfedge_mesh* mesh_ptr,const vertex_handle v,bool active):mesh_ptr(mesh_ptr),active(active)
{
	h = mesh_ptr->halfedge(v);
}
	
vertex_edge_iterator::vertex_edge_iterator() : mesh_ptr(nullptr),active(false){}

vertex_edge_iterator& vertex_edge_iterator::operator++()
{
	h=mesh_ptr->inverse(mesh_ptr->prev(h));
	active=true;
	return *this;
}

vertex_edge_iterator& vertex_edge_iterator::operator--()
{
	h=mesh_ptr->next(mesh_ptr->inverse(h));
	active=true;
	return *this;
}
	
vertex_edge_iterator vertex_edge_iterator::operator++(int) 
{
	vertex_edge_iterator tmp=*this;
	++*this;
	return tmp;
}
    
vertex_edge_iterator vertex_edge_iterator::operator--(int)
{
	vertex_edge_iterator tmp=*this;
	--*this;
	return tmp;
}

bool vertex_edge_iterator::operator==(const vertex_edge_iterator& it) const
{
	return (mesh_ptr == it.mesh_ptr) && (h == it.h) &&(active == it.active);
}
			
bool vertex_edge_iterator::operator!=(const vertex_edge_iterator& it) const
{
	return !(*this == it);
}

const edge_handle vertex_edge_iterator::operator*() const 
{ 
	return mesh_ptr->edge(h);
}







