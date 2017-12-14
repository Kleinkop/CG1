//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "halfedge_mesh_shell_extraction.h"
#include "halfedge_mesh_colorization.h"
#include <cgv/math/union_find.h>
#include <stack>

using namespace cgv::math;

//returns a vector of face handles containing one face_handle of each shell
std::vector<face_handle> extract_shells(halfedge_mesh& m, bool colorize)
{
	std::vector<face_handle> shells;

	std::vector<int> shell_id(m.num_faces(), -1);
	// student begin

	int color_group = 0;

	auto fend = m.faces_end();
	for (auto fit = m.faces_begin(); fit != fend; fit++) {

		if (shell_id[*fit] != -1) {
			continue;
		}
		
		std::stack<face_handle> stack;
		face_handle shell = *fit;
		stack.push(shell);

		while (!stack.empty()) {
			face_handle index = stack.top();
			stack.pop();

			if (shell_id[index] != -1) {
				continue;
			}
			shell_id[index] = color_group;

			auto ffend = m.faces_end(index);
			for (auto ffit = m.faces_begin(index); ffit != ffend; ffit++) {
				if (shell_id[*ffit] == -1) {
					stack.push(*ffit);
				}
			}
		}
		shells.push_back(shell);
		color_group++;
	}
	//student end
	if(colorize)
		colorize_faces(m,shell_id);
	return shells;
}



int count_shells(const halfedge_mesh& m)
{
	int nr_comp = m.num_vertices();
	union_find uf(nr_comp);
		
	auto hend = m.halfedges_end();
	for(auto hit = m.halfedges_begin(); hit !=hend; ++hit)
	{
		vertex_handle vi = m.origin(*hit);
		vertex_handle vj = m.target(*hit);
		if(uf.find(vi) != uf.find(vj))
		{
			uf.unite(vi,vj);
			nr_comp -= 1;
		}
	}
	
	return nr_comp;
}
