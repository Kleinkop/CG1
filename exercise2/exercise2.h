//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include <cgv/gui/provider.h>
#include <cgv/render/drawable.h>
#include <cgv_gl/gl/gl.h>

#include "halfedge_mesh.h"
#include "halfedge_mesh_primitives.h"
#include "halfedge_mesh_stripification.h"

using namespace cgv::base;
using namespace cgv::signal;
using namespace cgv::gui;
using namespace cgv::math;
using namespace cgv::render;
using namespace cgv::utils;

class exercise2 : public node, 
				  public drawable, 
				  public provider
{	
	bool render_solid;

	bool render_strips;

	bool render_wireframe;
	
	enum Shape { QUAD, CUBE, TETRAHEDRON, DISK, CYLINDER, SPHERE, TORUS, ICOSAEDER, OCTAEDER,ARROW} shp;

	float max_angle;

	int n_trials;

	float lambda;

	int n_iters;

	bool normal_dir;

	float sigma;

	bool colorize_strips;

	bool colorize_shells;

	bool auto_recompute_normals;

	enum normal_mode {FACE_NORMAL_MODE,VERTEX_NORMAL_MODE,HALFEDGE_NORMAL_MODE} nml_mode;
	
	enum color_mode {FACE_COLOR_MODE,VERTEX_COLOR_MODE} clr_mode;

	halfedge_mesh polymesh;

	std::vector<std::vector<vertex_handle>> strips;
public:
	// The constructor of this class
	exercise2();
	// Show information in the main window
	void stream_stats(std::ostream& os);
	// Create the gui elements
	void create_gui();
	// Method that is called whenever a gui element changes
	void on_set(void* member_ptr);

	void create_dual_mesh();

	void load_mesh();
	
	void store_mesh();

	void create_primitive();
	
	void triangulate_mesh();

	void extract_strips();

	void recompute_normals();


	void flip_face_orientations();

	void extract_shells();

	void compute_surface_area();

	void compute_volume();

	void add_noise();

	void smooth_mesh_laplacian();

	void smooth_mesh_laplacian_beltrami();

	
	// Draw the scene
	void draw(context& c);

	void render_solid_mesh();

	void render_wireframe_mesh();

	void render_boundary_loops();

	void render_triangle_strips();

};

