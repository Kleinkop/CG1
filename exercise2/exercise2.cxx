//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "exercise2.h"
#include "halfedge_mesh_area.h"
#include "halfedge_mesh_volume.h"
#include "halfedge_mesh_stripification.h"
#include "halfedge_mesh_io.h"
#include "halfedge_mesh_shell_extraction.h"
#include "halfedge_mesh_noise.h"
#include "halfedge_mesh_smoothing.h"
#include "halfedge_mesh_dual_mesh.h"
#include <cgv/utils/ostream_printf.h>
#include <cgv/gui/file_dialog.h>

using namespace cgv::utils;

// The constructor of this class
exercise2::exercise2():node("Exercise 2") 
{
	render_solid = true;
	render_wireframe = false;
	render_strips = true;
	n_trials = 20;
	n_iters = 10;
	lambda = 0.3f;
	sigma = 0.01f;
	colorize_strips = true;
	colorize_shells = true;
	auto_recompute_normals = true;
	shp = QUAD;
	clr_mode = FACE_COLOR_MODE;
	nml_mode = HALFEDGE_NORMAL_MODE;

	normal_dir=true;
	
	max_angle = 45;
	polymesh = create_tetrahedron();
	recompute_normals();
	polymesh.print_statistics();
}



// Method that is called whenever a gui element changes
void exercise2::on_set(void* member_ptr)
{
	post_redraw();
}



// Create the gui elements
void exercise2::create_gui() {

	// Mesh creation functions
	add_decorator("mesh creation", "heading");
		connect_copy(add_button("load obj from file ")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::load_mesh));
		connect_copy(add_button("store mesh to obj  ")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::store_mesh));
		add_member_control(this, "primitive", shp, "dropdown",
			"enums='QUAD,CUBE,TETRAHEDRON,DISK,CYLINDER,SPHERE,TORUS,ICOSAEDER,OCTAEDER,ARROW'");

		connect_copy(add_button("create primitive")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::create_primitive));
		connect_copy(add_button("triangulate")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::triangulate_mesh));
		connect_copy(add_button("flip face orientations")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::flip_face_orientations));
		connect_copy(add_button("recompute normals")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::recompute_normals));

		connect_copy(add_button("create dual mesh")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::create_dual_mesh));


	// Mesh noising functions
	add_decorator("mesh noise", "heading");
		add_member_control(this, "restrict to normal dir", normal_dir, "check");
		add_member_control(this, "sigma", sigma, "value_slider", "min=0;max=0.1;ticks=false");
		connect_copy(add_button("add noise")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::add_noise));

	// Mesh smoothing functions
	add_decorator("mesh smoothing", "heading");
		add_member_control(this, "lambda",lambda, "value_slider", "min=0;max=1;ticks=false");
		add_member_control(this, "n iterations", n_iters, "value_slider", "min=1;max=100;ticks=false");
		add_member_control(this, "auto recompute normals", auto_recompute_normals, "check");

		connect_copy(add_button("smooth uniform laplacian")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::smooth_mesh_laplacian));
		connect_copy(add_button("smooth lapacian beltrami")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::smooth_mesh_laplacian_beltrami));

	// Mesh stripification functions
	add_decorator("mesh stripification", "heading");
		add_member_control(this, "n_trials", n_trials, "value_slider", 
			"min=1;max=100;ticks=false");
		add_member_control(this, "colorize strips", colorize_strips,"check");
		connect_copy(add_button("extract strips")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::extract_strips));

	// Mesh shell extraction functions
	add_decorator("mesh shell extraction", "heading");
		add_member_control(this, "colorize shells", colorize_shells,"check");
		connect_copy(add_button("extract shells")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::extract_shells));

	// Functions for mesh computations	
	add_decorator("mesh computations", "heading"); 
		connect_copy(add_button("compute surface area")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::compute_surface_area));
		connect_copy(add_button("compute volume")->click,
			rebind(static_cast<exercise2*>(this), &exercise2::compute_volume));

	// Functions for mesh rendering
	add_decorator("mesh rendering options", "heading");
		add_member_control(this, "normal mode", nml_mode, "dropdown",
			"enums='FACE_NORMAL_MODE,VERTEX_NORMAL_MODE,HALFEDGE_NORMAL_MODE'");
		add_member_control(this, "color mode", clr_mode, "dropdown",
			"enums='FACE_COLOR_MODE,VERTEX_COLOR_MODE'");
		add_member_control(this, "render wireframe", render_wireframe, "check");
		add_member_control(this, "render solid", render_solid, "check");
		add_member_control(this, "render strips", render_strips, "check");

		add_member_control(this, "min sharp angle", max_angle, "value_slider", 
			"min=0;max=180;ticks=false");	 
}

