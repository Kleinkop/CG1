//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once

// makro to define a typesafe integer handle
// with DEFINE_HANDLE_TYPE(handle) a new type called handle is created
// which behaves mostly like an int.
//
// Here are a few problems which cannot be solved with simple typedefs:

// typedef int halfedge_handle;
// typedef int edge_handle;
// edge_handle e;
// halfedge_handle h;
// ...
// e = h; //not type safe
//
//class halfedge_mesh
//{
//	bool is_boundary(const edge_handle& e);
//	bool is_boundary(const vertex_handle& v); // not possible because two methods with equal signature
//...
//};




#define DEFINE_HANDLE_TYPE(HANDLE_TYPE)												\
struct HANDLE_TYPE																	\
{																					\
	HANDLE_TYPE():id(-1){};															\
	HANDLE_TYPE(const HANDLE_TYPE & h) : id(h.id){}									\
	HANDLE_TYPE & operator=(const HANDLE_TYPE & rhs) { id = rhs.id; return *this;}	\
	operator const int & () const {return id; }										\
    operator int & () { return id; }												\
    bool operator==(const HANDLE_TYPE & rhs) const { return id == rhs.id; }			\
    bool operator<(const HANDLE_TYPE & rhs) const { return id < rhs.id; }			\
private:																			\
	friend class halfedge_mesh;														\
	int id;																			\
	explicit HANDLE_TYPE(const int id) : id(id) {};									\
	HANDLE_TYPE & operator=(const int & rhs) { id = rhs; return *this;}				\
};																					\
																					\
namespace std																		\
{																					\
	template<>																		\
	class hash<HANDLE_TYPE>															\
	{																				\
	public:																			\
		size_t operator()(const HANDLE_TYPE& _Keyval) const							\
		{																			\
			return (hash<int>()((int)_Keyval));										\
		}																			\
	};																				\
};																					


DEFINE_HANDLE_TYPE(halfedge_handle)
DEFINE_HANDLE_TYPE(face_handle)
DEFINE_HANDLE_TYPE(boundary_handle)
DEFINE_HANDLE_TYPE(edge_handle)
DEFINE_HANDLE_TYPE(vertex_handle)