void exercise2::create_primitive()
{
	
	switch (shp) {
	case QUAD: polymesh = create_quad(); break;
	case CUBE: polymesh = create_cube(); break;
	case TETRAHEDRON: polymesh = create_tetrahedron(); break;
	case DISK: polymesh = create_disk(1,20); break;
	case CYLINDER: polymesh = create_cylinder(0.3f,1,20,10); break;
	case SPHERE:polymesh = create_sphere(1,20,20); break;
	case TORUS: polymesh = create_torus(0.4f,1,20,20); break;
	case ICOSAEDER: polymesh = create_icosaeder(1); break;
	case OCTAEDER: polymesh = create_octaeder(1); break;
	case ARROW: polymesh = create_unit_arrow(); break;
	default:
			std::cerr << "unknown shape" << std::endl;
	}
	recompute_normals();
	strips.clear();
	polymesh.print_statistics();
	post_redraw();

}

void exercise2::load_mesh()
{
	 std::string filename = cgv::gui::file_open_dialog("Load OBJ-Mesh...", "(*.obj)");
	 if(filename !="")
	 {
		 strips.clear();
		 load_obj(polymesh,filename);
		 polymesh.print_statistics();
		 
	 }
	 post_redraw();
}

void exercise2::store_mesh()
{
	std::string filename = cgv::gui::file_save_dialog("Load OBJ-Mesh...", "(*.obj)");
	 if(filename !="")
	 {
		 store_obj(polymesh,filename);		 
	 }
	 post_redraw();
}


void exercise2::create_dual_mesh()
{
	polymesh = ::create_dual_mesh(polymesh);
	recompute_normals();
	
	strips.clear();
	 post_redraw();
}


void exercise2::triangulate_mesh()
{
	if(!polymesh.is_triangle_mesh())
	{
		polymesh.triangulate();
		recompute_normals();
	}
	post_redraw();
}

void exercise2::flip_face_orientations()
{
	
	polymesh.flip_face_orientations();
	post_redraw();
	
}

void exercise2::compute_surface_area()
{
	
	std::cout << "surface area:" <<::compute_surface_area(polymesh)<<std::endl;
	post_redraw();
	
}

void exercise2::compute_volume()
{
	
	if(!polymesh.is_closed())
	{
		std::cout << "error in volume computation: mesh is not closed"<<std::endl;
		return;
	}

	if(!polymesh.is_triangle_mesh())
		triangulate_mesh();
		
	std::cout << "volume:" <<::compute_volume(polymesh)<<std::endl;
	post_redraw();
	
}


void exercise2::extract_shells()
{
	
	auto shells = ::extract_shells(polymesh,colorize_shells);
	this->update();
	std::cout <<"number of shells: "<< shells.size()<<std::endl; 
	std::cout << "real number of shells:" << ::count_shells(polymesh) << std::endl;
	post_redraw();
}


void exercise2::add_noise()
{
	if(normal_dir)
		add_noise_to_vertex_positions_in_normal_direction(polymesh,sigma);
	else
		add_noise_to_vertex_positions(polymesh,sigma);
	if(auto_recompute_normals)
		recompute_normals();
	
	post_redraw();
}

void exercise2::smooth_mesh_laplacian()
{
	smooth_vertex_positions_laplacian(polymesh,lambda,n_iters);
	if(auto_recompute_normals)
		recompute_normals();
	
	post_redraw();
}

void exercise2::smooth_mesh_laplacian_beltrami()
{
	smooth_vertex_positions_laplacian_beltrami(polymesh,lambda,n_iters);
	if(auto_recompute_normals)
		recompute_normals();
	
	post_redraw();
}

void exercise2::recompute_normals()
{
	
	polymesh.compute_face_normals();
	polymesh.compute_vertex_normals();
	polymesh.compute_halfedge_normals(max_angle);
	
	post_redraw();
}

void exercise2::extract_strips()
{
	
	if(!polymesh.is_triangle_mesh())
		triangulate_mesh();
	strips = ::extract_strips(polymesh,n_trials,colorize_strips);
	std::cout << "number of strips: " <<strips.size()<<std::endl;
	post_redraw();
}



// Draw the scene
void exercise2::draw(context& c) 
{
	if(render_solid)
		render_solid_mesh();
	if(render_wireframe)
		render_wireframe_mesh();
	if(render_strips)
		render_triangle_strips();
	
}


void exercise2::render_triangle_strips()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glColor3f(1,1,1);
	for(int i =0; i < (int)strips.size(); ++i)
	{
		std::vector<vertex_handle> vertex_handles = strips[i];
		auto vend = vertex_handles.end();
		
		glBegin(GL_TRIANGLE_STRIP);
		for(auto vit = vertex_handles.begin(); vit != vend; ++vit)
		{
			glNormal3fv(polymesh.normal(*vit));
			glVertex3fv(polymesh.position(*vit));
		}
		glEnd();
	}
}

void  exercise2::render_solid_mesh() 
{
	
	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	switch(nml_mode)
	{
	case FACE_NORMAL_MODE:
		{
		face_iterator fend = polymesh.faces_end();
		for(face_iterator fit = polymesh.faces_begin(); fit!= fend; ++fit)
		{
			glBegin(GL_POLYGON);
			if(nml_mode == FACE_NORMAL_MODE)
				glNormal3fv(polymesh.normal(*fit));
			if(clr_mode == FACE_COLOR_MODE)
				glColor3fv(polymesh.color(*fit));

			face_halfedge_iterator hend = polymesh.halfedges_end(*fit);
			for(face_halfedge_iterator hit = polymesh.halfedges_begin(*fit); hit != hend; ++hit)
			{
			//	glTexCoord2fv(polymesh.texcoord(*hit));
			//	glNormal3fv(polymesh.normal(*hit));
				if(clr_mode == VERTEX_COLOR_MODE)
					glColor3fv(polymesh.color(polymesh.origin(*hit)));
				glVertex3fv(polymesh.position(polymesh.origin(*hit)));
			
			}
			glEnd();
		}
		break;
		}
	case VERTEX_NORMAL_MODE:
		{
			face_iterator fend = polymesh.faces_end();
			for(face_iterator fit = polymesh.faces_begin(); fit!= fend; ++fit)
			{
				glBegin(GL_POLYGON);
				glColor3fv(polymesh.color(*fit));
				if(clr_mode == FACE_COLOR_MODE)
					glColor3fv(polymesh.color(*fit));

				face_vertex_iterator vend = polymesh.vertices_end(*fit);
				for(face_vertex_iterator vit = polymesh.vertices_begin(*fit); vit != vend; ++vit)
				{
					if(clr_mode == VERTEX_COLOR_MODE)
						glColor3fv(polymesh.color(*vit));
					glNormal3fv(polymesh.normal(*vit));
					glVertex3fv(polymesh.position(*vit));
				}
				glEnd();
			}
			break;
		}
	case HALFEDGE_NORMAL_MODE:
	default:
		{
			face_iterator fend = polymesh.faces_end();
			for(face_iterator fit = polymesh.faces_begin(); fit!= fend; ++fit)
			{
				glBegin(GL_POLYGON);
				if(clr_mode == FACE_COLOR_MODE)
					glColor3fv(polymesh.color(*fit));

				face_halfedge_iterator hend = polymesh.halfedges_end(*fit);
				for(face_halfedge_iterator hit = polymesh.halfedges_begin(*fit); hit != hend; ++hit)
				{
				
					glNormal3fv(polymesh.normal(*hit));
					if(clr_mode == VERTEX_COLOR_MODE)
						glColor3fv(polymesh.color(polymesh.origin(*hit)));
					glVertex3fv(polymesh.position(polymesh.origin(*hit)));
				}
				glEnd();
			}
			break;
		}

	}
}

void  exercise2::render_wireframe_mesh() 
{
	
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glLineWidth(1);
	glEnable(GL_LINE_SMOOTH);

	edge_iterator eend = polymesh.edges_end();
	glBegin(GL_LINES);
	for(edge_iterator eit = polymesh.edges_begin(); eit!= eend; ++eit)
	{	
		if(polymesh.is_boundary(*eit))
			glColor3f(1,0,0);
		else
			glColor3f(0,1,0);
		if(polymesh.is_sharp(*eit,max_angle))
			glColor3f(0,0,1);
		glVertex3fv(polymesh.position(polymesh.origin(*eit)));
		glVertex3fv(polymesh.position(polymesh.target(*eit)));
	}
	glEnd();
}

void exercise2::render_boundary_loops()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glLineWidth(5);
	glEnable(GL_LINE_SMOOTH);

	boundary_iterator bend = polymesh.boundaries_end();
	for(boundary_iterator bit = polymesh.boundaries_begin(); bit != bend; ++bit)
	{
		boundary_vertex_iterator vend = polymesh.vertices_end(*bit);
		glColor3f(1,0,0);
		glBegin(GL_LINE_LOOP);
		for(boundary_vertex_iterator vit = polymesh.vertices_begin(*bit); vit != vend; ++vit)
		{
			glVertex3fv(polymesh.position(*vit));
		}
		glEnd();

	}

}



// Show information in the main window
void exercise2::stream_stats(std::ostream& os) {
	//oprintf(os, "Hello world\n");
}
